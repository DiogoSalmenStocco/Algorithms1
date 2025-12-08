#include "IO1.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Salva a lista de pacientes (registros.txt) e o heap de espera (fila_espera.txt)
bool SAVE(Lista* lista , historico* pilha, HEAP* fila){
    if (!lista) return false;

    // 1. Salvando a Lista de Pacientes (Sistema Principal)
    // ... (Lógica inalterada para Lista) ...
    FILE *file_lista = fopen("registros.txt", "w");
    if(file_lista == NULL){
        printf("Erro ao abrir o arquivo registros.txt para salvar!\n");
        return false;
    }

    paciente_h* atual = lista->inicio;
    while(atual != NULL){
        fprintf(file_lista, "PACIENTE,%d,%s\n", atual->id, atual->nome ? atual->nome : "");
        
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

    // 2. Salvando a Fila de Espera (HEAP)
    if (fila) {
        FILE *file_fila = fopen("fila_espera.txt", "w");
        if (file_fila) {
            for(int i = 0; i < fila->tam_atual; i++){
                // Salva ID, PRIORIDADE e Nome dos pacientes no array interno do Heap
                fprintf(file_fila, "FILA,%d,%d,%s\n", 
                        fila->pacienteH[i].paciente->id, 
                        fila->pacienteH[i].prioridade,
                        fila->pacienteH[i].paciente->nome ? fila->pacienteH[i].paciente->nome : "");
            }
            fclose(file_fila);
        }
    }

    return true;
}

// Carrega os dados salvos nos arquivos para as estruturas de dados
bool LOAD(Lista* lista , historico* pilha, HEAP* fila){
    
    // 1. Carregando a Lista de Pacientes (Sistema Principal)
    // ... (Lógica inalterada para Lista) ...
    FILE *file_lista = fopen("registros.txt", "r");
    if(file_lista == NULL){
        printf("Aviso: Arquivo registros.txt nao encontrado. Iniciando com lista vazia.\n");
        return false;
    }

    char linha[256];
    char tipo[10], nome[100];
    int id;

    while (fgets(linha, sizeof(linha), file_lista)) {
        if (sscanf(linha, "%9[^,],%d,%99[^\n]", tipo, &id, nome) == 3) {
            if (strcmp(tipo, "PACIENTE") == 0) {
                bool inserido = inserir_paciente_fim(lista, nome, id);
                
                if (inserido) {
                    paciente_h* p = lista->fim; 
                    if (p && p->h) {
                        historico* hist_carregado = abrir_historico(id);
                        if (hist_carregado) {
                            memcpy(p->h->procedimento, hist_carregado->procedimento, sizeof(p->h->procedimento));
                            p->h->topo = hist_carregado->topo;
                            free(hist_carregado);
                        }
                    }
                }
            }
        }
    }
    fclose(file_lista);

    // 2. Carregando a Fila de Espera (HEAP)
    if (fila) {
        FILE *file_fila = fopen("fila_espera.txt", "r");
        if (file_fila) {
            while (fgets(linha, sizeof(linha), file_fila)) {
                int id, prio;
                char nome_p[100]; // Buffer temporario para o nome (corrigido)
                
                // CORREÇÃO: sscanf deve ler 3 campos: ID, PRIORIDADE e NOME
                if (sscanf(linha, "FILA,%d,%d,%99[^\n]", &id, &prio, nome_p) == 3) {
                    
                    // Cria o nó paciente_h que será inserido no Heap
                    paciente_h* p_node = (paciente_h*)malloc(sizeof(paciente_h));
                    if (p_node == NULL) continue;
                    
                    p_node->id = id;
                    p_node->nome = strdup(nome_p); // Aloca e copia
                    if (p_node->nome == NULL) { free(p_node); continue; }
                    
                    // Inicializa os campos restantes (necessário para ser um paciente_h válido)
                    p_node->prox = NULL;
                    p_node->h = criar_historico(); 

                    // Insere no heap
                    inserir_heap(fila, p_node, prio); 
                }
            }
            fclose(file_fila);
        } else {
            printf("Aviso: Arquivo fila_espera.txt nao encontrado. Iniciando com fila vazia.\n");
        }
    }
    
    return true;
}