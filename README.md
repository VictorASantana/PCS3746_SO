# Projeto da disciplina PCS3746 - Sistemas Operacionais

Esse projeto representa uma simulação em C++ de um sistema operacional de maneira básica. 
Apresenta como entidades principais Processo, TCB e Memória. Elas se intercomunicam por meio do sistema operacional simulado e seu funcionamento pode ser conferido via prompt de comando. A execução do projeto é abordada posteriormente.
O projeto foi proposto pela disciplina PCS3746 (Sistemas Operacionais), lecionada pelo professor Dr. Artur Jordão Lima Correia.

### Colaboradores
- Lucas Pavan Garieri
- Pedro Henrique Rodrigues de Viveiros
- Sophia Lie Asakura
- Victor de Almeida Santana

### Dependências
- Sistema Operacional: Linux (no caso, foi utilizado o WSL)
- Biblioteca: ncurses (para instalá-la basta rodar o comando `sudo apt-get install libncurses5-dev libncursesw5-dev`)

### Como usar a simulação?

Abaixo estão os comandos a serem usados para a simulação:

`make`
- Deve ser usado somente em terminais Linux e na pasta raiz do projeto
- Executa a interface que será utilizada para acompanhar o andamento da simulação

`make client`
- Deve ser usado somente em terminais Linux e na pasta raiz do projeto
- Deve ser usado somente **após** a execução da instrução `make`
- Executa o terminal que será utilizado para fornecer entradas do usuário à simulação (os comando seguintes devem ser executados nesse terminal)

`create -m X`
- Deve ser executado no terminal criado a partir de `make client`
- Cria um processo que ocupa X posições da memória, sendo X um numéro inteiro de 1 a 20

`kill Y`
- Deve ser executado no terminal criado a partir de `make client`
- Cria um processo cuja responsabilidade é desalocar a memória de um outro processo já existente na memória antes de terminar sua execução
- Y representa o ID de um processo já criado

`set fifo`
- Deve ser executado no terminal criado a partir de `make client`
- Faz com que o algoritmo de preempção seja FIFO, isto é, o processo criado mais antigamente será o primeiro a ser executado

`set rr`
- Deve ser executado no terminal criado a partir de `make client`
- Faz com que o algoritmo de preempção seja Round-Robin, isto é, o processo criado será executado por 4 ciclos e, após esse tempo, será interrompido e inserido ao final da fila de prontos

