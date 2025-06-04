#include <stdio.h>
#include <pthread.h>
#include <assert.h>

static int buffer; // for simplicity, buffer is 1 integer
static pthread_mutex_t g_lock;
static pthread_cond_t g_cond;

// put item in the buffer
void put() {
	assert(buffer == 0); // buffer should NOT be full
	buffer = 1;
	printf("Produced!\n");
}

void get() {	
	assert(buffer == 1); // buffer should NOT be empty 
	buffer = 0;
	printf("Consumed!\n");
}

void * producer(void * args) {
	// producer will put stuff into the buffer a few times (via a loop)
	printf("Starting to produce!\n");
	for(int i = 0; i < 5; i++) {
		pthread_mutex_lock(&g_lock);
		while(buffer == 1) {
			pthread_cond_wait(&g_cond, &g_lock);
		}
		put();
		pthread_cond_signal(&g_cond);
		pthread_mutex_unlock(&g_lock);
	}
	return NULL;
}

void * consumer(void * args) {
	// producer will put stuff into the buffer a few times (via a loop)
	printf("Starting to consume!\n");
	for(int i = 0; i < 5; i++) {
		pthread_mutex_lock(&g_lock);
		while(buffer == 0) {
			pthread_cond_wait(&g_cond, &g_lock);
		}
		get();
		pthread_cond_signal(&g_cond);
		pthread_mutex_unlock(&g_lock);
	}
	return NULL;
}

int main(int argc, char * argv[]) {
	buffer = 0;
	pthread_mutex_init(&g_lock, NULL);
	pthread_cond_init(&g_cond, NULL);
	pthread_t prod, cons;
	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);
	pthread_join(prod, NULL);
	pthread_join(cons, NULL);
	return 0;
}
