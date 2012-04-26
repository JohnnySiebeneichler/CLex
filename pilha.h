/** Johnny C. Siebeneichler. 12 Abril 2012 D.C..
Uma pilha estática. */
#ifndef PILHA_H
#define PILHA_H


#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct pilha {
	int q;		//Quantidade de elementos.
	int max;	//Máximo de elementos.
	size_t s;	//Tamanho de cada elemento.
	void *v;	//Elementos.
}pilha;


/** Inicializa a pilha (p), com o máximo de (max) elementos de (s) bytes cada.
Caso ocorra problema na alocação, o máximo é definido como 0. */
void cria_pilha(pilha *p, int max, size_t s);


/** Insere elemento apontado por (val) na pilha (p). Caso val seja nulo, não
é inserido. Val deve ter o mesmo tamanho definido em p. Caso a pilha já esteja
cheia seu máximo é dobrado, se isso não for possível nada ocorre. */
void push(pilha *p, void *val);

/** Remove o último elemento da pilha (p). Caso não existam elementos, nada o-
corre. */
void pop(pilha *p);

/** Retorna o último elemento da pilha (p). Caso não hajam elementos, retorna
NULL. */
void *peek(pilha *p);

/** Retorna o elemento na posição (pos) da pilha (p). Caso a pilha não tenha es-
se elemento, é retornado NULL. */
void *access(pilha *p, int pos);

/** Desaloca o vetor dos elementos da pilha, e os outros valores são zerados. */
void destroi_pilha(pilha *p);

/** Remove todos elementos da pilha, sem modificar o máximo nem desalocar nada.
*/
void limpa_pilha(pilha *p);

/** Dobra o máximo da pilha. Se não conseguir aumentar, não muda nada. Retorna o
sucesso da realocação. */
bool aumentar_pilha(pilha *p);


#endif
