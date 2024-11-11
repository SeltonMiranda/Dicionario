#include "trie.h"

#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Função que cria um novo nodo na Trie. Pode conter
 * uma palavra ou não.
 *
 * @param palavra: Ponteiro para palavra a ser inserida. 
 * @return ApNodo: Novo nodo. 
 **/
static ApNodo criaNodo(const char *palavra) {
    ApNodo novo = (ApNodo)malloc(sizeof(Nodo));
    if (novo == NULL)
        return NULL;

    if (palavra == NULL) novo->palavra = NULL;
    else novo->palavra = strdup(palavra);

    for (int i = 0; i < RANGE; i++)
        novo->prox[i] = NULL;
    
    return novo;
}

/**
 * Função auxiliar que insere uma palavra na Trie como
 * uma lista ligada.
 * 
 * @param raiz: Ponteiro para a raiz da árvore.
 * @param palavra: Ponteiro para palavra a ser inserida.  
 **/
static void insereLista(Trie *raiz, char *palavra) {
    ApNodo atual = *raiz;
    ApNodo anterior = NULL;
    while (atual != NULL) {
        anterior = atual;
        atual = atual->prox[HASHTAG];
    }
        
    atual = criaNodo(palavra);
    if (atual == NULL) {
        fprintf(stderr, "ERRO: Nao foi possivel alocar memoria para o nodo %s\n", palavra);
        return;
    }
    anterior->prox[HASHTAG] = atual;
}

/**
 * Função recursiva auxiliar que insere uma palavra na Trie,
 * retorna a nova raíz da subárvore.
 * 
 * @param raiz: Ponteiro para a raiz da árvore.
 * @param palavra: Ponteiro para palavra a ser inserida.
 * @param c: Ponteiro para o primeiro caractere da palavra.
 * @return Trie: Raíz da nova subárvore.  
 **/
static Trie insereR(Trie *raiz, char *palavra, char *c) {
    if (*c == '\0') { 
        if (*raiz == NULL) { // Caso em que chegou em um nodo nulo
            *raiz = criaNodo(palavra);
            if (*raiz == NULL) {
                fprintf(stderr, "ERRO: Nao foi possivel alocar memoria para o nodo %s\n", palavra);
                return NULL;
            }
        } else {
            if ((*raiz)->palavra != NULL) { // Verifica se já existe uma palavra no nodo atual.
                // Caso exista, insira a nova palavra como uma lista ligada.
                insereLista(raiz, palavra); 
            } else {
                // Caso não exista, simplesmente copie a palavra para o nodo atual.
                (*raiz)->palavra = strdup(palavra);
            }
        }
        return *raiz;
    }

    int index = charToDigit(*c);

    if (*raiz == NULL) {
        *raiz = criaNodo(NULL);
        if (*raiz == NULL) {
                fprintf(stderr, "ERRO: Nao foi possivel alocar memoria para o nodo\n");
                return NULL;
        }
    }

    (*raiz)->prox[index] = insereR(&((*raiz)->prox[index]), palavra, ++c);
    return *raiz;
}

void criaArv(Trie *raiz) {
    *raiz = NULL;
}

void insereArv(Trie *raiz, char *palavra) {
    char *c = palavra; // Ponteiro para o caractere da palavra
    *raiz = insereR(raiz, palavra, c);
}

void imprimeArv(Trie raiz, int profundidade) {
    if (raiz == NULL)
        return;
    
    if (raiz->palavra != NULL)
        printf("palavra: %s, profundidade: %d\n", raiz->palavra, profundidade);

    for (int i = 0; i < RANGE; i++) {
        if (raiz->prox[i] != NULL) {
            if (i == HASHTAG) {
                printf("%s ", "#");
            } else {
                printf("%d ", i);
            }
            imprimeArv(raiz->prox[i], profundidade + 1);
        }
    }
}

/**
 * Função auxiliar recursiva que busca uma palavra na Trie.
 * 
 * @param raiz: Ponteiro para a raiz da árvore.
 * @param palavra: Ponteiro para palavra a ser inserida.  
 **/
static char *buscaR(Trie *raiz, char *c) {
    
    if (*raiz == NULL)
	    return NULL;

    if (*c == '\0') {
        if (*raiz != NULL) {
            if ((*raiz)->palavra == NULL)
                return NULL;
            else
                return (*raiz)->palavra;
        }
        return NULL;
    }

    if (*c == '#')
        return buscaR(&(*raiz)->prox[HASHTAG], ++c);

    int index = *c - '0';
    if ((*raiz)->prox[index] == NULL)
        return NULL;
    else 
        return buscaR(&(*raiz)->prox[index], ++c);
}

char *buscaPalavra(Trie *raiz, char *palavra) {
    if (*raiz == NULL) 
        return NULL;

    return buscaR(raiz, palavra);
}

void destroiArv(Trie raiz) {
    if (raiz == NULL) return;

    for (int i = 0; i < RANGE; i++) {
        destroiArv(raiz->prox[i]);    
    }

    if (raiz->palavra) 
        free(raiz->palavra);
    free(raiz);
}
