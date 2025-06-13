#include <stdio.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h> // to check for flags in command

int main(int argc, char* argv[]) {
	DIR * mydir = NULL;
	short l_flag = 0;
	if(argc == 1) {
		// ls with no -l flag or PATH, assume current working directory
		mydir = opendir(".");
	}
	else if(argc == 2) {
		if(strcmp(argv[1], "-l") != 0) {
			mydir = opendir(argv[1]);
		}
		else { 
			mydir = opendir(".");	
			l_flag = 1;
		}
	}
	else {
		l_flag = 1;
		if(strcmp(argv[1], "-l") == 0) {
			mydir = opendir(argv[2]);
		}
		else if(strcmp(argv[2], "-l") == 0) {
			mydir = opendir(argv[1]);
		}
		else {
			fprintf(stderr, "Invalid command.\n");
			exit(1);
		}
	}
	assert(mydir > 0);
	struct dirent * entry = readdir(mydir);
	while(entry != NULL) {
		if(l_flag == 0) {
			printf("%s\n", entry->d_name);
		}
		else {	
			// file size, file name
			struct stat buffer;
			stat(entry->d_name, &buffer);
			printf("%ld %s\n", buffer.st_size, entry->d_name);
		}
		entry = readdir(mydir);
	}
	closedir(mydir);
	return 0;
}

