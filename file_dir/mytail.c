#include <assert.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {
	if(argc != 3) {
		fprintf(stderr, "Invalid command: mytail <file name> <# of lines>\n");
		exit(1);
	}
	int fd = open(argv[1], O_RDONLY); // open file for later
	assert(fd >= 0);
	long offset = (long)lseek(fd, -2, SEEK_END); // start at the end of the file and also ignore trailing \n!! IMPORTANT
	// getting arr of values of size of each line in file (max is # of lines)
	int nlines = atoi(argv[2]);
	int line_size[nlines];
	// preinit line_size array to zeros to avoid weird values
	for(int i = 0; i < nlines; i++) {
		line_size[i] = 0;
	}
	char new_line = '\n';
	char read_char[1]; // read 1 char at a time to find newline
	int curline = nlines-1;
	read(fd, read_char, 1);
	// get all the line sizes to print later in the algorithm
	while(curline >= 0 && (int)read_char[0] != 0 && offset >= 0) {
		// printf("debug read - %d\n", (int)read_char[0]);
		if(read_char[0] == '\n') {
			curline--;
		}
		if(curline >= 0) line_size[curline] += 1;
		offset = lseek(fd, -2, SEEK_CUR);
		read(fd, read_char, 1);
	}
	// printing out each line from front -> end to get proper tail of file
	if(offset < 0) {
		lseek(fd, 0, SEEK_SET); // avoid edge case where offset goes to negative
	}
	else {
		lseek(fd, 1, SEEK_CUR);
	}
	char * print_buffer = NULL;
	for(int i = 0; i < nlines; i++) {
		print_buffer = (char *) realloc(print_buffer, sizeof(char)*(line_size[i]+1));
		assert(print_buffer != NULL);
		int rb = read(fd, print_buffer, line_size[i]); 
		print_buffer[line_size[i]] = '\0'; // null terminate 
		printf("%s", print_buffer);	
	}
	printf("\n");
	return 0;
}
