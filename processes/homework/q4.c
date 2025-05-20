// Using fork to execute /bin/ls
// Using ALL execute syscalls available
// 1. Execl
// 2. Execle
// 3. Execlp
// 4. Execv
// 5. Execvp
// 6. Execvpe

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	printf("Command list: \n1.Execl\n2.Execle\n3.Execlp\n4.Execv\n5.Execvp\n6.Execvpe\n\n");
	const char* PATH = "/bin/ls";
	const char* COMMAND = "ls";
	char* const COMMAND_LIST[] = {"ls", NULL};
	for (int i = 0; i < 6; i++) {
		int rc = fork(); 
		if (rc < 0) {
			fprintf(stderr, "Cannot fork.");
			exit(1);	
		}
		if(rc == 0) {
			printf("Command %d\n", i+1);
			// l -> list of args as params
			// v -> var of args in 2d array
			// e -> custom env variables to read from
			// p -> assume command is in sys PATH env var
			switch(i) { // note that there is no breaks since child process will be rewritten anyway...
				case 0:
					execl(PATH, COMMAND, (char *)NULL);
				case 1: 
					// no useful env vars	
					execle(PATH, COMMAND, (char *)NULL, (char **)NULL);
				case 2:
					execlp(COMMAND, COMMAND, (char *) NULL);
				case 3:
					execv(PATH, COMMAND_LIST);
				case 4:
					execvp(COMMAND, COMMAND_LIST);
				case 5:
					execve(PATH, COMMAND_LIST, (char **) NULL);
			}
		}
		else {
			wait(NULL);
		}
	}
	printf("Finished\n");
	return 0;
}
