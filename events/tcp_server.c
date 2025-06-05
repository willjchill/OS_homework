#include <stdio.h> // you should know what this is by now...
#include <sys/socket.h> // good ol' socket structure in Linux
#include <netinet/in.h> // socket address IPv4 data type, port conversion
#include <stdlib.h> // error handling
#include <arpa/inet.h> // for string to struct IP conversion
#include <time.h> // part of our request API
#include <unistd.h> // for close fd in UNIX
#include <string.h> // for buffers

// we're going to set up a local TCP server using sockets in C
// this should teach us about event-based concurrency

int main(int argc, char * argv[]) {
	if(argc != 3) {
		fprintf(stderr, "Invalid command. ./tcp_server <address> <port>\n");
		exit(1);
	}
	int sd = socket(AF_INET, SOCK_STREAM, 0);
	if(sd < 0) {
		fprintf(stderr, "Could not init the socket!\n");
		exit(1);
	}

	// configuring server address..
	
	struct sockaddr_in server_addr;
	int input_port = atoi(argv[2]);
	char * input_address = argv[1];
	server_addr.sin_port = htons(input_port); 
	server_addr.sin_family = AF_INET;
	inet_pton(AF_INET, input_address, &server_addr.sin_addr);

	// ok, server address is configured...
	// binding socket file to network stack based on our address	
	
	if(bind(sd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		fprintf(stderr, "Could not bind!\n");		
		exit(1);
	}
	printf("Server is listening on %s:%d\n", input_address, input_port);
	listen(sd, 1); // listen for a request (1) from the client
	// continously serve requests from client
	struct sockaddr_in client_addr;
	socklen_t client_addr_len;
	while(1) {
		printf("Waiting for request...");
		client_addr_len = (socklen_t) sizeof(client_addr);
		int client_sd = accept(sd, (struct sockaddr *) &client_addr, &client_addr_len); // checking network stack for packet (BLOCKING) 
		if(client_sd < 0) {
			fprintf(stderr, "Cannot accept incoming requests.\n");
			exit(1);
		}
		// if ANY request is sent, immediately respond with time of day
		char buffer[1024];
		recv(client_sd, (void *) buffer, sizeof(buffer), 0);
		// get time of day for response
		time_t now;
		time(&now);
		char * response = ctime(&now);
		send(client_sd, response, strlen(response), 0);
		printf("Served a request.\n");
		close(client_sd);
	}
	close(sd);
}
