#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	int * data = (int *) malloc(10*sizeof(int));
	// free weird pointer in data arr
	free(data+5);
	printf("Integer in last index of arr: %d\n", data[9]);
	return 0;
}
