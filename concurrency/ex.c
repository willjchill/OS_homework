#include <stdio.h>
#include <pthread.h>

void * printChar(void * letter) {
	printf("%s\n", (char *) letter);
	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_t t1, t2;
	printf("Entering main thread...\n");
	pthread_create(&t1, NULL, printChar, "A");
	pthread_create(&t2, NULL, printChar, "B");
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("Completed main thread...\n");
	return 0;
}
	
