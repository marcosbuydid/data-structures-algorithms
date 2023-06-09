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

void insertNode(NodeList* &list, int number, int pos) {
	if (list->next == NULL || pos == 0) {
		NodeList* node = new NodeList();
		node->data = number;
		node->next = list;
		list = node;
	}
	else {
		if (pos > 0) {
			NodeList* p = list;

			for (int i = 1; i < pos && p->next != NULL; i++) {
				p = p->next;
			}
			NodeList* node = new NodeList();
			node->data = number;
			node->next = p->next;
			p->next = node;
		}
	}
}

void insertNodeInSortedList(NodeList* &list, int number) {
	if (list->next == NULL || list->data >= number) {
		NodeList* node = new NodeList();
		node->data = number;
		node->next = list;
		list = node;
	}
	else {
		insertNodeInSortedList(list->next, number);
	}
}

void deleteNode(NodeList* &list, int number) {
	if (list != NULL) {
		if (list->data == number) {
			NodeList* nodeToDelete = list;
			list = list->next;
			delete nodeToDelete;
		}
		else {
			deleteNode(list->next, number);
		}
	}
}

void deleteNodeByPosition(NodeList* &list, int pos) {
	if (list != NULL) {
		if (pos == 0) {
			NodeList* nodeToDelete = list;
			list = list->next;
			delete nodeToDelete;
		}
		else {
			if (pos > 0) {
				for (int i = 1; i <= pos && list->next != NULL; i++) {
					list = list->next;
				}
				NodeList* nodeToDelete = list;
				list = list->next;
				delete nodeToDelete;
			}
		}
	}
}

int main() {

	int A[] = { 2,1,6,3,30,52,14,26 };
	NodeList *list = createLinkedList(A, 8);

	int B[] = { 1,3,5,8,9,10 };
	NodeList *sortedList = createLinkedList(B, 6);

	//DisplayNodeListData(list); 
	//RecursiveDisplayNodeListData(list);
	//cout << NodeCounter(list);
	//cout << RecursiveNodeCounter(list);
	//cout << NodeDataSum(list);
	//cout << RecursiveNodeDataSum(list);
	//cout << maxNodeData(list);
	//cout << recursiveMaxNodeData(list);
	//cout << searchNode(list, 14);
	//cout << searchNodeRecursively(list, 14);
	//insertNode(list, 20, 8);
	//insertNodeInSortedList(sortedList, 4);
	//deleteNode(list, 30);
	deleteNodeByPosition(list, 1);
	DisplayNodeListData(list);

	return 0;
}
