#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "../process/process.h"

#define PORT 8080

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024];

    // Criar o socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Erro na criaÃ§Ã£o do socket" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convertendo endereÃ§o IPv4 e IPv6 do texto para binÃ¡rio
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "EndereÃ§o invÃ¡lido / EndereÃ§o nÃ£o suportado" << std::endl;
        return -1;
    }

    // Conectar ao servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "ConexÃ£o falhou" << std::endl;
        return -1;
    }
    while (true)
    {
        std::cout << "Digite uma mensagem: ";
        std::cin.getline(buffer, sizeof(buffer));

        // Envia a mensagem para o servidor
        send(sock, buffer, strlen(buffer), 0);

        // Termina a execução se a mensagem for "exit"
        if (strcmp(buffer, "exit") == 0)
            break;
    }

    close(sock);

    return 0;
}
