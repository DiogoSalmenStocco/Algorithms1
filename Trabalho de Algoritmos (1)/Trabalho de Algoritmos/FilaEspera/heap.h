#ifndef HEAP_H // Use HEAP_H
#define HEAP_H // Não use o ponto (.), use um nome de macro padrão
#define tam_max_heap 50

#include "../ListaSistema/Lista.h"

typedef struct nodo_heap{
    paciente_h* paciente;
    int prioridade;
}NOH_HEAP;

typedef struct heap{
    NOH_HEAP *pacienteH;
    int tam_max;
    int tam_atual;
}HEAP;

HEAP* criar_heap();
bool cheia(HEAP* heap);
bool vazia(HEAP* heap);
bool inserir_heap(HEAP* heap, paciente_h* paciente, int prioridade);
void subir_no_heap(HEAP* heap, int indice);
NOH_HEAP remover_heap(HEAP* heap);
void descer_no_heap(HEAP* heap, int indice);
void liberar_heap(HEAP* heap);
HEAP* copiar_heap(HEAP* heap);
void imprimir_ordenado(HEAP* heap);
bool buscar_heap(HEAP* heap, int id);

#endif