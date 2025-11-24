# O nome do executavel final
TARGET = at

# Arquivos objeto que serao gerados
OBJS = Fila.o Lista.o Pilha_hist.o atendimento.o IO1.o

# Compilador
CC = gcc
CFLAGS = -Wall -g -std=c11

# REMOVIDO: A variável BASE_DIR não é mais necessária

# Regra principal: compilar todos os objetos e linkar
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Regras de Compilacao para cada arquivo objeto (.c -> .o)
# Os caminhos agora sao relativos a este diretorio (Trabalho de Algoritmos)

Fila.o: FilaEspera/Fila.c
	$(CC) $(CFLAGS) -c $< -o $@

Lista.o: ListaSistema/Lista.c
	$(CC) $(CFLAGS) -c $< -o $@

Pilha_hist.o: ListaSistema/Historico/Pilha_hist.c
	$(CC) $(CFLAGS) -c $< -o $@

atendimento.o: atendimento.c
	$(CC) $(CFLAGS) -c $< -o $@

IO1.o: SaveLoad/IO1.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para executar
run: $(TARGET)
	./$(TARGET)

# Regra para limpar
clean:
	del Fila.o Lista.o Pilha_hist.o atendimento.o IO1.o $(TARGET) registros.txt fila_espera.txt historico_*.txt