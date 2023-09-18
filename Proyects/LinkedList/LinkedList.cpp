#include <iostream>
#include<stdio.h>
#include <stdlib.h>

using namespace std;

struct NodeList {
	int data;
	NodeList* next = NULL;
};

NodeList* first = NULL;

NodeList* createLinkedList(int A[], int n) {

	struct NodeList* temp, * last;
	first = (struct NodeList*)malloc(sizeof(struct NodeList));
	first->data = A[0];
	first->next = NULL;
	last = first;

	for (int i = 1; i <= n; i++) {
		temp = (struct NodeList*)malloc(sizeof(struct NodeList));
		temp->data = A[i];
		temp->next = NULL;
		last->next = temp;
		last = temp;
	}
	return first;
}

void DisplayNodeListData(NodeList* l) {

	while (l->next != NULL) {
		printf("%d \n", l->data);
		l = l->next;
	}
}

void RecursiveDisplayNodeListData(NodeList* l) {

	if (l->next != NULL) {
		printf("%d \n", l->data);
		RecursiveDisplayNodeListData(l->next);
	}
}

int NodeCounter(NodeList* l) {

	int quantity = 0;
	if (l == NULL) {
		return quantity;
	}
	else {
		while (l->next != NULL) {
			quantity++;
			l = l->next;
		}
		return quantity;
	}
}

int RecursiveNodeCounter(NodeList* l) {

	if (l->next == NULL) {
		return 0;
	}
	else {
		return 1+ RecursiveNodeCounter(l->next);
	}
}

int NodeDataSum(NodeList* l) {

	int sum = 0;
	if (l == NULL) {
		return sum;
	}
	else {
		while (l->next != NULL) {
			sum = sum + l->data;
			l = l->next;
		}
		return sum;
	}
}

int RecursiveNodeDataSum(NodeList* l) {

	if (l->next == NULL) {
		return 0;
	}
	else {
		return l->data + RecursiveNodeDataSum(l->next);
	}
}

int maxNodeData(NodeList* l) {

	if (l == NULL) {
		return 0;
	}
	else {
		//we asume first node data is the max node
		int max = l->data;
		while (l->next != NULL) {
			if (l->data > max) {
				max = l->data;
			}
			l = l->next;
		}
		return max;
	}
}

int recursiveMaxNodeData(NodeList* l) {

	if (l == NULL) {
		return 0;
	}
	else {
		int max = recursiveMaxNodeData(l->next);
		if (max > l->data) {
			return max;
		}
		else {
			return l->data;
		}
	}
}

NodeList* searchNode(NodeList* l, int number) {

	if (l == NULL) {
		return NULL;
	}
	else {
		while (l->next != NULL) {
			if (l->data == number) {
				return l;
			}
			l = l->next;
		}
	}
}

NodeList* searchNodeRecursively(NodeList* l, int number) {

	if (l->next == NULL) {
		return NULL;
	}
	if (l->data == number) {
		return l;
	}
	searchNodeRecursively(l->next, number);
}

void insertNodeAtFront(NodeList*& l, int number) {

		NodeList* node = new NodeList();
		node->data = number;
		node->next = l;
		l = node;
}

void insertNodeAtPosition(NodeList*& list, int number, int pos) {

	if (list == NULL || pos == 0) {
		insertNodeAtFront(list, number);
	}
	else {
		if (pos > 0) {
			NodeList* l = list;

			for (int i = 1; i < pos && l->next != NULL; i++) {
				l = l->next;
			}

			NodeList* node = new NodeList();
			node->data = number;
			node->next = l->next;
			l->next = node;
		}
	}
}

void insertNodeInSortedList(NodeList*& list, int number) {

	if (list == NULL || list->data >= number) {
		insertNodeAtFront(list, number);
	}
	else {
		insertNodeInSortedList(list->next, number);
	}
}

void deleteNode(NodeList*& list, int number) {
	if (list != NULL) {
		if (list->data == number) {
			NodeList* nodeToDelete = list;
			list = list->next;
			delete nodeToDelete;
		}
	}
}

void deleteNodeByPositionRecursively(NodeList*& list, int pos) {
	if (list != NULL) {
		if (pos == 0) {
			deleteNode(list, list->data);
		}
		else {
			pos--;
			deleteNodeByPositionRecursively(list->next, pos);
		}
	}
}

int main() {

	int A[] = { 2,1,6,3,30,52,14,26 };
	NodeList* list = createLinkedList(A, 8);

	int B[] = { 1,3,5,8,9,10 };
	NodeList* sortedList = createLinkedList(B, 6);
 
	//RecursiveDisplayNodeListData(list);
	//cout << NodeCounter(list);
	//cout << RecursiveNodeCounter(list);
	//cout << NodeDataSum(list);
	//cout << RecursiveNodeDataSum(list);
	//cout << maxNodeData(list);
	//cout << recursiveMaxNodeData(list);
	//cout << searchNode(list, 14);
	//cout << searchNodeRecursively(list, 14);
	//insertNodeAtPosition(list, 20, 8);
	//insertNodeInSortedList(sortedList, 4);
	deleteNodeByPositionRecursively(list, 6);
	//DisplayNodeListData(sortedList);
	DisplayNodeListData(list);

	return 0;
}
