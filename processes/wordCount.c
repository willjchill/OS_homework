#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	int rc = fork();
	if(rc < 0) {
		fprintf(stderr, "Cannot fork.");
		exit(1);
	}
	if(rc == 0) {
		close(1);
		open("./wordCount.text", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		char * argv[3];
		argv[0] = "wc";
		argv[1] = "wordCount.c";
		argv[2] = NULL;
		execvp(argv[0], argv);
	} 
	else {
		int rc_wait = wait(NULL); // child waits for parent to change fd
	}
	return 0;
}
