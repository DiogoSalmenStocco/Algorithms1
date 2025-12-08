#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Heap.h"
#include "../ListaSistema/Lista.h"

HEAP* criar_heap() {
    HEAP* heap = (HEAP*)malloc(sizeof(HEAP));
    heap->tam_max = tam_max_heap;
    heap->tam_atual = 0;
    heap->pacienteH = (NOH_HEAP*)malloc(tam_max_heap * sizeof(NOH_HEAP));
    if(heap->pacienteH == NULL || heap == NULL) {
        free(heap->pacienteH);
        free(heap);
        return NULL;
    }
    return heap;
}

bool cheia(HEAP* heap) {
    return heap->tam_atual == heap->tam_max;
}
bool vazia(HEAP* heap) {
    return heap->tam_atual == 0;
}

void subir_no_heap(HEAP* heap, int indice) {
    while (indice > 0) {
        int pai = (indice - 1) / 2;
        if (heap->pacienteH[indice].prioridade <= heap->pacienteH[pai].prioridade) {
            break;
        }
        NOH_HEAP temp = heap->pacienteH[indice];
        heap->pacienteH[indice] = heap->pacienteH[pai];
        heap->pacienteH[pai] = temp;
        indice = pai;
    }
}

bool inserir_heap(HEAP* heap, paciente_h* paciente, int prioridade) {
    if (cheia(heap)) {
        printf("Heap cheia! Nao e possivel inserir novo paciente.\n");
        return false;
    }
    NOH_HEAP novo_no;
    novo_no.paciente = paciente;
    novo_no.prioridade = prioridade;
    heap->pacienteH[heap->tam_atual] = novo_no;
    subir_no_heap(heap, heap->tam_atual);
    heap->tam_atual++;
    return true;
}

NOH_HEAP remover_heap(HEAP* heap) {
    if (vazia(heap)) {
        printf("Heap vazia! Nao e possivel remover paciente.\n");
        exit(EXIT_FAILURE);
    }
    NOH_HEAP raiz = heap->pacienteH[0];
    heap->tam_atual--;
    heap->pacienteH[0] = heap->pacienteH[heap->tam_atual];
    descer_no_heap(heap, 0);
    return raiz;
}

void descer_no_heap(HEAP* heap, int indice) {
    while (true) {
        int esquerda = 2 * indice + 1;
        int direita = 2 * indice + 2;
        int maior = indice;

        if (esquerda < heap->tam_atual && heap->pacienteH[esquerda].prioridade > heap->pacienteH[maior].prioridade) {
            maior = esquerda;
        }
        if (direita < heap->tam_atual && heap->pacienteH[direita].prioridade > heap->pacienteH[maior].prioridade) {
            maior = direita;
        }
        if (maior == indice) {
            break;
        }
        NOH_HEAP temp = heap->pacienteH[indice];
        heap->pacienteH[indice] = heap->pacienteH[maior];
        heap->pacienteH[maior] = temp;
        indice = maior;
    }
}

void liberar_heap(HEAP* heap) {
    free(heap->pacienteH);
    free(heap);
}

HEAP* copia_heap(HEAP* original) {
    HEAP* copia = criar_heap();
    if (copia == NULL) {
        return NULL;
    }
    copia->tam_atual = original->tam_atual;
    for (int i = 0; i < original->tam_atual; i++) {
        copia->pacienteH[i] = original->pacienteH[i];
    }
    return copia;
}

void imprimir_ordenado(HEAP* heap) {
    HEAP* copia = copia_heap(heap);
    if (copia == NULL) {
        printf("Erro ao copiar o heap para impressao.\n");
        return;
    }
    printf("Pacientes na fila de espera (ordenados por prioridade):\n");
    while (!vazia(copia)) {
        NOH_HEAP paciente_no = remover_heap(copia);
        printf("Nome: %s, Prioridade: %d\n", paciente_no.paciente->nome, paciente_no.prioridade);
    }
    liberar_heap(copia);
}

bool buscar_heap(HEAP* heap, int id){
    for(int i = 0; i < heap->tam_atual; i++){
        if(heap->pacienteH[i].paciente->id == id){
            return true;
        }
    }
    return false;
}