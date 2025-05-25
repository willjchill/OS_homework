#include <stdio.h>

int main(int argc, char* argv[]) {
	int * ptr = NULL;
	// bad code
	printf("Integer in pointer: %d\n", *ptr);
	return 0;
}
