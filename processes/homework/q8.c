#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

#define FORK_ERROR(rc) do { if(rc < 0) { fprintf(stderr, "Cannot fork."); exit(1); } } while(0)

int main(int argc, char * argv[]) {
	int pipefd[2];
	if(pipe(pipefd) == -1) {
		fprintf(stderr, "Cannot pipe.");
		exit(1);
	}
	int rc = fork();
	FORK_ERROR(rc);
	if (rc == 0) { //first child
		close(pipefd[0]); // first child will be writing
		dup2(pipefd[1], STDOUT_FILENO);
		printf("hello - sent from first child");	
	}
	else {
		int rc_2 = fork();
		FORK_ERROR(rc_2);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]); // first child will be reading
		if(rc_2 == 0) { // second child
			char buffer[100];
			read(pipefd[0], buffer, 100); // possible vulnerability but wtv lol  
			printf("second child sees - %s\n", buffer);	
		}
	}
	return 0;
}
