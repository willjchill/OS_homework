// Testing to see if OFFSET is shared in open file table
// of parent and child process in UNIX

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	int fd = open("file.txt", O_WRONLY);		
	assert(fd >= 0);
	int rc = fork();
	assert(rc >= 0); 
	if(rc == 0) { // child process		
		printf("Child process: Offset = %ld\n", (long)lseek(fd, 10, SEEK_SET));
	}
	else {
		(void) wait(NULL); // ensures child runs first
		printf("Parent process: Offset = %ld\n", (long)lseek(fd, 0, SEEK_CUR));	
	}
	return 0;
}
