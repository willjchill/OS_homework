// prints out the file system tree 
// with a recursive search

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

// recursive DFS
void print_tree(char * file_path) {
	DIR * mydir = opendir(file_path);
	assert(mydir > 0);
	struct dirent * entry;
	while(1) {
		entry = readdir(mydir);
		if(entry == NULL) break;
		if(entry->d_name[0] == '.') continue; // do not show hidden folders, parent, or current dir
		printf("%s\n", entry->d_name);
		if(entry->d_type == DT_DIR) {
			int len = strlen(file_path) + strlen(entry->d_name) + 1; // slash seperator +1
			char * new_file_path = (char *) malloc(len+1);
			strcpy(new_file_path, file_path);
			strcat(new_file_path, "/");
			strcat(new_file_path, entry->d_name);
			new_file_path[len] = '\0';
			print_tree(new_file_path);
		}
		entry = readdir(mydir);
	}
}

int main(int argc, char* argv[]) {
	char * file_path;
	if(argc == 1) {
		// prints tree of a files in working directory
		file_path = getcwd(NULL, 0);	
	}
	else if(argc == 2) {
		file_path = argv[1];
	}
	else {
		fprintf(stderr, "Invalid command: mysearch <optional: file path>");
		exit(1);
	}
	assert(file_path > 0);
	print_tree(file_path);
	return 0;
}
