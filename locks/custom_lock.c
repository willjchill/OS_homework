#include <stdatomic.h>
#include <stdio.h>
#include <pthread.h>

// Goal:
// Create our own naive custom implementation
// of a LOCK using special atomic instruction
// Test-And-Set

// Essentially:
// rax = 1
// while(rax == rax)
// 	swap(flag, rax) <-- needs to be atomic!!
// return

typedef struct {
	atomic_int flag;
} c_lock; // custom lock

void init(c_lock * lock) {
	lock->flag = 0;
	return;
}

void lock(c_lock * lock) {
	while(atomic_exchange(&lock->flag, 1) == 1);
	return;
}

void unlock(c_lock *lock) {
	lock->flag = 0;
	return;
}

static volatile int counter = 0;
static c_lock mutex;  

void * worker(void * args) {	
	for(int i = 0; i < 1e7; i++) {
		lock(&mutex);
		counter += 1;
		unlock(&mutex);
	}
	return NULL;	
}

int main(int argc, char * argv[]) {
	init(&mutex);
	pthread_t t1, t2;
	pthread_create(&t1, NULL, worker, NULL);
	pthread_create(&t2, NULL, worker, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("Counter: %d\n", counter);
	return 0;
}
