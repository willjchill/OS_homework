#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	// practicing execvp syscall on UNIX
	int pid = fork(); 
	if (pid < 0) {
		fprintf(stderr, "Cannot create child process.");
		exit(1);
	}
	if(pid == 0) {
		printf("Child process id: %d\n", (int)getpid()); 
		// include arguments to execute custom process on command line
		// wc exec_test.c
		char * argv[4];
		argv[0] = "wc"; //read-only string literal (not on stack or heap)
		argv[1] = "-w";
		argv[2] = "exec_test.c";
		argv[3] = NULL;
		int status = execvp(argv[0], argv);
		printf("Should NOT print this line. Execvp exits child process. Exit status: %d\n", status);
	}
	else {
		int pid_wait = wait(NULL);
		printf("Parent process id: %d\n", (int)getpid());
	}
	return 0;
}
