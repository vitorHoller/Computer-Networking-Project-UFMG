all:
	gcc -Wall -c common.c
	gcc -Wall -c f_server.c
	gcc -Wall client.c common.o -o client
	gcc -Wall server.c common.o f_server.o -o server

clean:
	rm common.o f_server.o client server 
