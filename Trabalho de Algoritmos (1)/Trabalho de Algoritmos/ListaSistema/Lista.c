#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Lista.h"
#include "Pilha_hist.h"

// Funções
void inicializar(Lista* lista) 
{
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

bool inserir_paciente_in(Lista* lista, char* nome, int id) 
{
  paciente_h* novo = (paciente_h*)malloc(sizeof(paciente_h));
  if (novo == NULL)return false;
  
  novo->nome = nome;
  novo->id = id;
  novo->prox = lista->inicio;
  lista->inicio = novo;
  if (lista->fim == NULL)lista->fim = novo;
  lista->tamanho++;
  return true;
}

bool inserir_paciente_mid(Lista* lista, char* nome, int id) {
  paciente_h* novo = (paciente_h*)malloc(sizeof(paciente_h));
  if (novo == NULL)return false;

  novo->nome = nome;
  novo->id = id;

  if (lista->tamanho < 2) {
    inserir_paciente_in(lista, nome, id);
    return true;
  }
  paciente_h* atual = lista->inicio;
  int meio = lista->tamanho / 2;
  for (int i = 1; i < meio; i++) {
    atual = atual->prox;  
  }
  novo->prox = atual->prox;
  atual->prox = novo;
}

bool inserir_paciente_fim(Lista* lista, char* nome, int id) {
  paciente_h* novo = (paciente_h*)malloc(sizeof(paciente_h));
  if (novo == NULL)return false;

  if (lista->tamanho == 0)
  {
    inserir_paciente_in(lista, nome, id);
    return true;
  }
  
  novo->nome = nome;
  novo->id = id;
  novo->prox = NULL;
  if (lista->fim)
    lista->fim->prox = novo;
  else
    lista->inicio = novo;
  lista->fim = novo;
  lista->tamanho++;
}

bool apagar_paciente_in(Lista* lista, int id) {
  paciente_h* atual = lista->inicio;
  paciente_h* anterior = NULL;
  while (atual && atual->id != id) {
    anterior = atual;
    atual = atual->prox;
  }
  if (atual) {
    if (anterior)
      anterior->prox = atual->prox;
    else
      lista->inicio = atual->prox;
    if (atual == lista->fim)
      lista->fim = anterior;
    free(atual->nome);
    free(atual);
    lista->tamanho--;
  }
}

bool apagar_paciente(Lista* lista, int id) {
  apagar_paciente_in(lista, id);
}

bool apagar_paciente_fim(Lista* lista, int id) {
  paciente_h* atual = lista->inicio;
  paciente_h* anterior = NULL;
  paciente_h* ultimo = NULL;
  paciente_h* penultimo = NULL;
  while (atual) {
    if (atual->id == id)
      ultimo = atual;
    if (ultimo)
      penultimo = anterior;
    anterior = atual;
    atual = atual->prox;
  }
  if (ultimo) {
    if (penultimo)
      penultimo->prox = ultimo->prox;
    else
      lista->inicio = ultimo->prox;
    if (ultimo == lista->fim)
      lista->fim = penultimo;
    free(ultimo->nome);
    free(ultimo);
    lista->tamanho--;
  }
}

Lista* buscar_paciente(Lista* lista, int id) {
  paciente_h* atual = lista->inicio;
  while (atual) {
    if (atual->id == id)
      return lista;
    atual = atual->prox;
  }
  return NULL;
}

Lista* buscar_paciente_nome(Lista* lista, char* nome) {
  paciente_h* atual = lista->inicio;
  while (atual) {
    if (strcmp(atual->nome, nome) == 0)
      return lista;
    atual = atual->prox;
  }
  return NULL;
}

Lista* listar_pacientes(Lista* lista) 
{
  paciente_h* atual = lista->inicio;
  while (atual) {
    printf("ID: %d, Nome: %s\n", atual->id, atual->nome);
    atual = atual->prox;
  }
  return lista;
}