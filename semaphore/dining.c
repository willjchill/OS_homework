// Solving the dining philosophers problem

// 1 fork to the left and right of each phil in a circle
// Each phil needs two forks to consume
// Let's give every phil 10 food units on their plate

#include <assert.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define FOOD 2 // food per table
#define FORK 5 // # of forks = # of philosophers = # of tables
static int table[FOOD];
static sem_t fork_sem[FORK]; // each philosopher has their own semaphore to order properly

void up_left_fork(int p) { // left of philosopher	
	printf("Philosopher %d picks up left fork.\n", p);
	sem_wait(&fork_sem[p]);
}

void up_right_fork(int p) {
	printf("Philosopher %d picks up right fork.\n", p);
	sem_wait(&fork_sem[(p+1) % FORK]);
}

void down_left_fork(int p) {
	printf("Philosopher %d picks down left fork.\n", p);
	sem_post(&fork_sem[p]);
}

void down_right_fork(int p) {
	printf("Philosopher %d picks down right fork.\n", p);
	sem_post(&fork_sem[(p+1) % FORK]);
}

void eat(int p) {
	table[p]--;
	printf("Philosopher %d eats. %d pieces of food left.\n", p, table[p]);
}

void think(int p) {
	printf("Philosopher %d thinks.\n", p);
}

void * philosopher(void * args) {
	int p = *(int *) args;
	while(table[p] > 0) {
		think(p);
		if(p != FORK-1) {
			up_left_fork(p);
			up_right_fork(p);
		}
		else {
			up_right_fork(p); // order switched for last phil to avoid deadlock
			up_left_fork(p);
		}
		eat(p);
		down_left_fork(p);
		down_right_fork(p);
	}
	return NULL;
}

int main(int argc, char * argv[]) {
	int phil_index[FORK];
	// setting up the tables
	for(int i = 0; i < FORK; i++) {
		sem_init(&fork_sem[i], 0, 1);
		table[i] = FOOD;
		phil_index[i] = i;
	}
	// init the philosophers = forks
	pthread_t phil_threads[FORK];
	for(int i = 0; i < FORK; i++) {
		pthread_create(&phil_threads[i], NULL, philosopher, (void *) &phil_index[i]);
	}
	// join when all philosophers are done eating
	for(int i = 0; i < FORK; i++) {
		pthread_join(phil_threads[i], NULL);
	}
	printf("All philosophers are done eating!\n");
	return 0;
}
