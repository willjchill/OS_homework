#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "Cannot fork");
		exit(1);
	}
	if (rc == 0) {
		close(STDOUT_FILENO); // stdout fd = 1
		printf("hello\n");	
	}
	else {
		wait(NULL);
		printf("parent hi\n");
	}
	return 0;
}
