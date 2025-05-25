#include <stdlib.h>

int main(int argc, char* argv[]) {
	int * ptr = (int *) malloc(sizeof(int));
	// no free... mem leak in process!
	return 0;
}
