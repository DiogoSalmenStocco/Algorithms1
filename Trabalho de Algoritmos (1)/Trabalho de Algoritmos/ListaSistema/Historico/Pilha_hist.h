#include <stdbool.h>
#include <stdlib.h>
typedef struct Pilha_hist
{
  char procedimento[10][100];  
  int topo;
}historico;

historico* criar_historico();
historico* abrir_historico(int id);
void consultar_procedimentos(int id);
void inserir_procedimento(historico *h, char procedimento[100], int id);
void desfazer_procedimento(historico *h);
bool historico_vazio(historico *h);
bool historico_cheio(historico *h);
