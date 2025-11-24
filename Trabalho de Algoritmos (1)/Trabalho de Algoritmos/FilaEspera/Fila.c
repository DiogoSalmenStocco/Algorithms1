#include "Fila.h"
#include <stdio.h>
#include <stdlib.h>

Fila criar_Fila()
{
    Fila fila;
    fila.tamanho = 0;
    fila.capacidade = 50;
    fila.inicio = -1; // -1 indica fila vazia
    fila.fim = -1; // CORREÇÃO: FIM deve ser -1 tambem para que o primeiro elemento seja inserido no indice 0
    return fila;
}

bool Fila_vazia(Fila f) {
    return (f.tamanho == 0);
}

bool Fila_cheia(Fila f) {
    return (f.tamanho == f.capacidade);
} 

void inserir_paciente_f(Fila* fila, paciente_f p)
{
    if (Fila_cheia(*fila))
        return;
    
    // CORREÇÃO CRÍTICA: Ajustar o inicio se a fila esta vazia
    if (Fila_vazia(*fila)) {
        fila->inicio = 0;
        fila->fim = 0;
    } else {
        // Logica normal de avanco para fila circular
        fila->fim = (fila->fim + 1) % fila->capacidade;
    }

    fila->paciente[fila->fim] = p;
    fila->tamanho++;
    
    printf("\nPaciente %s com ID %d inserido na Fila de emergência.\n", p.nome, p.id);  
    return;
}

paciente_f remover_paciente_f(Fila* fila) // Retorna o paciente removido
{
    paciente_f paciente_removido = {"", -1}; 
    
    if (Fila_vazia(*fila)) {
        return paciente_removido;
    }
    
    // Pega o paciente no inicio
    paciente_removido = fila->paciente[fila->inicio];
    
    // Atualiza o inicio
    fila->inicio = (fila->inicio + 1) % fila->capacidade;
    fila->tamanho--;

    // Se a fila esvaziou, reseta os indices
    if (fila->tamanho == 0) {
        fila->inicio = -1;
        fila->fim = -1;
    }
    
    printf("\nPaciente %s com ID %d removido da Fila de emergencia para atendimento.\n", paciente_removido.nome, paciente_removido.id);  
    return paciente_removido;
}

paciente_f buscar_paciente_fila(Fila* fila, paciente_f p)
{
    for (int i=0; i < fila->capacidade; i++)
    {
        if (fila->paciente[i].id == p.id)
        {
            return fila->paciente[i];
        }
    }

    paciente_f paciente_erro = {"", -1};
    printf("Paciente não encontrado");
    return paciente_erro;
}

void mostrar_todos_f(Fila* fila)
{
    if (Fila_vazia(*fila)) {
        printf("Fila de espera esta vazia.\n");
        return;
    }
    
    // Percorre do inicio ate o tamanho
    for (int i = 0, ind=fila->inicio; i < fila->tamanho; i++, ind=(ind+1)%fila->capacidade)
		printf("%s \n", fila->paciente[ind].nome);

	printf("\n");
    return;
}