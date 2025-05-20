#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char * argv[]) {
	int pipefd[2];
	pipe(pipefd);
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "Cannot fork");
		exit(1);
	}
	if (rc == 0) {
		int rc_2 = fork();
		pid_t child_pid = getpid();
		printf("Child PID: %d", child_pid);
	}
	return 0;
}
