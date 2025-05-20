#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "Cannot fork.");
		exit(1);
	}
	if(rc == 0) {
		// note that wait produces process id we're waiting in
		int pid = (int)wait(NULL); // wait in child process?
		printf("Child process id status %d.\n", pid);
	}
	else {
		printf("At parent process.\n");
	}

}
