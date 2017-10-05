
/************************************
	ACH2043 - Introducao a Teoria da Computacao
	Prof. Marcelo de Souza Lauretto

	Estrutura de dados e funcoes sobre AFDs
	Adaptacao de:
	RAMOS, M. V. M.; NETO, J. J.; VEGA, I. S. Linguagens Formais. Ed. Bookman

  Chamada:
     converte_afd <inp_afd> <out_afd>
  Ver detalhes dos tipos de arquivos no comentario da funcao main

  compilacao:
    gcc -Wall -O3 -o converte_afd.exe afd_util.c -D _STANDALONE_

*************************************/

// #define _STANDALONE_

#define M_PI 3.14159265358979323846
#define MAX_AFD_SZ 200
#define swap(type, i, j) {type vaux = i; i = j; j = vaux;}

#include "afd_util.h"

/*
  InicializaAFD(AFD, n, s):
  Inicializa a estrutura para um AFD com n estados e s simbolos
  Aloca espaco para o vetor binario de estados finais e para a matriz de transicao
*/
void InicializaAFD(tAFD *aut, int n, int s) {
  int i, j;
  aut->n = n;
  aut->s = s;

  aut->F = (int*) calloc(n, sizeof(int));
  for (i=0; i<n; i++) aut->F[i] = 0;

  aut->Delta = (int**) calloc(n, sizeof(int*));
  for (i=0;i<n; i++)
    aut->Delta[i] = (int*) calloc(s, sizeof(int));

  for (i=0; i<n; i++)
    for (j=0; j<s; j++)
      aut->Delta[i][j] = -1;
}


/*
  LiberaAFD(AFD): Liberar o espaco ocupado por um AFD.
*/
void LiberaAFD (tAFD *aut) {
  int i;
  int *v;

  free(aut->F);
  for (i=0;i<aut->n; i++) {
    v = aut->Delta[i];
    free(v);
  }
  free(aut->Delta);
  aut->n = aut->s = 0;
}

/*
  LeAFDTXT(nomearq, aut)
  Le o arquivo nomearq e armazena na estrutura aut
  Lay-out:
    A 1a linha deve conter o número de estados, numero de simbolos do alfabeto e indice do estado inicial.
    A 2a linha contem um vetor binario F:
         F[i] = 1 se estado i eh de aceitacao; F[i] = 0 caso contrario
    As proximas linhas contem os elementos da matriz de transicao:
    Delta[i][j] = estado ao qual o automato deve ir se estiver no estado i e ler o simbolo j
    Se nao houver transicao do estado i com o simbolo j, Delta[i][j] = -1
    Observações:
      - Estados e simbolos sao indexados de 0 a n-1 e 0 a s-1
      - Em cada linha, os simbolos sao separados por espacos

  Codigo de saida:
    1: leitura bem sucedida
    0: erro na leitura do arquivo
*/
int LeAFDTXT(char* nomearq, tAFD *aut) {
  FILE *fp;
  int i, j, n, s, q0;

  fp = fopen(nomearq, "rt");
  if (fp==NULL) return(0);

  if (fscanf(fp, "%u %u %u", &n, &s, &q0)!=3) return(0);

  InicializaAFD(aut, n, s);

  aut->n = n;
  aut->s = s;
  aut->q0 = q0;

  for (i=0; i<n; i++) {
    if (fscanf(fp, "%d", &(aut->F[i])) !=1 ) {
      LiberaAFD(aut);
      return(0);
    }
  }

  // for (i=0;i<n;i++) printf("elemento %d: %d\n", i, aut->F[i]);

  for (i=0;i<n; i++)
    for (j=0; j<s; j++) {
      if (fscanf(fp, "%d", &(aut->Delta[i][j])) != 1) {
        LiberaAFD(aut);
        return(0);
      }
    }

  fclose(fp);
  return(1);
}


/*
  EscreveFD(nomearq, aut)
  Escreve o automato no arquivo nomearq
  Lay-out: identico aa funcao LeAFDTXT

  Codigo de saida:
    1: escrita bem sucedida
    0: erro na escrita do arquivo
*/
int EscreveAFDTXT(char* nomearq, tAFD *aut) {
  FILE *fp;
  int i, j;

  fp = fopen(nomearq, "wt");
  if (fp==NULL)
     return(0);

  fprintf(fp, "%d %d %d\n", aut->n,  aut->s, aut->q0);

  for (i=0;i<aut->n;i++)
    fprintf(fp, "%d ", aut->F[i]);
  fprintf(fp, "\n");

  for (i=0;i<aut->n; i++) {
    for (j=0; j<aut->s; j++)
      fprintf(fp, "%d ", aut->Delta[i][j]);
    fprintf(fp, "\n");
  }

  fclose(fp);
  return(1);
}

/*
  Esta implementacao da funcao main serve exclusivamente para leitura e escrita de
  automatos, tanto no formato texto do enunciado do EP como no formato do JFlap.

  chamada:
     converte_afd <inp_afd> <out_afd>

  Os formatos dos arquivos de entrada e saida dependem das extensoes:
    Se extensao for .JFF: formato JFlap (XML)
    Qualquer outra extensao (ou sem extensao): formato texto:
        1a linha:   n  s  q0
        2a linha: vetor binario F indicando quais sao os estados finais
        3a linha em diante: matriz de transicao:
             Delta[i][j] = estado de destino dado o estado i e simbolo j
    Observacao: maiusculas e minusculas nao sao diferenciadas na extensao

  Exemplo:
    converte_afd <afd01.txt> <afd01.jff>  --> converte de TXT para JFF

*/
#ifdef _STANDALONE_
int main(int argc, char *argv[]) {
  tAFD aut;
  char inpformat, outformat;

  if (argc!=3) {
    printf("Chamada correta: \n");
    printf("   converte_afd <inp_afd> <out_afd> \n");
    printf("Se extensao for .jff, assume-se o formato do JFlap.\n");
    return(1);
  }

  printf("%c  %c  \n", inpformat, outformat);

  LeAFDTXT(argv[1], &aut);
  EscreveAFDTXT(argv[2], &aut);

  LiberaAFD (&aut);
  return(0);
}
#endif // _STANDALONE_