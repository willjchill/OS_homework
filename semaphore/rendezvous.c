#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// The problem is as follows: you have two threads, each of which are about
// to enter the rendezvous point in the code. Neither should exit this part of
// the code before the other enters it.

static sem_t g_sem; 

void critical() {
	printf("Thread is entering critical part of code.\n");
	sleep(1);
}

void * child() {
	sem_post(&g_sem);
	critical();
	sem_wait(&g_sem);
	printf("Thread is exiting critical part of code.\n");
	return NULL;
}

int main(int argc, char * argv[]) {
	sem_init(&g_sem, 0, -1);
	pthread_t c1, c2;
	pthread_create(&c1, NULL, child, NULL);
	pthread_create(&c2, NULL, child, NULL);
	pthread_join(c1, NULL);
	pthread_join(c2, NULL);
	return 0;
}
