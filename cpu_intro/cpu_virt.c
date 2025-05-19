#include <stdlib.h>
#include <stdio.h>
#include "setTimeout.h"

int main(int argc, char* argv[]) {
	// attempting to write a program
	// that prints out argv[1] after 1 second of time
	if(argc != 2) {
		fprintf(stderr, "Incorrect init\n");
		exit(1);
	}	
	while(1) {
		printf("%s\n", argv[1]); // runs instruction every second
		setTimeout(1);
	}
	return 0;
}
