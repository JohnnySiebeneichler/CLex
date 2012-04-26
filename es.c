/** Johnny C. Siebeneichler, Maurício Klipe. 26 Abril 2012 D.C..
Define os arquivos de entrada a saída. */

#ifndef ES_C
#define ES_C

#include "es.h"



void abrir_arquivos(int argc, char **argv, FILE **in, FILE **out) {
	*in = stdoin;
	*out = stdout;

	int c1;
	for (c1 = 1; c1 < argc - 1; c1++) {
		if (!strcmp(argc[c1], "-i")) {
			*in = fopen(argc[c1+1], "r");
			if (!*in) {
				*out = NULL;
				return;
			}
		}

		else if (!strcmp(argc[c1], "-o")) {
			*out = fopen(argc[c1+1], "w");
			if (!*out) {
				*in = NULL;
				return;
			}
		}
	}
}



void fechar_arquivos(FILE **in, FILE **out) {
	if (*in && *in != stdin) fclose(*in);
	if (*out && *out != stdout) fclose(*out);
}

#endif
