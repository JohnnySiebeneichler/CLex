/** Johnny C. Siebeneichler, Maurício Klipe. 25 Abril 2012 D.C..
Faz a limpeza do código, removendo comentários e separando corretamente os to-
kens.
*/
#ifndef ANALISE_H
#define ANALISE_H


#define SINAL_REMOVER_ANTERIOR -2

#define nao_imprimivel(ch) (ch == ' ' || ch == '\n' || ch == '\t')
#define carac_invalido(ch) (ch >= 127 || ch <= 7 || (ch >= 12 && ch <= 31))


#include <stdbool.h>
#include <stdio.h>
#include "util.h"
#include "erros.h"
#include "pilha.h"



/** O tipo de texto que o analisador está lendo no código. */
typedef enum {
	_codigo,	//Código compilável.
	_coment,	//Comentários com /* ou /**
	_coment_eol,	//Comentários com //
	_cadeia,	//strings, entre aspas duplas
	_caractere,	//entre aspas simples
	_preproc	//diretiva do preprocessador, inicia por #
}estado_geral;


/** O tipo de token que está sendo lido no código compilável. */
typedef enum {
	_nada,		//Quando não é nada especial.
	_espaco,	//whitespace ' ' ou tab '\t', em código compilável.
	_token,		//nomes de funções, variáveis, macros, etc., em código
			//compilável.
	_barra,		//pode iniciar comentário, em codigo compilável e dire-
			//tivas.
	_barrainvertida,//Usada para caracteres de escape, em cadeias e direti-
			//vas.
	_asterisco,	//Pode finalizar comentário.
}subestado;


typedef struct {
	FILE *in;
	FILE *out;
	pilha erros;

	int linha_atual;
	estado_geral estado_atual;
	subestado subestado_atual;
}analisador;


/** Inicializa as estruturas e variáveis do analisador. Retorna o sucesso das a-
locações. */
bool inicializar_analisador(analisador *a, FILE *in, FILE *out);


/** Declara a ocorrência de um erro na linha atual. */
void declarar_erro(analisador *a, tipo_erro tipo);


/** Muda o estado_atual do analisador para (para), e o subestado_atual para na-
da. */
void mudar_estado(analisador *a, estado_geral para);


/** Chama a função certa para tratar do caractere lido (ch), com base no estado
atual do código. Retorna o caractere a ser escrito na saida (\0 se nenhum, EOF
para o fim do source, SINAL_REMOVER_ANTERIOR se o último caractere enviado deve
ser desconsiderado e nenhum impresso. Verifica fim de arquivo e newline. */
int escolhe_estado(analisador *a, int ch);


/** As funções seguintes tratam do que fazer com o caractere lido (ch) para cada
estado em que se encontra a fonte, e retornam o caractere a ser escrito (vide
escolhe_estado() ). */
int quando_codigo(analisador *a, int ch);
int quando_coment(analisador *a, int ch);
int quando_coment_eol(analisador *a, int ch);
int quando_cadeia(analisador *a, int ch);
int quando_caractere(analisador *a, int ch);
int quando_preproc(analisador *a, int ch);


/** Verifica se um comentário está sendo iniciado na posição atual. Já atualiza
o estado. */
bool inicio_de_comentario(analisador *a, int ch);


/** Roda o analisador até o final, lendo da entrada e escrevendo na saída. */
void rodar(analisador *a);

#endif
