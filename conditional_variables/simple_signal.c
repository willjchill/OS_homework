#include <stdio.h>
#include <pthread.h>

// using conditional variables
// to control order of execution for
// threads -- parent and child in this case

static pthread_mutex_t g_lock; // prevent race conditions on flag for signal
static pthread_cond_t g_cond; // for signaling
static int done = 0;

void thr_exit() {
	pthread_mutex_lock(&g_lock);
	done = 1;
	printf("Child: finish\n");
	pthread_cond_signal(&g_cond);
	pthread_mutex_unlock(&g_lock);
}

void thr_join() {
	pthread_mutex_lock(&g_lock);	
	while(!done) {
		pthread_cond_wait(&g_cond, &g_lock);
	}
	printf("Parent: finish\n");
	pthread_mutex_unlock(&g_lock);
}

void * child(void * args) {
	printf("Child: start\n");
	thr_exit();
	return NULL;
}

int main(int argc, char * argv[]) {
	pthread_mutex_init(&g_lock, NULL);
	pthread_cond_init(&g_cond, NULL);
	printf("Parent: start\n");
	pthread_t c1;
	pthread_create(&c1, NULL, child, NULL);
	thr_join(); // thread join
	return 0;
}
