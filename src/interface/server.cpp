#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "../process/process.h"

const int PORT = 8080;

int main()
{
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr, newAddr;
    socklen_t addrSize;
    char buffer[1024];

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

    while (true)
    {
        buffer = " ";
        // Recebe a mensagem do cliente
        recv(newSocket, buffer, sizeof(buffer), 0);

        // Mostra a mensagem recebida
        std::cout << "Mensagem recebida: " << buffer << std::endl;

        // Envia uma resposta de volta ao cliente (opcional)
        send(newSocket, "Mensagem recebida pelo servidor.", strlen("Mensagem recebida pelo servidor."), 0);

        // Termina a execução se a mensagem for "exit"
        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(newSocket);
    close(serverSocket);
    return 0;
}
