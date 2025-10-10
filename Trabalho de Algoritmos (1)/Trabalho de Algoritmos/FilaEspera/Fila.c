#include "Fila.h"
#include <stdio.h>
#include <stdlib.h>

Fila criar_Fila()
{
    Fila fila;
    fila.tamanho = 0;
    fila.capacidade = 50;
    fila.inicio = -1;
    fila.fim = 0;
    return fila;
}

bool Fila_vazia(Fila f) {
    printf("\nFila vazia!!\n");
    return (f.tamanho == 0);
}

bool Fila_cheia(Fila f) {
    printf("\nFila cheia!!\n");
    return (f.tamanho == f.capacidade);
} 

void inserir_paciente_f(Fila* fila, paciente_f p)
{
    if (Fila_cheia(*fila))
        return;
    

    fila->fim = (fila->fim +1) % fila->capacidade;
    fila->paciente[fila->fim] = p;
    fila->tamanho++;
    
    printf("\nPaciente %s com ID %d inserido na Fila de emergência.\n", p.nome, p.id);  
    return;
}

paciente_f remover_paciente_f(Fila* fila) // Retorna o paciente removido
{
    paciente_f paciente_removido = {-1, ""}; // Struct de erro
    
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

    paciente_f paciente_erro = {-1, ""};
    printf("Paciente não encontrado");
    return paciente_erro;
}

void mostrar_todos_f(Fila* fila)
{
    for (int i = 0, ind=fila->inicio; i < fila->tamanho; i++, ind=(ind+1)%fila->capacidade)
		printf("%d \n", fila->paciente[ind].nome);

	printf("\n");
    return;
}