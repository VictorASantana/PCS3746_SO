#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <deque>
#include "so.h"

#define PORT 8080
#define MAX_BUFFER 1024

WINDOW *create_newwin(int, int, int, int);
void printStatusWin(WINDOW*, TCB*);
void printTCBWin(WINDOW*, TCB*);
void printBitMapWin(WINDOW*, int*);
void printReadyLine(WINDOW*, deque<TCB*>);
void printAlgorithm(WINDOW*, bool);

int main()
{
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr, newAddr;
    socklen_t addrSize;
    OperatingSystem so;

    // Criação do socket servidor
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cerr << "Erro na criação do socket." << std::endl;
        return 1;
    }

    // Configuração do endereço do servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Associa o socket ao endereço e porta
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "Erro na associação do socket." << std::endl;
        return 1;
    }

    // O servidor está escutando conexões
    if (listen(serverSocket, 5) == -1)
    {
        std::cerr << "Erro ao escutar por conexões." << std::endl;
        return 1;
    }

    addrSize = sizeof(newAddr);

    // Aguarda a conexão do cliente
    newSocket = accept(serverSocket, (struct sockaddr *)&newAddr, &addrSize);

    string alg = "rr";

    // Loop principal, trata os comandos e aciona a classe OperatingSystem
    while (true)
    {
        char buffer[MAX_BUFFER] = "";
        memset(buffer, 0, sizeof(buffer));

        // Recebe a mensagem do cliente
        string op, pid;
        int umem, pc;

        op = pid = "";
        umem = pc = 0;

        recv(newSocket, buffer, sizeof(buffer), 0);

        for (int i = 0; i < MAX_BUFFER; i++)
        {
            if (buffer[i] == ' ' || buffer[i] == '\0')
            {
                if (op == "create")
                {
                    umem = int(buffer[(i + 4)]) - int('0');
                    so.addProcess(umem, 1);
                }

                else if (op == "kill")
                {
                    for (int j = i + 1; buffer[j] != '\0'; j++)
                        pid.push_back(buffer[j]);

                    so.addProcess(stoi(pid), 2);
                }

                else if (op == "run")
                {
                    pc = so.runCycle();
                }
                    

                else if (op == "set")
                {
                    alg = "";

                    for (int j = i + 1; buffer[j] != '\0'; j++)
                        alg.push_back(buffer[j]);

                    so.setAlgorithm(alg);
                }

                break;
            }
            else
                op.push_back(buffer[i]);
        }

        if (strcmp(buffer, "exit") == 0)
            break;

        // Lógica da interface
        int startx = 0;
        int starty = 0;
        int ch;

        initscr();
        cbreak();
        keypad(stdscr, TRUE);
        noecho();
        curs_set(false);

        int i = 0;

        WINDOW *status_win = create_newwin(10, 30, 0, 0);
        WINDOW *tcb_win = create_newwin(10, 20, 0, 25);
        WINDOW *bitMap_win = create_newwin(10, 30, 0, 50);
        WINDOW *readyLine_win = create_newwin(5, 80, 10, 0);
        WINDOW *algorithm_win = create_newwin(10, 80, 15, 0);

        TCB *t = so.getRunning();
        int *bitMap = so.getBitMapState();
        deque<TCB *> sched = so.getScheduler();
        bool algorithm = so.getAlgorithm();

        printStatusWin(status_win, t);
        printTCBWin(tcb_win, t);
        printBitMapWin(bitMap_win, bitMap);
        printReadyLine(readyLine_win, sched);
        printAlgorithm(algorithm_win, algorithm);

        i++;

        sleep(1);

        delwin(status_win);
        delwin(tcb_win);
        delwin(bitMap_win);
        delwin(readyLine_win);

        // Envia uma resposta de volta ao cliente (opcional)
        char res[MAX_BUFFER] = "Mensagem recebida pelo servidor";
        send(newSocket, res, strlen(res), 0);

        // Termina a execução se a mensagem for "exit"
        if (strcmp(buffer, "exit") == 0)
            break;
    }

    endwin();
    close(newSocket);
    close(serverSocket);
    return 0;
}

void printStatusWin(WINDOW *local_win, TCB *t)
{
    wprintw(local_win, "STATUS\n\n");
    if (t != NULL)
    {
        Process *process = t->getProcess();
        if (process != NULL)
        {
            if (process->getType() == 0)
            {
                vector<string> instructions = process->getInstructions();
                for (int i = 0; i < instructions.size(); i++)
                {
                    wprintw(local_win, "%s ", instructions[i].c_str());

                    if (process->getPC() == i)
                        wprintw(local_win, "<-");

                    wprintw(local_win, "\n");
                }
            }
        }
    }
    wrefresh(local_win);
}

void printTCBWin(WINDOW *local_win, TCB *tcb)
{
    wprintw(local_win, "TCB\n\n");

    if (tcb != NULL)
    {
        wprintw(local_win, "PID: %d\n", tcb->getProcess()->getID());
        wprintw(local_win, "PC: %d\n", tcb->getProcess()->getPC());
        wprintw(local_win, "........\n");
    }
    wrefresh(local_win);
}

void printBitMapWin(WINDOW *local_win, int *bitMap)
{
    wprintw(local_win, "MAPA DE BITS\n\n");
    if (bitMap != NULL)
    {
        for (int i = 0; i < 20; i++)
        {
            if (i % 5 == 0 && i != 0)
                wprintw(local_win, "\n");

            int n = (int)rand() % 2;
            wprintw(local_win, "%d ", bitMap[i]);
        }
    }
    wrefresh(local_win);
}

void printReadyLine(WINDOW *local_win, deque<TCB *> sched)
{
    if (sched[0] != NULL)
    {
        wprintw(local_win, "\nFILA DE PRONTOS\n\n");
        wprintw(local_win, "| ");
        for (int i = 0; i < sched.size(); i++)
        {
            int pid = sched[i]->getProcess()->getID();
            int type = sched[i]->getProcess()->getType();
            int memblock = sched[i]->getProcess()->getMemoryBlock();

            if (type == 1)
                wprintw(local_win, "CREATE %d | ", memblock);

            else if (type == 2)
                wprintw(local_win, "KILL %d | ", memblock);
                
            else wprintw(local_win, "PID %d | ", pid);
        }
        wprintw(local_win, "\n\n");
    }

    wrefresh(local_win);
}

void printAlgorithm(WINDOW *local_win, bool algorithm)
{
    if (algorithm)
        wprintw(local_win, "\nESCALONAMENTO: ROUND ROBIN\n");

    else wprintw(local_win, "\nESCALONAMENTO: FIFO\n");
    wrefresh(local_win); 
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    return local_win;
}
