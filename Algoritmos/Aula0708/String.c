#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "String.h"

// A implementação de TODAS as operacoes...
/*
Pre-cond: uma string em c
Pos-cond: retorna um ponteiro para String formada.
        Em caso de erro, retorna NULL
*/
String* createString(const char *s)
{
    String *temp;

    temp = (String *)malloc(sizeof(String));
    if (temp == NULL) return NULL;

    // aloca espaco para a string
    temp->dado = (char*)malloc((strlen(s) + 1) * sizeof(char));
    if (temp->dado == NULL) return NULL;

    // copia conteudo
    strcpy(temp->dado, s);
    //atualiza tamanho
    temp->tam = strlen(s);
}

/*
*/
void delString(String *s)
{
    if (s != NULL)
    {
        free(s->dado);
        free(s);
    }
}

char * c_str(String *s)
{
    if(s == NULL)
    {
        return " ";
    }
    return s->dado;
}