#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_CLIENT_TO_SERVER "client_to_server_fifo"
#define FIFO_SERVER_TO_CLIENT "server_to_client_fifo"
#define BUFFER_SIZE 256

int main() {
    char buffer[BUFFER_SIZE];
    int client_to_server_fd, server_to_client_fd;

    // Entrar com a mensagem
    printf("Digite uma string: ");
    fgets(buffer, BUFFER_SIZE, stdin);

    // Remover o '\n' do final da string
    buffer[strcspn(buffer, "\n")] = '\0';

    // Enviar a mensagem ao servidor
    client_to_server_fd = open(FIFO_CLIENT_TO_SERVER, O_WRONLY);
    write(client_to_server_fd, buffer, strlen(buffer) + 1); // +1 para incluir o '\0'
    close(client_to_server_fd);

    // Esperar a resposta do servidor
    server_to_client_fd = open(FIFO_SERVER_TO_CLIENT, O_RDONLY);
    read(server_to_client_fd, buffer, BUFFER_SIZE);
    close(server_to_client_fd);

    // Exibir a resposta
    printf("Resposta do servidor: %s\n", buffer);

    return 0;
}
