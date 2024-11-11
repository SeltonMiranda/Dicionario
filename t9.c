#include "trie.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

#define MAX_TAM 50

int main(int argc, char **argv) {
    
    if ( argc != 2 ) {
        fprintf(stderr, "Forneça apenas o arquivo txt.\n");
	return 1;
    }
   
    FILE *dicionario = fopen(argv[1], "r");
    if ( dicionario == NULL ) {
        fprintf(stderr, "Não foi possível abrir o arquivo.\n");
	return 1;
    }

    char palavra[MAX_TAM];
    Trie arv;
    criaArv(&arv);
    while ( fscanf(dicionario, "%49s", palavra) == 1 )
	insereArv( &arv, palavra );

    fclose( dicionario );

    char busca[MAX_TAM * 2];
    scanf("%s", busca);
    char anterior[MAX_TAM * 2];

    while ( strlen(busca) != 1 || busca[0] != '0' ) {
    	
	char *teste = busca;
	int saiu = 0;

        while ( *teste != '\0' && !saiu ) {
	    if ( *teste == '0' ) {
		printf("entrada invalida\n");
		saiu = 1;
	    }
	    ++teste;
        }

	if ( busca[0] == '#' ) {
            strcat( anterior, busca );
	    char *word = buscaPalavra( &arv, anterior );
	    if ( word )
		printf("%s\n", word);
	}

	if ( !saiu && busca[0] != '#' ) {
            char *word = buscaPalavra( &arv, busca );
	    if ( word )
	        printf("%s\n", word);
	    strcpy( anterior, busca );
	}
        scanf("%s", busca);
    }

    destroiArv(arv);
    return 0;
}
