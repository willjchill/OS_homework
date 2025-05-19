#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	// practicing fork syscall on UNIX
	int pid = fork(); 
	if (pid < 0) {
		fprintf(stderr, "Cannot create child process.");
		exit(1);
	}
	if(pid == 0) {
		printf("Child process id: %d\n", pid);
	}
	else {
		printf("Parent process id: %d\n", pid);
	}
	return 0;
}
