#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#define BUCKETS 101

// for hash collisions
// we will use a linkedlist in every key-value table entry in case of collisions
// ****************************************************
struct node {
	void * value;
	struct node * next;
};

typedef struct {
	struct node * head;
} list_t;

void list_init(list_t * list) {
	list->head = NULL;	
}

void list_insert(list_t * list, void * value) {
	struct node * tmp = malloc(sizeof(struct node));
	tmp->value = value;	
	tmp->next = list->head;
	list->head = tmp;
}

void * list_find(list_t * list, void * value) {
	struct node * search = list->head;
	while(search != NULL) {
		if(*(int *)search->value == *(int*)value) {
			return value;
		}
		search = search->next;
	}
	return NULL;
}
// ***************************************************

typedef struct {
	list_t list[BUCKETS];
} hash_t;

// my own naive hashing algorithm
int hash(void * val) {
	float c = 3.14159; // PI constant used for hashing 
	float * pi = &c;
	int key = (((*(int *)val) >> 5) ^ (*(int *)pi)); // simple algo i made up	
	return key;
}

void hash_init(hash_t * table) {
	for(int i = 0; i < BUCKETS; i++) {
		list_init(&table->list[BUCKETS]);
	}
}

void hash_insert(hash_t * table, void * key, void * value) {
	int key_hashed = hash(key) % BUCKETS;
	list_insert(&table->list[key_hashed], value); // collisions added to linked list in key-value pair 
}

void * hash_lookup(hash_t * table, void * key, void * value) {
	int key_hashed = hash(key) % BUCKETS;
	return list_find(&table->list[key_hashed], value);	
}

// ******************************************************

int main(int argc, char * argv[]) {
	hash_t test;
	hash_init(&test);
	char name[] = "John";
	char name2[] = "Alice";
	int age = 34;
	int age2 = 41;
	hash_insert(&test, (void *) &name, (void *) &age);
	hash_insert(&test, (void *) &name2, (void *) &age2);
	void * result_ptr = hash_lookup(&test, (void *) &name2, (void *) &age2); 
	assert(result_ptr != NULL);
	int result = *(int *)result_ptr;	
	printf("Hash for Alice: %d\n", hash((void *) &name2));	
	printf("Alice's age is: %d\n", result); 
	return 0;
}
