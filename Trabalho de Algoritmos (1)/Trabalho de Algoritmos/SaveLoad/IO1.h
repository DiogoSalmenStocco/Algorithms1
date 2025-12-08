#ifndef IO1_H
#define IO1_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // Necessario para LOAD

#include "../ListaSistema/Lista.h"
#include "../ListaSistema/Historico/Pilha_hist.h"
#include "../FilaEspera/heap.h"

// As funcoes serao implementadas no IO1.c
bool SAVE(Lista* lista , historico* pilha, HEAP* fila);
bool LOAD(Lista* lista , historico* pilha, HEAP* fila);

#endif // IO1_H