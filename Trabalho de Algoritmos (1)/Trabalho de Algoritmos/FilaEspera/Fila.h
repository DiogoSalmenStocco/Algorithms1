#include <stdbool.h>
// capacidade: tamanho máximo.
// tamanho: quatidade atual de paciente_fs na Fila.
typedef struct paciente{
    char *nome;
    int id;
} paciente_f;

typedef struct Fila_{
    
    paciente_f paciente[50];
    int tamanho; // tamanho atual
    int capacidade; //tamanho max (50)

    int inicio;
    int fim;
} Fila;


Fila criar_Fila();
void inserir_paciente_f(Fila* espera, paciente_f paciente_f);
void remover_paciente_f(Fila* espera, paciente_f paciente_f);
bool Fila_vazia(Fila f);
bool Fila_cheia(Fila f);

paciente_f buscar_paciente_fila(Fila* fila, paciente_f p);
void mostrar_todos_f(Fila* fila);
