#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int main(int argc, char* argv[]) {
	int pipefd[2];
	pipe(pipefd);
	struct timeval curr;
	if(gettimeofday(&curr, NULL) == -1) {
		fprintf(stderr, "Cannot get time of day.");
		exit(1);
	}
	int rc = fork();
	if(rc < 0) {
		fprintf(stderr, "Cannot fork.");
		exit(1);
	}
	else if(rc == 0) {
		// child process
		char buffer[5];
		for(int i = 0; i < 100; i++) {
			write(pipefd[1], "test", 5);
			read(pipefd[0], buffer, 5);
		}
		exit(0);
	}
	else {
		// parent process
		char buffer[5];
		for(int i = 0; i < 100; i++) {
			write(pipefd[1], "test", 5);
			read(pipefd[0], buffer, 5);
		}
		struct timeval finish;
		if(gettimeofday(&finish, NULL) == -1) {
			fprintf(stderr, "Cannot get time of day.");
			exit(1);
		}
		long res_s = ((long)finish.tv_sec - (long)curr.tv_sec) / 100;
		long res_us = ((long)finish.tv_usec - (long)curr.tv_usec) / 100;
		printf("Time to context switch: %ld s %ld us\n", res_s, res_us); 
	}
	return 0;
}
