#include "IO1.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool SAVE(Lista* lista , historico* pilha, Fila* fila){
    FILE *file_lista, file_fila;
    file_lista = fopen("registros.txt", "w");
    if(file_lista == NULL){
        printf("Erro ao abrir o arquivo dos registros!");
        return false;
    }

    //Salvando a lista de pacientes
    paciente_h* atual = lista->inicio;
    #include "IO1.h"

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    // Save Lista (pacientes), historico (pilha) and Fila to text files.
    bool SAVE(Lista* lista , historico* pilha, Fila* fila){
        if (!lista) return false;

        FILE *file_lista = fopen("registros.txt", "w");
        if(file_lista == NULL){
            printf("Erro ao abrir o arquivo dos registros!\n");
            return false;
        }

        // Salvando a lista de pacientes
        paciente_h* atual = lista->inicio;
        while(atual != NULL){
            fprintf(file_lista, "Paciente:%s\nID:%d\n", atual->nome ? atual->nome : "", atual->id);
            // If the patient has a historico pointer, save their history to a per-patient file
            if (atual->h) {
                char filename[256];
                sprintf(filename, "historico_%d.txt", atual->id);
                FILE *hf = fopen(filename, "w");
                if (hf) {
                    for (int i = 0; i <= atual->h->topo; i++) {
                        fprintf(hf, "%s\n", atual->h->procedimento[i]);
                    }
                    fclose(hf);
                }
            }
            atual = atual->prox;
        }
        fclose(file_lista);

        // Salvando a pilha de historico (if provided, write a generic dump)
        if (pilha) {
            FILE *file_hist = fopen("pilha_historico.txt", "w");
            if (file_hist) {
                for (int i = 0; i <= pilha->topo; i++) {
                    fprintf(file_hist, "%s\n", pilha->procedimento[i]);
                }
                fclose(file_hist);
            }
        }

        // Salvando a fila de espera
        if (fila) {
            FILE *file_fila = fopen("fila_espera.txt", "w");
            if (file_fila) {
                for(int i = 0; i < fila->tamanho; i++){
                    int index = (fila->inicio + i) % fila->capacidade;
                    // fila stores paciente_f by value
                    fprintf(file_fila, "F,%s,%d\n", fila->paciente[index].nome ? fila->paciente[index].nome : "", fila->paciente[index].id);
                }
                fclose(file_fila);
            }
        }

        return true;
    }