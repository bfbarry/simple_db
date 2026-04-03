#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>

#define PORT 2345
#define BUFFER_SIZE 1024
#define FILENAME "A"
void error(const char *msg) {
    perror(msg);
    exit(1);
}

char* read_table(const char* tablename, long *file_size) {
    FILE* file = fopen(tablename, "rb");
    if (file == NULL) {
        return NULL;
    }

    //get file size
    fseek(file, 0, SEEK_END);
    *file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // memory for file content
    char* buffer = (char*)malloc(*file_size + 1);
    if (buffer == NULL) {
        fclose(file);
        return NULL;
    }

    // read f
    fread(buffer, 1, *file_size, file);
    buffer[*file_size] = '\0';

    fclose(file);
    return buffer;
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address, cli_address;
    int opt = 1;
    int addrlen = sizeof(address);
    int cli_addrlen = sizeof(cli_address);
    char buffer[BUFFER_SIZE] = {0};

    //socket file descripter
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    error("Socket creation failed");
    }

    //reuse address //and port
    int err = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (err) {
        error("setsockopt failed");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        error("Bind failed");
    }

    if (listen(server_fd, 5) < 0) {
        error("Listen failed");
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
       if ((client_fd = accept(server_fd, (struct sockaddr*)&cli_address, (socklen_t*)&cli_addrlen)) < 0) {
            error("accept failed.");
        }
    
        printf("Client connected: %s:%d\n", inet_ntoa(cli_address.sin_addr), ntohs(cli_address.sin_port));

        //read client message
        int valread = read(client_fd, buffer, BUFFER_SIZE);
        printf("Received: %s\n", buffer);
        //read file to send
        long fsize;
        char* file_content = read_table(FILENAME, &fsize);

        if (file_content == NULL) {
            const char* error_msg = "Error: could not read file";
            send(client_fd, error_msg, strlen(error_msg), 0);
        } else {
            send(client_fd, file_content, fsize, 0);
            free(file_content);
        }

        //close client
        close(client_fd);
        memset(buffer, 0 , BUFFER_SIZE);
    }

    close(server_fd);
    return 0;
}


//echo "ping" | nc localhost 2345





















