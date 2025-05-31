#include <stdio.h>
#include <pthread.h>

static volatile int counter = 0;

void * count(void * arg) {
	for(int i = 0; i < 1e7; i++) {
		counter += 1;	
	}
	return NULL;
}

int main(int argc, char * argv[]) {
	pthread_t t1, t2;
	pthread_create(&t1, NULL, count, NULL);
	pthread_create(&t2, NULL, count, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("Final counter: %d\n", counter);
	return 0;
}
