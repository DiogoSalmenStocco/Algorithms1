#include <stdio.h>
#include <stdbool.h>
#include "Pilha_hist.h"

typedef struct noh
{
    char *nome;
    int id;
    struct noh* prox;
    historico* h;
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
Lista* buscar_paciente(Lista* lista, int id);
Lista* buscar_paciente_nome(Lista* lista, char* nome);
Lista* listar_pacientes(Lista* lista);