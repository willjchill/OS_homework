#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
	close(1);
	int fd = open("output.text", O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	int rc = fork();
	if(rc < 0) {
		fprintf(stderr, "Cannot fork.");
		exit(1);
	}
	// can both child and parent access fd?
	if(rc == 0) {
		char * child_text = "read-only str literal CHILD I WILL ADD MORE RANDOM TEXT HERE FOR ILLUSTRATIVE PURPOSES HOPOEFULLYH WHAT I AM PLANNIGN TO DO WORKS HERE\n";
		write(fd, child_text, strlen(child_text));
	}
	else {
		char * parent_text = "read-only str literal PARENT I AM GOING TO DO THE SAME TRICK HERE MY HOPE IS THAT AN INTERRUPT WILL OCCUR AND A ROUND ROIBIN ESQUE CPU SCHEDULING POLICY WILL HAPPEN SUCH THAT THE TEXT WILL BE JUMBLED UP\n";
		write(fd, parent_text, strlen(parent_text));
	}
	return 0;
}
