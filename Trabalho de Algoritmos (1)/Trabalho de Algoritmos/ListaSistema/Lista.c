#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> 
#include "Lista.h"
#include "Pilha_hist.h"

// Funcao auxiliar para liberar a memoria de um paciente_h (nome e historico)
void liberar_paciente(paciente_h* p) {
    if (p) {
        if (p->nome) free(p->nome);
        if (p->h) free(p->h); // Libera o historico (pilha)
        free(p);
    }
}

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
  if (novo == NULL) return false;
  
  // Correcao: Aloca memoria para o nome e copia (evita vazamento)
  novo->nome = strdup(nome);
  if (novo->nome == NULL) {
      free(novo);
      return false;
  }

  novo->id = id;
  novo->h = criar_historico(); // Inicializa o historico
  novo->prox = lista->inicio;
  lista->inicio = novo;
  if (lista->fim == NULL) lista->fim = novo;
  lista->tamanho++;
  return true;
}

bool inserir_paciente_mid(Lista* lista, char* nome, int id) {
  paciente_h* novo = (paciente_h*)malloc(sizeof(paciente_h));
  if (novo == NULL) return false;

  // Correcao: Aloca memoria para o nome e copia (evita vazamento)
  novo->nome = strdup(nome);
  if (novo->nome == NULL) {
      free(novo);
      return false;
  }
  
  novo->id = id;
  novo->h = criar_historico(); // Inicializa o historico
  novo->prox = NULL;

  if (lista->tamanho == 0) {
    // Caso especial: lista vazia. Trata como insercao no inicio.
    lista->inicio = novo;
    lista->fim = novo;
    lista->tamanho++;
    return true;
  }
  
  // Encontra o ponto de insercao (meio)
  paciente_h* atual = lista->inicio;
  int meio = lista->tamanho / 2;
  for (int i = 1; i < meio; i++) {
    atual = atual->prox;  
  }
  
  // Logica de insercao
  novo->prox = atual->prox;
  atual->prox = novo;
  lista->tamanho++;
  
  return true; // Correcao: Falta de retorno
}

bool inserir_paciente_fim(Lista* lista, char* nome, int id) {
  paciente_h* novo = (paciente_h*)malloc(sizeof(paciente_h));
  if (novo == NULL) return false;

  // Correcao: Aloca memoria para o nome e copia (evita vazamento)
  novo->nome = strdup(nome);
  if (novo->nome == NULL) {
      free(novo);
      return false;
  }
  
  novo->id = id;
  novo->h = criar_historico(); // Inicializa o historico
  novo->prox = NULL;
  
  if (lista->tamanho == 0)
  {
    lista->inicio = novo;
    lista->fim = novo;
    lista->tamanho++;
    return true;
  }
  
  // Se ja existe, insere no fim
  lista->fim->prox = novo;
  lista->fim = novo;
  lista->tamanho++;
  return true; // Correcao: Falta de retorno
}

// Funcao base para remocao generica por ID
bool apagar_paciente(Lista* lista, int id) {
  paciente_h* atual = lista->inicio;
  paciente_h* anterior = NULL;
  
  // Busca o paciente
  while (atual && atual->id != id) {
    anterior = atual;
    atual = atual->prox;
  }
  
  // Se encontrou o paciente
  if (atual) {
    if (anterior) {
      // O paciente esta no meio ou fim
      anterior->prox = atual->prox;
    } else {
      // O paciente e o inicio da lista
      lista->inicio = atual->prox;
    }
    
    // Atualiza o fim, se necessario
    if (atual == lista->fim) {
      lista->fim = anterior;
    }
    
    // Libera a memoria do paciente, nome e historico
    liberar_paciente(atual);
    lista->tamanho--;
    return true;
  }
  return false;
}

// As funcoes _in, _mid, _fim sao redefinidas para chamar a remocao por ID,
// ja que um paciente é identificado unicamente pelo ID.
bool apagar_paciente_in(Lista* lista, int id) {
    return apagar_paciente(lista, id);
}
bool apagar_paciente_mid(Lista* lista, int id) {
    return apagar_paciente(lista, id);
}
bool apagar_paciente_fim(Lista* lista, int id) {
    return apagar_paciente(lista, id);
}

// Funcoes de busca
paciente_h* buscar_paciente_noh(Lista* lista, int id) {
  paciente_h* atual = lista->inicio;
  while (atual) {
    if (atual->id == id)
      return atual; // Retorna o no
    atual = atual->prox;
  }
  return NULL;
}

paciente_h* buscar_paciente_nome_noh(Lista* lista, char* nome) {
  paciente_h* atual = lista->inicio;
  while (atual) {
    // Uso de strcmp para comparacao de strings
    if (strcmp(atual->nome, nome) == 0)
      return atual; // Retorna o no
    atual = atual->prox;
  }
  return NULL;
}

Lista* listar_pacientes(Lista* lista) 
{
  paciente_h* atual = lista->inicio;
  if (lista->tamanho == 0) {
      printf("Lista de pacientes vazia.\n");
      return lista;
  }
  printf("\n--- Lista de Pacientes no Sistema ---\n");
  while (atual) {
    printf("ID: %d, Nome: %s\n", atual->id, atual->nome);
    atual = atual->prox;
  }
  printf("--------------------------------------\n");
  return lista;
}