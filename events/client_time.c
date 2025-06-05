#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char * argv[]) {
	if(argc != 3) {
		fprintf(stderr, "Invalid command. ./client_time <address> <port>\n");
		exit(1);
	}
	int sd = socket(AF_INET, SOCK_STREAM, 0);
	if(sd < 0) {
		fprintf(stderr, "Cannot init socket.\n");
		exit(1);
	}

	// setting up server address to send messages to
	struct sockaddr_in server_addr;
	socklen_t server_addr_len = (socklen_t) sizeof(server_addr);
	int input_port = atoi(argv[2]);
	char * input_address = argv[1]; 
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(input_port);
	inet_pton(AF_INET, input_address, &server_addr.sin_addr);
	
	printf("Connecting to server %s:%d..\n", input_address, input_port);
	if(connect(sd, (struct sockaddr *) &server_addr, server_addr_len) < 0) {
		fprintf(stderr, "Could not connect to server!\n");
		exit(1);
	}
	printf("Successfully connected. Sending a request..\n");	

	// requesting time from server
	char msg[] = "test";
	if(send(sd, (void *)msg, sizeof(msg), 0) < 0) {
		fprintf(stderr, "Could not send request!\n");
		exit(1);
	}
	printf("Sent server a request.\n");

	char buffer[1024];
	if(recv(sd, (void *) buffer, sizeof(buffer), 0) < 0) {
		fprintf(stderr, "Could not receive request!\n");
		exit(1);
	}
	printf("Current time: %s\n", buffer);
	close(sd);
	return 0;
}
