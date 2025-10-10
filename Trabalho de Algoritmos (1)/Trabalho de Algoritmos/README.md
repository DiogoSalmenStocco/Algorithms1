# Sistema de Gerenciamento de Atendimento Hospitalar

Este projeto implementa um sistema básico de gerenciamento de pacientes e atendimentos utilizando estruturas de dados fundamentais (Lista Encadeada para cadastro principal, Fila Circular para espera e Pilha para histórico de procedimentos).

# Integrantes

Lista n°usp:
Danilo de Oliveira Lopes- 17086598
Diogo Salmen Stocco - 16906441

## Estruturas de Dados Utilizadas:
* **Lista Encadeada (`Lista.c`):** Utilizada como registro principal de pacientes.
* **Fila Circular (`Fila.c`):** Utilizada para gerenciar a ordem de espera dos pacientes.
* **Pilha (`Pilha_hist.c`):** Utilizada para registrar e desfazer procedimentos no histórico médico de cada paciente.

## Requisitos de Compilação

Para compilar e executar este projeto, você precisará de:
1.  Um **Compilador C** (preferencialmente **GCC**).
2.  A ferramenta **Make** (GNU Make).

### 1.1. Configuração no Windows

No Windows, a maneira mais fácil de compilar este código é usando:
* **WSL (Windows Subsystem for Linux):** É a opção mais recomendada, pois oferece um ambiente Linux nativo onde o `make` e o `gcc` funcionam perfeitamente.
* **MinGW / TDM-GCC:** Ferramentas que adicionam o `gcc` e `make` ao prompt de comando do Windows.

Certifique-se de que o `gcc` e o `make` estão instalados e acessíveis no seu terminal.

### 1.2. Configuração no Linux (ou WSL)

No Linux (ou WSL), instale as ferramentas essenciais de desenvolvimento (se ainda não o fez):

```bash
sudo apt update
sudo apt install build-essential

# Simulação do terminal:
$ make

# Saída de Compilação (simulada)

# Compilando Fila.c
gcc -Wall -g -std=c11 -c Trabalho\ de\ Algoritmos\ \(1\)/Trabalho\ de\ Algoritmos/FilaEspera/Fila.c -o Fila.o

# Compilando Lista.c
gcc -Wall -g -std=c11 -c Trabalho\ de\ Algoritmos\ \(1\)/Trabalho\ de\ Algoritmos/ListaSistema/Lista.c -o Lista.o

# Compilando Pilha_hist.c
gcc -Wall -g -std=c11 -c Trabalho\ de\ Algoritmos\ \(1\)/Trabalho\ de\ Algoritmos/ListaSistema/Historico/Pilha_hist.c -o Pilha_hist.o

# Compilando atendimento.c
gcc -Wall -g -std=c11 -c Trabalho\ de\ Algoritmos\ \(1\)/Trabalho\ de\ Algoritmos/atendimento.c -o atendimento.o

# Compilando IO1.c (Save/Load)
gcc -Wall -g -std=c11 -c Trabalho\ de\ Algoritmos\ \(1\)/Trabalho\ de\ Algoritmos/SaveLoad/IO1.c -o IO1.o

# Linkando e criando o executavel 'at'
gcc -Wall -g -std=c11 Fila.o Lista.o Pilha_hist.o atendimento.o IO1.o -o at

$ make run