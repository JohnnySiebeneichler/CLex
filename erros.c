/** Johnny C. Siebeneichler, Maurício M. Klipe. 26 Abril 2012. */
#ifndef ERROS_C
#define ERROS_C

#include "erros.h"

void imprimir_msg_erro(ocorrencia_de_erro err) {
	fprintf(stderr, "ERRO (linha %d): ", err.linha);

	switch (err.tipo) {

	case ERRO_STRING_NAO_FECHADO_CORRETAMENTE:
		fprintf(stderr, "Cadeia de caracteres nao foi fechada \
corretamente.\n");
		break;
	case ERRO_CHAR_NAO_FECHADO_CORRETAMENTE:
		fprintf(stderr, "Caractere nao foi fechado corretamente.\n");
		break;
	case ERRO_SEM_LINHA_PARA_CONTINUAR:
		fprintf(stderr, "A linha termina em barra invertida, mas nao \
ha linha seguinte para juntar.\n");
		break;
	case ERRO_CARACTERE_INVALIDO:
		fprintf(stderr, "Caractere nao reconhecido.\n");
		break;
	default:
		debug_msg("Armazenou tipo desconhecido no erro.\n");
	}
}




void imprimir_relatorio_erros(pilha *p) {
	if (!p) return;

	fprintf(stderr, "Foram encontrados %d erros durante a analise lexica.\n"
		, p->q);

	int c;
	for (c = 0; c < p->q; c++) {
		ocorrencia_de_erro *err = access(p, c);
		imprimir_msg_erro(*err);
	}
}

#endif
