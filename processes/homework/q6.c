#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
	pid_t parent_pid = getpid();
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "Cannot fork.");
		exit(1);
	}
	if(rc == 0) {
		// note that wait produces process id we're waiting in
		pid_t pid = waitpid(parent_pid, NULL, 0); // wait until parent is complete? 
		printf("Child process id status %d.\n", (int)pid);
	}
	else {
		printf("At parent process.\n");
	}
	return 0;
}
