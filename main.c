#include <stdio.h>
#include <stdlib.h>
#include "analise.h"
#include "erros.h"
#include "es.h"

int main(int argc, char **argv) {
	FILE *in, *out;
	abrir_arquivos(argc, argv, &in, &out);

	analisador a;
	if (!inicializar_analisador(&a, in, out)) {
		debug_msg("Não conseguiu inicializar o analisador.");
		return -1;
	}
	rodar(&a);
	imprimir_relatorio_erros(&a.erros);
	finalizar_analisador(&a);

	return 0;
}
