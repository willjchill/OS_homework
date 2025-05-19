#include <time.h>

void setTimeout(int seconds) {
	time_t init = time(NULL);
	while(time(NULL) - init < seconds) {
		continue;
	}
	return;
}
