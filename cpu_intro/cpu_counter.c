#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "setTimeout.h"

// demonstrating how our virtual CPU can access memory

int main(int argc, char* argv[]) {
	int * p = malloc(sizeof(int));
	if (p == NULL) {
		fprintf(stderr, "Invalid pointer.");
		exit(1);
	}
	int pid = getpid();
	printf("%d address pointed to by p: %p\n", pid, p);
	// mimic an instruction cycle in our virtual CPU
	while(1) {
		*p = *p + 1;
		printf("%d p: %d\n", pid, *p); 
		setTimeout(1);
	}
	// we won't free(p) and p = NULL because we won't end this program
	return 0;
}
