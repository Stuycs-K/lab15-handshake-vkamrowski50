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

int server_handshake_half(int *to_client,int from_client) {
  char private_pipe[HANDSHAKE_BUFFER_SIZE];

  printf("Server Step 5: Reading SYN\n");
  if(read(from_client,private_pipe,HANDSHAKE_BUFFER_SIZE)==-1){
    perror("Server: Error reading SYN\n");
    exit(1);
  }
  printf("Server received PP: %s\n",private_pipe);

  printf("Server Step 6: Opening PP\n");
  *to_client = open(private_pipe,O_WRONLY);
  if(*to_client==-1){
    perror("Server: Error opening PP\n");
    exit(1);
  }

  char syn_ack[] = "SYN_ACK";
  printf("Server Step 7: Sending SYN_ACK\n");
  if(write(*to_client,syn_ack,sizeof(syn_ack))==-1){
    perror("Server: Error sending SYN_ACK\n");
    exit(1);
  }

  char final_ack[HANDSHAKE_BUFFER_SIZE];
  printf("Server Step 9: Reading final ACK\n");
  if(read(from_client,final_ack,HANDSHAKE_BUFFER_SIZE)==-1){
    perror("Server: Error reading final ACK\n");
    exit(1);
  }
  printf("Server: Handshake complete. Final ACK: %s\n",final_ack);


  return from_client;
}

int main() {
  int to_client;
  int from_client;
  signal(SIGINT, sighandler);
  signal(SIGPIPE,SIG_IGN);
  srand(time(NULL));
  while(1){
    printf("Server: Waiting for client\n");
  from_client = server_setup();
  printf("Server: Client connected, forking a subserver\n");
  pid_t pid = fork();
  if(pid==0){
    to_client = 0;
    from_client = server_handshake_half(&to_client,from_client);
    printf("Communication with client %d started\n",getpid());
  
  while(1){
  int randnum = rand()%101;
  if(write(to_client,&randnum,sizeof(randnum))==-1){
    perror("Server: Client disconnected\n");
    break;
  }
  sleep(1);
  }
  close(to_client);
  close(from_client);
  exit(0);
  }
  else if (pid>0){
    close(from_client);
  }
  else{
    perror("Server forking error\n");
    exit(1);
  }
}
}
