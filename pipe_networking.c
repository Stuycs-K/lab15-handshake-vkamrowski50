#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  int from_client;
  printf("Server Step 1: Creating WKP\n");
  if(mkfifo(WKP,0666)==-1){
    perror("Server: Error creating WKP\n");
    exit(1);
  }

  printf("Server Step 2: Opening WKP (BLOCKS)\n");
  from_client = open(WKP, O_RDONLY);
  if(from_client==-1){
    perror("Server: Error opening WKP\n");
    exit(1);
  }

  printf("Server Step 4: Removing WKP\n");
  if(remove(WKP)==-1){
    perror("Server: Error removing WKP\n");
    exit(1);
  }
  return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int from_client = server_setup();
  char private_pipe[HANDSHAKE_BUFFER_SIZE];

  printf("Server Step 5: Reading SYN\n");
  if(read(from_client,private_pipe,HANDSHAKE_BUFFER_SIZE)==-1){
    perror("Server: Error reading SYN\n");
    exit(1);
  }
  printf("Server received PP: %s\n",private_pipe);

  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server;
  char private_pipe[HANDSHAKE_BUFFER_SIZE];

  sprintf(private_pipe,"%d",getpid());
  printf("Client Step 3: Creating PP: %s\n",private_pipe);
  if(mkfifo(private_pipe,0666)==-1){
    perror("Client: Error creating PP\n");
    exit(1);
  }

  printf("Client Step 3: Opening WKP\n");
  *to_server = open(WKP, O_WRONLY);
  if(*to_server == -1){
    perror("Client: Error opening WKP\n");
    remove(private_pipe);
    exit(1);
  }

  printf("Client Step 3: Writing PP name to WKP\n");
  if(write(*to_server,private_pipe,sizeof(private_pipe))==-1){
    perror("Client: Error writing PP to WKP\n");
    remove(private_pipe);
    exit(1);
  }

  printf("Client Step 3: Opening PP (BLOCKS)\n");
  from_server = open(private_pipe,O_RDONLY);
  if(from_server==-1){
    perror("Client: Error opening PP\n");
    remove(private_pipe);
    exit(1);
  }

  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}
