#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	int * arr = (int *) malloc(10*sizeof(int));
	free(arr);
	printf("First value in arr: %d\n", arr[0]);
	return 0;
}
