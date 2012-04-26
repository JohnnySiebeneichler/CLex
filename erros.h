/** Johnny C. Siebeneichler, Maurício M. Klipe. 23 Abril 2012.
Lida com erros que podem ocorrer durante a análise léxica.
*/
#ifndef ERROS_H
#define ERROS_H


#include <stdio.h>
#include "pilha.h"


typedef enum {

	/** Quando um string é aberto em uma linha e não é fechado na mesma, e a
	linha não é finalizada com uma barra invertida. */
	ERRO_STRING_NAO_FECHADO_CORRETAMENTE,

	/** Quando um char (entre aspas simples) não é fechado na mesma linha.
	Note que o analisador léxico não verifica se há só um caractere dentro
	das aspas. */
	ERRO_CHAR_NAO_FECHADO_CORRETAMENTE,

	/** Quando a linha é finalizada com uma barra invertida mas não existe
	uma próxima linha para juntar. */
	ERRO_SEM_LINHA_PARA_CONTINUAR,

	/** Quando é encontrado um caractere inválido. Não considera-se inválido
	se ocorre dentro de string ou comentário. */
	ERRO_CARACTERE_INVALIDO
}tipo_erro;


typedef struct {
	int linha;
	tipo_erro tipo;
}ocorrencia_de_erro;


/** Imprime uma mensagem de erro no stderr. Quebra linha. */
void imprimir_msg_erro(ocorrencia_de_erro err);

/** Imprime todos os erros de uma pilha de ocorrencia_de_erro, e a quantidade de
erros. */
void imprimir_relatorio_erros(pilha *p);


//#define DEBUG


#ifdef DEBUG
#define debug_msg(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug_msg(...)
#endif



#endif
