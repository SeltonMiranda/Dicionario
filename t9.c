/**************************************
 * Arquivo principal que implementa o projeto especificado no enunciado.
 * Autores: Selton Miranda Rolim (GRR20235688) e Gabriel Carloto Nowak (GRR20235686).
***************************************/


#include "trie.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

#define MAX_TAM 50

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Forneça apenas o arquivo txt.\n");
    return 1;
  }

  FILE *dicionario = fopen(argv[1], "r");
  if (dicionario == NULL) {
    fprintf(stderr, "Não foi possível abrir o arquivo.\n");
    return 1;
  }

  char palavra[MAX_TAM];
  Trie arv;
  criaArv(&arv);
  while (fscanf(dicionario, "%49s", palavra) == 1)
    insereArv(&arv, palavra);

  if (ferror(dicionario)) {
    fprintf(stderr, "Não foi possível ler o arquivo.\n");
    destroiArv(arv);
    fclose(dicionario);
    return 1;
  }

  fclose(dicionario);

  char busca[MAX_TAM * 2];
  scanf("%s", busca);
  char anterior[MAX_TAM * 2];

  while (strlen(busca) != 1 || busca[0] != '0') {

    if ( !palavraValida(busca) )
      printf("entrada invalida\n");

    else {
      if ( busca[0] == '#' ) {
        strcat(anterior, busca);
        char *word = buscaPalavra(&arv, anterior);
        if (!word)
          printf("palavra nao encontrada\n");
        else
          printf("%s\n", word);
      } 
      else {
        char *word = buscaPalavra(&arv, busca);
        if (!word)
          printf("palavra nao encontrada\n");
        else 
          printf("%s\n", word);

        strcpy(anterior, busca);
      }
    }
    scanf("%s", busca);
  }

  destroiArv(arv);
  return 0;
}
