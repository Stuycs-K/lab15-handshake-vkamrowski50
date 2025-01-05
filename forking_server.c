#include "pipe_networking.h"
#include <signal.h>
#include <time.h>
static void sighandler(int signo) {
    if ( signo == SIGINT ){
      printf("Removing WKP\n");
      if(remove(WKP)==-1){
        perror("Server: Error removing WKP\n");
        exit(1);
      }
      exit(0);
}
}

int main() {
  int to_client;
  int from_client;
  signal(SIGINT, sighandler);
  signal(SIGPIPE,SIG_IGN);
  srand(time(NULL));
  while(1){
  from_client = server_handshake( &to_client );
  while(1){
  int randnum = rand()%101;
  if(write(to_client,&randnum,sizeof(randnum))==-1){
    perror("Server: Client disconnected\n");
    break;
  }
  printf("Server: Sending random number: %d\n",randnum);
  sleep(1);
  }
  close(to_client);
  close(from_client);
}
}
