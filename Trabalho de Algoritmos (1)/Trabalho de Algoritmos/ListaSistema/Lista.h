#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdbool.h>
#include "Pilha_hist.h"

typedef struct noh
{
    char *nome;
    int id;
    struct noh* prox;
    historico* h; // Ponteiro para o historico (pilha) do paciente
} paciente_h;

typedef struct Lista_
{
    paciente_h* inicio;
    paciente_h* fim;
    int tamanho;
}Lista;

void inicializar(Lista* lista);
bool inserir_paciente_in(Lista* lista, char* nome, int id);
bool inserir_paciente_mid(Lista* lista, char* nome, int id);
bool inserir_paciente_fim(Lista* lista, char* nome, int id);
bool apagar_paciente_in(Lista* lista, int id);
bool apagar_paciente_mid(Lista* lista, int id);
bool apagar_paciente_fim(Lista* lista, int id);
bool apagar_paciente(Lista* lista, int id); // Adicionado

// As funcoes de busca devem retornar o noh do paciente para ser util
paciente_h* buscar_paciente_noh(Lista* lista, int id);
paciente_h* buscar_paciente_nome_noh(Lista* lista, char* nome);

Lista* listar_pacientes(Lista* lista);

#endif // LISTA_H