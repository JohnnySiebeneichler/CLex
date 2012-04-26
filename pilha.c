/** Johnny C. Siebeneichler. 12 Abril 2012 D.C..
Uma pilha estática. */
#ifndef PILHA_C
#define PILHA_C


#include "pilha.h"


void cria_pilha(pilha *p, int max, size_t s) {
	if (!p || max < 0 || s < 0) return;

	p->max = max;
	p->s = s;
	p->q = 0;
	p->v = malloc(s * max);
	if (!p->v) {
		p->max = 0;
	}
}

void push(pilha *p, void *val) {
	if (!p) return;
	if (p->q >= p->max) {
		if (!aumentar_pilha(p)) return;
	}
	memcpy(p->v + (p->q)*(p->s), val, p->s);
	p->q++;
}

void pop(pilha *p) {
	if (p && p->q > 0) p->q--;
}

void *peek(pilha *p) {
	return (p->q > 0)? (p->v + (p->q - 1) * (p->q)) : NULL;
}

void *access(pilha *p, int pos) {
	return (p->q >= pos)? p->v + pos * p->s : NULL;
}

void destroi_pilha(pilha *p) {
	if (p->v) free(p->v);
	p->q = 0;
	p->s = 0;
	p->max = 0;
}

void limpa_pilha(pilha *p) {
	p->q = 0;
}

bool aumentar_pilha(pilha *p) {
	if (!p) return false;
	void *buff = p->v;
	p->v = realloc(p->v, 2 * p->max);
	if (!p->v) {
		p->v = buff;
		return false;
	}
	p->max *= 2;
	return true;
}

#endif
