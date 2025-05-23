#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	// measuring average syscall time for 100 of them
	struct timeval curr; 
	struct timeval final;
	close(STDOUT_FILENO); // does not write to terminal to flood with message
	if(gettimeofday(&curr, NULL) == -1) {
		fprintf(stderr, "Cannot measure starting time.\n");
		exit(1);
	}
	for(int i = 0; i < 100; i++) {
		syscall(SYS_write, STDOUT_FILENO, "hello\n", 7);  // insert your syscall here
	}
	if(gettimeofday(&final, NULL) == -1) {
		fprintf(stderr, "Cannot measure starting time.\n");
		exit(1);
	}
	open("/dev/tty", O_WRONLY);
	long res_s = ((long)final.tv_sec - (long)curr.tv_sec)/100;
	long res_us = ((long) final.tv_usec - (long) curr.tv_usec)/100;
	printf("Time to execute syscall: %ld s %ld us\n", res_s, res_us);
	return 0;
}
