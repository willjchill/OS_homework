#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

// we are going to use a binary semaphore (essentially just a lock)
// recall that semaphore are mutexes and conditional variables combined

static int counter = 0; 
static sem_t g_sem;

void * worker(void * args) {
	sem_wait(&g_sem);	
	counter += 1;
	sem_post(&g_sem);	
	return NULL;
}

int main(int argc, char * argv[]) {
	sem_init(&g_sem, 0, 1);
	pthread_t t1, t2;
	pthread_create(&t1, NULL, worker, NULL);
	pthread_create(&t2, NULL, worker, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("Final counter: %d\n", counter);
	return 0;
}
