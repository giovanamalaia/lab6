#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_CLIENT_TO_SERVER "client_to_server_fifo"
#define FIFO_SERVER_TO_CLIENT "server_to_client_fifo"
#define BUFFER_SIZE 256

void to_uppercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    char buffer[BUFFER_SIZE];
    int client_to_server_fd, server_to_client_fd;

    // Criar as FIFOs com permissões de leitura e escrita apenas para o dono
    mkfifo(FIFO_CLIENT_TO_SERVER, S_IRUSR | S_IWUSR);
    mkfifo(FIFO_SERVER_TO_CLIENT, S_IRUSR | S_IWUSR);

    printf("Servidor rodando em background...\n");

    while (1) {
        // Abrir FIFO para leitura
        client_to_server_fd = open(FIFO_CLIENT_TO_SERVER, O_RDONLY);
        read(client_to_server_fd, buffer, BUFFER_SIZE);
        close(client_to_server_fd);

        // Transformar a string recebida para maiúsculas
        to_uppercase(buffer);

        // Abrir FIFO para escrever de volta a resposta
        server_to_client_fd = open(FIFO_SERVER_TO_CLIENT, O_WRONLY);
        write(server_to_client_fd, buffer, strlen(buffer) + 1); // +1 para incluir o '\0'
        close(server_to_client_fd);
    }

    return 0;
}
