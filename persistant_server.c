#include "pipe_networking.h"

static void sighandler(int signo) {
    if ( signo == SIGINT ){
      printf("Removing WKP\n");
      if(close(WKP)==-1){
        perror("Server: Error removing WKP\n");
        exit(1);
      }
      exit(0);
}
}

int main() {
  int to_client;
  int from_client;
  close(WKP);
  while(1){
    signal(SIGINT, sighandler);
  from_client = server_handshake( &to_client );
  sleep(1);
  close(to_client);
  close(from_client);
}
}
