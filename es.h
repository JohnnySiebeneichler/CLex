/** Johnny C. Siebeneichler, Maurício Klipe. 26 Abril 2012 D.C..
Define os arquivos de entrada a saída. */

#ifndef ES_H
#define ES_H

#include <stdio.h>
#include "erros.h"

/** Com base nos parâmetros passados ao programa, definir e abrir os arquivos de
entrada e saída para o analisador léxico. Caso o arquivo de entrada não tenha
sido definido, usa-se stdin; caso o arquivo de saída não tenha sido definido, u-
sa-se stdout. Caso um deles tenha sido definido mas ocorra erro ao abri-lo, am-
bos são definidos como NULL. */
void abrir_arquivos(int argc, char **argv, FILE **in, FILE **out);

/** Fecha os arquivos abertos pela função abrir_arquivos(). */
void fechar_arquivos(FILE **in, FILE **out);


#endif
