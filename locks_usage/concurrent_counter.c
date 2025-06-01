#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
	pthread_mutex_t lock;
	long count;
	long threshold; // stop counter at this point
	int complete; // when threshold is met, trigger flag
	int approx; // how often local workers should update counter
} g_counter;

static g_counter global_counter;

// initalizes the global counter
void init(g_counter * counter, int approx) {
	counter->count = 0;
	counter->threshold = 10e5;
	counter->complete = 0;
	counter->approx = approx;
	pthread_mutex_init(&counter->lock, NULL);
}

int checkThreshold(g_counter * counter) {
	if(counter->count >= counter->threshold) {
		counter->complete = 1;
	}
	return counter->complete;
}

void increment(g_counter * counter, long val) {
	counter->count += val; // critical section
}

void * worker(void * args) {
	int local_counter = 0;
	while(1) {	
		for(int i = 0; i < global_counter.approx; i++) {
			local_counter += 1;
		}
		pthread_mutex_lock(&global_counter.lock);
		if(checkThreshold(&global_counter)) {
			pthread_mutex_unlock(&global_counter.lock); // prevent deadlock
			break;
		}
		else {
			increment(&global_counter, local_counter);
			local_counter = 0; // flush
		}
		pthread_mutex_unlock(&global_counter.lock);
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	if(argc != 3) {
		printf("Invalid command: ./concurrent_counter <number of threads> <approx value>\n");
		return -1;
	}
	const int THREADS_NUM = atoi(argv[1]);
	const int APPROX = atoi(argv[2]);
	struct timeval start, finish;
	init(&global_counter, APPROX); // init concur ds
	gettimeofday(&start, NULL);
	pthread_t * threads_list = (pthread_t *) malloc(THREADS_NUM * sizeof(pthread_t));
	for(int i = 0; i < THREADS_NUM; i++) {
		pthread_create(&threads_list[i], NULL, worker, NULL);
	}
	// now join all the workers once they are complete
	for(int i = 0; i < THREADS_NUM; i++) {
		pthread_join(threads_list[i], NULL);
	}
	gettimeofday(&finish, NULL);
	long exe_sec = (long)finish.tv_sec - (long)start.tv_sec;
	long exe_usec = (long)finish.tv_usec - (long)start.tv_usec;
	long combined_exe = exe_sec * (long)1000000 + exe_usec;
	printf("Final counter: %ld\n", global_counter.count); 
	printf("Time to execute (us): %ld\n", combined_exe); 
	return 0;
}
