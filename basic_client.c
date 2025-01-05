#include "pipe_networking.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int to_server;
    int from_server;
    from_server = client_handshake(&to_server);
    while (1) {
        int randnum;
        int bytesread = read(from_server, &randnum, sizeof(randnum));

        if (bytesread == -1) {
            perror("Client: Error reading random number");
            break;
        } 
        else if (bytesread == 0) {
            printf("Client: Server disconnected.\n");
            break;
        }
        printf("Client: Received random number: %d\n", randnum);
    }

    close(to_server);
    close(from_server);
}