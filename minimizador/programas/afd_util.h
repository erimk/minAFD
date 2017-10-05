/************************************
	ACH2043 - Introducao a Teoria da Computacao
	Prof. Marcelo de Souza Lauretto

	Estrutura de dados e funcoes sobre AFDs
	Adaptacao de:
	RAMOS, M. V. M.; NETO, J. J.; VEGA, I. S. Linguagens Formais. Ed. Bookman

*************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <ctype.h>

/*
  tipo estruturado AFD:
    armazena: numero de estados, numero de simbolos, simbolo inicial,
              vetor indicador de estados finais e matriz de transicoes
*/
typedef struct {
  int n;   // numero de estados
  int s;   // numero de simbolos do alfabeto
  int q0;  // estado inicial
  int *F;  // vetor binario indicando os estados de aceitacao
  int **Delta; // matriz que representarah a funcao de transicao
}tAFD;

void InicializaAFD(tAFD *aut, int n, int s);
void LiberaAFD (tAFD *aut);
int LeAFDTXT(char* nomearq, tAFD *aut);
int EscreveAFDTXT(char* nomearq, tAFD *aut);

