/**************************************
 * Esse arquivo contém funções que ajudam na implementação da Trie e do projeto.
 * Autores: Selton Miranda Rolim (GRR20235688) e Gabriel Carloto Nowak (GRR20235686).
***************************************/


#ifndef __UTILS__
#define __UTILS__

/**
 * Converte um caractere para o respectivo número do teclado T9.
 * @param c: Caractere de uma palavra. 
 * @return : Número no teclado T9. 
 **/
int charToDigit(char c);

int contains(char *digitos, char *fonte);

int palavraValida(char *p);

/**
 * Retira espaços em branco de uma string.
 * @param str: Ponteiro para a string. 
 * @return : Ponteiro para a string sem espaços em branco. 
 **/
char *trim(char *str);

/**
 * Converte uma string para o formato minúsculo.
 * @param str: Ponteiro para uma palavra. 
 **/
void toLowerCase(char *str);

#endif /*  __UTILS__  */ 