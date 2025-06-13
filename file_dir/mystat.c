#include <assert.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
	if(argc != 2) {
		fprintf(stderr, "Invalid command: mystat <file name>\n");	
		exit(1);
	}
	struct stat buffer;
	stat(argv[1], &buffer);
	printf("File: %s\n", argv[1]);
	printf("Size: %ld\tBlocks: %ld\tIO Block: %ld\n", (long)buffer.st_size, (long)buffer.st_blocks, (long)buffer.st_blksize);
	printf("Inode: %ld\tLinks: %ld\n", (long)buffer.st_ino, (long)buffer.st_nlink);
	return 0;
}
