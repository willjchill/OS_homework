#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	long counter = 0;
	struct timeval start, finish;
	gettimeofday(&start, NULL);
	for(int i = 0; i < 10e5; i++) {
		counter++;	
	}
	gettimeofday(&finish, NULL);
	long exe_sec = (long)finish.tv_sec - (long)start.tv_sec;
	long exe_usec = (long)finish.tv_usec - (long)start.tv_usec;
	long combined_exe = exe_sec * (long)1000000 + exe_usec;
	printf("Final counter: %ld\n", counter);
	printf("Time to execute (us): %ld\n", combined_exe); 
	return 0;
}
