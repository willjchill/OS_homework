#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// we will use a linkedlist in C to determine the winner
// using lottery-based scheduling to maximize proportional-fairness

struct node {
	int tickets;
	struct node * next;
};

int g_tickets = 0;
struct node * head = NULL; // no job init

// create new job w tickets and insert into linked list
void insert(int job_tickets) {
	g_tickets += job_tickets;
	struct node * tmp = malloc(sizeof(struct node));	
	tmp->tickets = job_tickets; 
	tmp->next = head;
	head = tmp;
	return;
}

// prints all jobs in the linked list
void printlist() {
	int job = 1;
	struct node * s = head;
	while(s != NULL) {
		printf("Job %d - tickets %d\n", job, s->tickets);
		s = s->next;
		job += 1;
	}
	return;
}

int main(int argc, char* argv[]) {
	// input command arguments to set the seed
	if (argc != 2) {
		fprintf(stderr, "Command should be: lottery <seed>\n");
		exit(1);
	}
	srand(atoi(argv[1]));

	// test case: insert 3 jobs 
	insert(50);
	insert(100);
	insert(200);

	// get a winner using rand number between 0 and g_tickets
	int winner = random() % g_tickets;

	// search through linked list to get a winner
	struct node * s = head;
	int sum = 0; 
	while(s != NULL) {
		sum += s->tickets;
		if(sum > winner) {
			break;	
		}
		s = s->next;
	}
	printlist();
	printf("Winner: lottery # - %d, job tickets # - %d\n", winner, s->tickets);	
	return 0;
}
