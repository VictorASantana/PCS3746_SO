#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "so.h"

#define PORT 8080
#define MAX_BUFFER 1024

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



    // Loop principal, trata os comandos e aciona a classe OperatingSystem
    while (true)
    {
        char buffer[MAX_BUFFER] = "";

        // Recebe a mensagem do cliente
        string op, pid;
        int umem, pc;
        
        op = pid = "";
        umem = pc = 0;

        recv(newSocket, buffer, sizeof(buffer), 0);

        for (int i = 0; i < MAX_BUFFER; i++)
        {
            if (buffer[i] == ' ' || buffer[i] == '\0' )
            {
                if (op == "create")
                {
                    umem = int(buffer[(i+4)]) - int('0');
                    so.createProcess(umem);
                }
                
                else if (op == "kill")
                {
                    for (int j = i + 1; buffer[j] != '\0'; j++)
                    {
                        pid.push_back(buffer[j]);
                        so.killProcess(stoi(pid));
                    }
                }

                else if (op == "run")
                    pc = so.runCycle();

                break;

            } else op.push_back(buffer[i]);
        }

        // Mostra a mensagem recebida
        std::cout << "Mensagem recebida: " << buffer << endl;
        std::cout << "Operation: " << op << endl;
        std::cout << "Memory blocks: " << umem << endl;
        std::cout << "Process ID: " << pid << endl;
        std::cout << "Process PC: " << pc << endl << endl;

        // Envia uma resposta de volta ao cliente (opcional)
        char res[MAX_BUFFER] = "Mensagem recebida pelo servidor";
        send(newSocket, res, strlen(res), 0);

        // Termina a execução se a mensagem for "exit"
        if (strcmp(buffer, "exit") == 0) break;
    }



    close(newSocket);
    close(serverSocket);
    return 0;
}
