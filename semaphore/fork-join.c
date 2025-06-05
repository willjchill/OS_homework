#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// simulating fork/join methods with semaphores

static sem_t g_sem;

void * child() {
	sleep(1); // ensure it runs properly
	printf("Child done!\n");
	sem_post(&g_sem);
	return NULL;
}

int main(int argc, char * argv[]) {
	pthread_t c1;
	sem_init(&g_sem, 0, 0);
	pthread_create(&c1, NULL, child, NULL);
	sem_wait(&g_sem);
	printf("Parent done!\n");
	return 0;
}
