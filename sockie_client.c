#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;

    char *client_buf = malloc(1024);

    socklen_t addr_size = sizeof(server_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) == -1) {
        printf("invalid addr\n");
        return -1;
    }  // specify ip of the server. this case:
       // localhost or 127.0.0.1

    if (connect(clientfd, (struct sockaddr *)&server_addr, addr_size) == -1) {
        printf("couldn't connect to server :c\n");
        return -1;
    }

    // ask for input and once entered, do control flow to gather further user
    // input

    char *exit_phrase = "exit()";

    while (strcmp(client_buf, exit_phrase) != 0) {
        scanf("%s", client_buf);
        send(clientfd, client_buf, strlen(client_buf), 0);
    }
}
