#include <iostream>
#include<stdio.h>
#include <stdlib.h>

using namespace std;

struct NodeList {
	int data;
	NodeList* next = NULL;
};

NodeList *first = NULL;

NodeList* createLinkedList(int A[], int n) {
	struct NodeList *t, *last;
	first = (struct NodeList *) malloc(sizeof(struct NodeList));
	first->data = A[0];
	first->next = NULL;
	last = first;

	for (int i = 1; i <= n; i++) {
		t = (struct NodeList *) malloc(sizeof(struct NodeList));
		t->data = A[i];
		t->next = NULL;
		last->next = t;
		last = t;
	}
	return first;
}

void DisplayNodeListData(NodeList *p) {
	while (p->next != NULL) {
		printf("%d \n", p->data);
		p = p->next;
	}
}

void RecursiveDisplayNodeListData(NodeList *p) {
	if (p->next != NULL) {
		printf("%d \n", p->data);
		RecursiveDisplayNodeListData(p->next);
	}
}

int NodeCounter(NodeList *p) {
	int quantity = 0;
	while (p->next != NULL) {
		quantity++;
		p = p->next;
	}
	return quantity;
}

int RecursiveNodeCounter(NodeList *p) {
	if (p->next == NULL) {
		return 0;
	}
	else {
		return RecursiveNodeCounter(p->next) + 1;
	}
}

int NodeDataSum(NodeList *p) {
	int sum = 0;
	if (p->next == NULL) {
		return sum;
	}
	while (p->next != NULL) {
		sum = sum + p->data;
		p = p->next;
	}
	return sum;
}

int RecursiveNodeDataSum(NodeList *p) {
	if (p->next == NULL) {
		return 0;
	}
	else {
		return RecursiveNodeDataSum(p->next) + p->data;
	}
}

int maxNodeData(NodeList *p) {
	if (p->next == NULL) {
		return 0;
	}
	//we asume first node data is the max node
	int max = p->data;
	while (p->next != NULL) {
		if (p->data > max) {
			max = p->data;
		}
		p = p->next;
	}
	return max;
}

int recursiveMaxNodeData(NodeList *p) {
	if (p->next == NULL) {
		return INT_MIN;
	}
	else {
		int max = recursiveMaxNodeData(p->next);
		if (max > p->data) {
			return max;
		}
		else {
			return p->data;
		}
	}
}

NodeList* searchNode(NodeList *p, int number) {
	if (p->next == NULL) {
		return NULL;
	}
	while (p->next != NULL) {
		if (p->data == number) {
			return p;
		}
		p = p->next;
	}
}

NodeList* searchNodeRecursively(NodeList *p, int number) {
	if (p->next == NULL) {
		return NULL;
	}
	if (p->data == number) {
		return p;
	}
	searchNodeRecursively(p->next, number);
}

int main() {

	int A[] = { 2,4,6,8,10,12,14,16 };
	NodeList *p = createLinkedList(A, 8);

	//DisplayNodeListData(p); 
	//RecursiveDisplayNodeListData(p);
	//cout << NodeCounter(p);
	//cout << RecursiveNodeCounter(p);
	//cout << NodeDataSum(p);
	//cout << RecursiveNodeDataSum(p);
	//cout << maxNodeData(p);
	//cout << recursiveMaxNodeData(p);
	//cout << searchNode(p, 14);
	cout << searchNodeRecursively(p, 14);

	return 0;
}
