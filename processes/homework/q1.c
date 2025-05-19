#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int x = 100;
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "Cannot fork.");
		exit(1);
	}
	if(rc == 0) {
		printf("Local var x = %d (CHILD)\n", x);
		x = 50;
		printf("UPD CHILD: x = %d (CHILD)\n", x);
	}
	else {
		printf("Local var x = %d (PARENT)\n", x);
		x = 10;
		printf("UPD PARENT: x = %d (PARENT)\n", x);
	}
	return 0;
}
