/** Johnny C. Siebeneichler, Maurício Klipe. 26 Abril 2012 D.C..*/
#ifndef ANALISE_C
#define ANALISE_C


#include "analise.h"


bool inicializar_analisador(analisador *a, FILE *in, FILE *out) {
	if (!a || !in || !out) return false;

	a->in = in;
	a->out = out;
	cria_pilha(&(a->erros), 100, sizeof(ocorrencia_de_erro));
	if (a->erros.max == 0) return false;
	a->linha_atual = 1;
	a->estado_atual = _codigo;
	a->subestado_atual = _nada;

	return true;
}


void finalizar_analisador(analisador *a) {
	if (!a) return;

	fechar_arquivos(&a->in, &a->out);
	destroi_pilha(&a->erros);
	a->linha_atual = 0;
	a->estado_atual = _codigo;
	a->subestado_atual = _nada;
}


void declarar_erro(analisador *a, tipo_erro tipo) {
	ocorrencia_de_erro ode;
	ode.linha = a->linha_atual;
	ode.tipo = tipo;
	push(&a->erros, &ode);
}


void mudar_estado(analisador *a, estado_geral para) {
	a->estado_atual = para;
	a->subestado_atual = _nada;
}


int escolhe_estado(analisador *a, int ch) {

	if (ch == EOF) {
		if (a->subestado_atual == _barrainvertida) {
			declarar_erro(a, ERRO_SEM_LINHA_PARA_CONTINUAR);
		}
		return EOF;
	}
	if (ch == '\n') a->linha_atual++;

	switch (a->estado_atual) {

	case _codigo: return quando_codigo(a, ch);
	case _coment: return quando_coment(a, ch);
	case _coment_eol: return quando_coment_eol(a, ch);
	case _cadeia: return quando_cadeia(a, ch);
	case _caractere: return quando_caractere(a, ch);
	case _preproc: return quando_preproc(a, ch);
	default: debug_msg("Estado desconhecido.\n");
	}
	return EOF;
}


int quando_codigo(analisador *a, int ch) {

	if (carac_invalido(ch)) {
		declarar_erro(a, ERRO_CARACTERE_INVALIDO);
		return 0;
	}

	//Verifica se um comentário está iniciando.
	if (inicio_de_comentario(a, ch)) return SINAL_REMOVER_ANTERIOR;

	//Verifica se está iniciando uma diretiva do preprocessador. Note que só
	//inicia se os caracteres antes do # na linha são tab ou espaço.
	if (a->subestado_atual == _nada) {
		if (ch == '#') {
			mudar_estado(a, _preproc);
			return ch;
		}
	}

	//Verifica se está com mais de um espaço/tab/newline seguido.
	if (a->subestado_atual == _nada || a->subestado_atual == _espaco) {
		if (nao_imprimivel(ch)) return 0;
	}

	if (ch == '/') a->subestado_atual = _barra;
	else if (ch == '\\') a->subestado_atual = _barrainvertida;
	else if (nao_imprimivel(ch)) a->subestado_atual = _espaco;
	else if (ch == '"') mudar_estado(a, _cadeia);
	else if (ch == '\'') mudar_estado(a, _caractere);
	else a->subestado_atual = _token;

	return ch;

}


int quando_coment(analisador *a, int ch) {
	if (a->subestado_atual == _asterisco && ch == '/') {
		mudar_estado(a, _codigo);
	}
	else if (ch == '*') {
		a->subestado_atual = _asterisco;
	}
	else a->subestado_atual = _nada;
	return 0;
}

int quando_coment_eol(analisador *a, int ch) {

	if (ch == '\n') {
		mudar_estado(a, _codigo);
	}
	return 0;
}

int quando_cadeia(analisador *a, int ch) {

	if (a->subestado_atual != _barrainvertida) {

		switch (ch) {
		case '\n': declarar_erro(a,
					ERRO_STRING_NAO_FECHADO_CORRETAMENTE);
		case '"': mudar_estado(a, _codigo); break;
		case '\\': a->subestado_atual = _barrainvertida; return ch;
		}
	}
	else if (ch == '\n') {
		a->subestado_atual = _nada;
		return SINAL_REMOVER_ANTERIOR;
	}
	a->subestado_atual = _nada;

	return ch;
}

int quando_caractere(analisador *a, int ch) {
	if (ch == '\\' && a->subestado_atual != _barrainvertida) {
		a->subestado_atual = _barrainvertida;
		return ch;
	}
	if (ch == '\'' && a->subestado_atual != _barrainvertida) {
		mudar_estado(a, _codigo);
	}
	else if (ch == '\n') {
		declarar_erro(a, ERRO_CHAR_NAO_FECHADO_CORRETAMENTE);
		mudar_estado(a, _codigo);
	}
	a->subestado_atual = _nada;
	return ch;
}

int quando_preproc(analisador *a, int ch) {

	if (carac_invalido(ch)) {
		declarar_erro(a, ERRO_CARACTERE_INVALIDO);
		return 0;
	}

	if (inicio_de_comentario(a, ch)) return SINAL_REMOVER_ANTERIOR;

	if (ch == '\n') {
		if (a->subestado_atual != _barrainvertida) {
			mudar_estado(a, _codigo);
		}
		else return SINAL_REMOVER_ANTERIOR;
	}
	else if (ch == '/') {
		a->subestado_atual = _barra;
	}
	return ch;
}



bool inicio_de_comentario(analisador *a, int ch) {
	if (a->subestado_atual == _barra) {
		if (ch == '/') {
			mudar_estado(a, _coment_eol);
		}
		else if (ch == '*') {
			mudar_estado(a, _coment);
		}
		else return false;
		return true;
	}
	return false;
}



void rodar(analisador *a) {
	if (!a || !a->in || !a->out) return;

	int ch_anterior = 0;
	int ch;
	int retorno;

	while (1) {

		ch = fgetc(a->in);
		retorno = escolhe_estado(a, ch);
		debug_msg("%c %d (%d %d)\n", ch, retorno, a->estado_atual,
			a->subestado_atual);

		switch (retorno) {
			case EOF: fputc(ch_anterior, a->out); return;
			case SINAL_REMOVER_ANTERIOR: retorno = 0; break;
			case 0:
				if (ch_anterior != 0) {
					fputc(ch_anterior, a->out);
				}
				retorno = 0;
				break;
			default:
				if (ch_anterior != 0) {
					fputc(ch_anterior, a->out);
				}
		}
		ch_anterior = retorno;
	}
}


#endif
