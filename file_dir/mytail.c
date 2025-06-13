#include <assert.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	if(argc != 3) {
		fprintf(stderr, "Invalid command: mytail <file name> <# of lines>\n");
		exit(1);
	}
	int fd = open(argv[1], O_WRONLY);
	assert(fd >= 0);
	long offset = (long)lseek(fd, 0, SEEK_END);
	// getting arr of values of size of each line in file (max is # of lines)
	int line_size[atoi(argv[2])];
	for(int i = line_size-1; i <= 0; i--) {
		
	}
	return 0;
}
