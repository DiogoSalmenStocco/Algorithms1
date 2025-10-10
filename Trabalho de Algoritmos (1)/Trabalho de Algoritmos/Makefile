# O nome do executavel final
TARGET = at

# Arquivos objeto que serao gerados
OBJS = Fila.o Lista.o Pilha_hist.o atendimento.o IO1.o

# Compilador
CC = gcc
CFLAGS = -Wall -g -std=c11

# Caminhos base (Ajuste se o caminho for diferente)
BASE_DIR = Trabalho\ de\ Algoritmos\ \(1\)/Trabalho\ de\ Algoritmos

# Regra principal: compilar todos os objetos e linkar
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Regras de Compilacao para cada arquivo objeto (.c -> .o)
# Uso de $< (primeiro pre-requisito) e $@ (nome do alvo)
Fila.o: $(BASE_DIR)/FilaEspera/Fila.c
	$(CC) $(CFLAGS) -c $< -o $@

Lista.o: $(BASE_DIR)/ListaSistema/Lista.c
	$(CC) $(CFLAGS) -c $< -o $@

Pilha_hist.o: $(BASE_DIR)/ListaSistema/Historico/Pilha_hist.c
	$(CC) $(CFLAGS) -c $< -o $@

atendimento.o: $(BASE_DIR)/atendimento.c
	$(CC) $(CFLAGS) -c $< -o $@

IO1.o: $(BASE_DIR)/SaveLoad/IO1.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para executar
run: $(TARGET)
	./$(TARGET)

# Regra para limpar
clean:
	rm -f $(OBJS) $(TARGET) registros.txt fila_espera.txt historico_*.txt