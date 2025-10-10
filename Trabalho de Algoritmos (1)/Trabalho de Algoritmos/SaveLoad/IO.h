#ifndef IO_H
	#define IO_H
	//#include "item.h"
    #include "fila.h"
    #include "lista.h"
    #include <stdbool.h>

    bool SAVE(Lista *lista, Fila *fila); // Salva os itens da lista e da fila em arquivos
    bool LOAD(Lista **lista, Fila **fila); // Carrega os itens dos arquivos na lista e na fila
	  
#endif
