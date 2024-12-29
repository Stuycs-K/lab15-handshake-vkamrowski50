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
  printf("Server: Creating WKP\n");
  if(mkfifo(WKP,0666)==-1){
    perror("Server: Error creating WKP\n");
    exit(1);
  }

  printf("Server: Opening WKP (BLOCKS)\n");
  from_client = open(WKP, O_RDONLY);
  if(from_client==-1){
    perror("Server: Error opening WKP\n");
    exit(1);
  }

  printf("Server: Removing WKP\n");
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
  int from_client;
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
  char PP[40];
  sprintf(PP,"%d",getpid());
  mkfifo(PP,0666);
  int firstopen = open(WKP,O_WRONLY);
  write(WKP,PP,sizeof(PP));
  int firstread = open(PP,O_RDONLY);
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
