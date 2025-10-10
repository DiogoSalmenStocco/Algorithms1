#include "IO1.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Salva a lista de pacientes (registros.txt) e a fila de espera (fila_espera.txt)
bool SAVE(Lista* lista , historico* pilha, Fila* fila){
    if (!lista) return false;

    // 1. Salvando a Lista de Pacientes (Sistema Principal)
    FILE *file_lista = fopen("registros.txt", "w");
    if(file_lista == NULL){
        printf("Erro ao abrir o arquivo registros.txt para salvar!\n");
        return false;
    }

    paciente_h* atual = lista->inicio;
    while(atual != NULL){
        // Salva ID, Nome e TIPO (para diferenciar de outros dados)
        fprintf(file_lista, "PACIENTE,%d,%s\n", atual->id, atual->nome ? atual->nome : "");
        
        // Salva o historico em um arquivo por paciente
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

    // 2. Salvando a Fila de Espera
    if (fila) {
        FILE *file_fila = fopen("fila_espera.txt", "w");
        if (file_fila) {
            for(int i = 0; i < fila->tamanho; i++){
                int index = (fila->inicio + i) % fila->capacidade;
                // Salva ID e Nome dos pacientes na fila
                fprintf(file_fila, "FILA,%d,%s\n", fila->paciente[index].id, fila->paciente[index].nome ? fila->paciente[index].nome : "");
            }
            fclose(file_fila);
        }
    }

    return true;
}

// Carrega os dados salvos nos arquivos para as estruturas de dados
bool LOAD(Lista* lista , historico* pilha, Fila* fila){
    
    // 1. Carregando a Lista de Pacientes (Sistema Principal)
    FILE *file_lista = fopen("registros.txt", "r");
    if(file_lista == NULL){
        printf("Aviso: Arquivo registros.txt nao encontrado. Iniciando com lista vazia.\n");
        return false;
    }

    char linha[256];
    char tipo[10], nome[100];
    int id;

    // Le linha por linha (PACIENTE,ID,NOME)
    while (fgets(linha, sizeof(linha), file_lista)) {
        // Usa sscanf para extrair os campos
        if (sscanf(linha, "%9[^,],%d,%99[^\n]", tipo, &id, nome) == 3) {
            if (strcmp(tipo, "PACIENTE") == 0) {
                // Insere o paciente na lista principal (assume que a insercao no final e mais rapida)
                bool inserido = inserir_paciente_fim(lista, nome, id);
                
                if (inserido) {
                    // Carrega o historico do paciente recem-criado
                    paciente_h* p = lista->fim; // O ultimo no inserido e o paciente
                    if (p && p->h) {
                        // Abrir_historico ira criar um novo historico temporario
                        historico* hist_carregado = abrir_historico(id);
                        if (hist_carregado) {
                            // Copia os dados da pilha carregada para a pilha do paciente na lista
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

    // 2. Carregando a Fila de Espera
    if (fila) {
        FILE *file_fila = fopen("fila_espera.txt", "r");
        if (file_fila) {
            while (fgets(linha, sizeof(linha), file_fila)) {
                // Le linha por linha (FILA,ID,NOME)
                if (sscanf(linha, "FILA,%d,%99[^\n]", &id, nome) == 2) {
                    
                    paciente_f p;
                    p.id = id;
                    // Aloca e copia o nome
                    p.nome = strdup(nome); 
                    if (p.nome == NULL) continue;
                    
                    // Insere na fila de espera
                    inserir_paciente_f(fila, p); 
                }
            }
            fclose(file_fila);
        } else {
            printf("Aviso: Arquivo fila_espera.txt nao encontrado. Iniciando com fila vazia.\n");
        }
    }
    
    return true;
}