compile: client1 server1
client1: basic_client.o pipe_networking.o
	@gcc -o clientfile basic_client.o pipe_networking.o

server1: forking_server.o pipe_networking.o
	@gcc -o serverfile forking_server.o pipe_networking.o

basic_client.o: basic_client.c pipe_networking.h
	@gcc -c basic_client.c

forking_server.o: forking_server.c pipe_networking.h
	@gcc -c forking_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	@gcc -c pipe_networking.c

server: serverfile
	@./serverfile

client: clientfile
	@./clientfile

clean:
	@rm *.o
	@rm *~
