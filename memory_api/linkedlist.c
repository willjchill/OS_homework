#include <stdlib.h>
#include <stdio.h>

struct node {
	int val;
	struct node * next;
};

struct node * createList() {
	struct node * head = malloc(sizeof(struct node));
	head->val = 0;
	head->next = NULL;
	return head;
}

struct node * append(struct node * head, int val) {
	struct node * newNode = malloc(sizeof(struct node));
	newNode->val = val;
	newNode->next = head;
	return newNode; // our new head
}

void printList(struct node * head) {
	struct node * s = head;
	while(s) {
		printf("%d ", s->val);
		s = s->next;
	}
	printf("\n");
	return;
}

int main(int argc, char* argv[]) {
	struct node * mylist = createList();
	mylist = append(mylist, 0);
	mylist = append(mylist, 0);
	mylist = append(mylist, 3);
	mylist = append(mylist, 4);
	printList(mylist);
	// freeing up list and all that
	struct node * s = mylist;
	while(s) {
		struct node * tmp = s;
		s = s->next;
		// destructor
		tmp->val = 0;
		tmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
	return 0;
}
