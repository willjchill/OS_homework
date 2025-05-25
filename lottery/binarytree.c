#include <stdlib.h>
#include <stdio.h>


// implemented a binary search tree (BST) in C 
struct node {
	int val;
	struct node * left;
	struct node * right;
};

struct node * root = NULL;

void insert(int val) {
	if(!root) {
		root = malloc(sizeof(struct node));
		root->val = val;
	}
	else {
		// search through tree for proper insertion
		struct node * s = root;
		while(s) {
			if(val > s->val) {
				if(s->right) {
					s = s->right;
				}
				else {
					s->right = malloc(sizeof(struct node));
					s->right->val = val;
					break;
				}
			}
			else {
				if(s->left) {
					s = s->left;
				}
				else {
					s->left = malloc(sizeof(struct node));
					s->left->val = val;
					break;
				}
			}
		}
	}
	return;
}

void printTree(struct node * s) {
	if(!s) {
		return;
	}
	printf("%d ", s->val);
	printTree(s->left);
	printTree(s->right);
}

int find(int val) {
	struct node * s = root;
	while(s) {
		if(val > s->val) {
			if(s->right) {
				s = s->right;
			}
			else {
				break;
			}
		}
		else if (val < s->val) {
			if(s->left) {
				s = s->left;
			}
			else {
				break;
			}
		}
		else {
			return 0;
		}
	}
	return -1;
}

int main(int argc, char* argv[]) {
	// test case
	insert(1);
	insert(2);
	insert(3);
	insert(10);
	insert(11);
	insert(12);
	printTree(root);
	int find_val = 10;
	int found = find(find_val);
	printf("\nFound %d for %d\n", found, find_val);
	return 0;
}
