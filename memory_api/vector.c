#include <stdlib.h>
#include <stdio.h>

// creating vector ds with c
// assume vectors only accept integers

typedef struct {
	int size;
	int * head; // uses malloc to get contigous block of mem
} vector;

vector * createVector(int size) {
	vector * my_vec = malloc(sizeof(vector));
	my_vec->size = size;
	my_vec->head = calloc(size, sizeof(int));
	return my_vec;
}

void append(vector * my_vec, int val) {
	my_vec->head = (int *) realloc(my_vec->head, sizeof(int)*(my_vec->size+1));
	my_vec->size += 1;
	my_vec->head[my_vec->size-1] = val;
	return;
}

void printVector(vector my_vec) {
	for(int i = 0; i < my_vec.size; i++) {
		printf("%d ", my_vec.head[i]);
	}
	printf("\n");
	return;
}

int main(int argc, char* argv[]) {
	vector * vec = createVector(3);
	append(vec, 3);
	append(vec, 4);
	printf("%d\n", vec->size);
	printVector(*vec);
	// done with vector. removing it from the mem
	free(vec->head);
	free(vec);
	vec = NULL;
	return 0;
}
