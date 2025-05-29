#define _GNU_SOURCE
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>

// Goal: Measure average time to access set of pages in a TLB cache

// Note that the resolution of gettimeday is in microseconds
// Nano -> Micro (x1000) -> therefore, access page 1000 times by default.

// Command: tlb.c <number of pages to touch> <number of trials> 
// x axis: # of pages, y axis: average time per access (ns) (control via num of trials) 
int main(int argc, char* argv[]) {
	// pinning the thread to CPU 0
	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(0, &set);
	if (sched_setaffinity(0, sizeof(set), &set) == -1) {
		perror("sched_setaffinity");
		exit(1);
	}

	if(argc != 3) {
		fprintf(stderr, "Invalid command: tlb <number of pages to touch> <number of trials>\n");	
		exit(1);
	}
	const long PAGE_SIZE = getpagesize();
	const int NUM_PAGES = atoi(argv[1]);
	const int TRIALS = atoi(argv[2]);
	int jump = PAGE_SIZE / sizeof(int); // number of integers stored in a page
	// make it a static array to ensure all the pages are sequential
	int arr[jump*NUM_PAGES];
	// TIMER INFORMATION FOR CHART
	struct timeval curr;
	struct timeval final;
	suseconds_t time_per_access = 0; 

	// pre-load everything in cache before starting our trials
	for(int i = 0; i < jump*NUM_PAGES; i += jump) {
		arr[i] += 1; 
	}

	// testing out our cache
	for(int t = 0; t < TRIALS; t += 1) {
		gettimeofday(&curr, NULL);
		for(int j = 0; j < 10000; j += 1) { // loop through 1000 times to go from ns -> us
			for(int i = 0; i < jump*NUM_PAGES; i += jump) {
				arr[i] += 1; 
			}
		}
		gettimeofday(&final, NULL);
		time_per_access += (final.tv_usec - curr.tv_usec) / NUM_PAGES;
	}

	// average all of the values and print graph
	time_per_access = time_per_access / TRIALS;	
	printf("%ld", (long) time_per_access);
	return 0;
}
