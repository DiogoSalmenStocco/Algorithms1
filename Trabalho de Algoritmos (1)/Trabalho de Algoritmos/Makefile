all: Fila.o Lista.o Pilha_hist.o atendimento.o
	gcc Fila.o Lista.o Pilha_hist.o atendimento.o -o at

Fila.o:
	gcc -c Fila.o

Lista.o:
	gcc -c Lista.o

Pilha_hist.o:
	gcc -c Pilha_hist.o

atendimento.o:
	gcc -c atendimento.o

run:
	./at

clean:
	rm *.o
	rm at