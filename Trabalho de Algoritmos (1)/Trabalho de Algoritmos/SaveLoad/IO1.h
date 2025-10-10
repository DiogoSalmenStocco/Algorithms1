#ifndef IO1_H
#define IO1_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../ListaSistema/Lista.h"
#include "../ListaSistema/Historico/Pilha_hist.h"
#include "../FilaEspera/Fila.h"

bool SAVE(Lista* lista , historico* pilha, Fila* fila);
bool LOAD(Lista* lista , historico* pilha, Fila* fila);

#endif // IO1_H