#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	if(argc != 2) {
		fprintf(stderr, "Invalid command. Type memory-user.c <amount of mem in bytes>\n");
		return -1;
	}
	int mem = atoi(argv[1]);
	char * stream = calloc(mem, sizeof(char)); 
	char s;
	while(1) {
		for (int i = 0; i < mem; i++) {
			s = stream[i]++; // stream through array
		}
	}
	return 0;
}
