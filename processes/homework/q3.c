#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// we will use pipes in UNIX
// pipes are an IPC (I/O between processes)
// thus, when a process reads from a PIPE it will be in blocking state
int main(int argc, char * argv[]) {
	int rc = fork();
	if(rc < 0) {
		fprintf(stderr, "Cannot fork.");
		exit(1);
	}
	printf("Cur return code for process: %d\n", rc);
	int pipefd[2];
	if(pipe(pipefd) == -1) {
		fprintf(stderr, "Cannot pipe.");
		exit(1);
	}
	if(rc == 0) {
		printf("hello\n");
		close(pipefd[0]); // we will write to pipefd 1
		char * sent = "s";
		write(pipefd[1], sent, sizeof(char));
	}
	else {
		close(pipefd[1]);
		char * buffer;
		// read will put parent into blocking state
		read(pipefd[0], buffer, sizeof(char));
		printf("goodbye\n");
	}

	return 0;
}
