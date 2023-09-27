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

void displayNodeListData(NodeList* l) {

	while (l->next != NULL) {
		printf("%d \n", l->data);
		l = l->next;
	}
}

void displayNodeListDataRec(NodeList* l) {

	if (l->next != NULL) {
		printf("%d \n", l->data);
		displayNodeListDataRec(l->next);
	}
}

int nodeCounter(NodeList* l) {

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

int nodeCounterRec(NodeList* l) {

	if (l->next == NULL) {
		return 0;
	}
	else {
		return 1+ nodeCounterRec(l->next);
	}
}

int nodeDataSum(NodeList* l) {

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

int nodeDataSumRec(NodeList* l) {

	if (l->next == NULL) {
		return 0;
	}
	else {
		return l->data + nodeDataSumRec(l->next);
	}
}

int maxNode(NodeList* l) {

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

int maxNodeRec(NodeList* l) {

	if (l == NULL) {
		return 0;
	}
	else {
		int max = maxNodeRec(l->next);
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

NodeList* searchNodeRec(NodeList* l, int number) {

	if (l->next == NULL) {
		return NULL;
	}
	if (l->data == number) {
		return l;
	}
	searchNodeRec(l->next, number);
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

void insertNodeAtLast(NodeList*& list, int number) {
	if (list == NULL) {
		list = new NodeList();
		list->data = number;
		list->next = NULL;
	}
	else {
		insertNodeAtLast(list->next, number);
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

void deleteNodeByPositionRec(NodeList*& list, int pos) {
	if (list != NULL) {
		if (pos == 0) {
			deleteNode(list, list->data);
		}
		else {
			pos--;
			deleteNodeByPositionRec(list->next, pos);
		}
	}
}

NodeList* eraseRange(NodeList*& list, int startPos, int finalPos) {
	if (list == NULL || startPos > finalPos || startPos < 1) {
		return NULL;
	}
	else {
		int posAux = 1;
		NodeList* result = NULL;
		while (list != NULL) {
			if (posAux == startPos) {
				while (startPos <= finalPos) {
					deleteNode(list, list->data);
					startPos++;
				}
			}
			insertNodeAtLast(result, list->data);
			list = list->next;
			posAux++;
		}
		return result;
	}
}

NodeList* eraseRangeRec(NodeList*& list, int startPos, int finalPos) {
	if (list == NULL || startPos > finalPos || startPos < 1) {
		return NULL;
	}
	if (startPos == 1 && finalPos >= 1) {
		deleteNode(list, list->data);
		eraseRangeRec(list, startPos, finalPos - 1);
	}
	else {
		eraseRangeRec(list->next, startPos-1, finalPos - 1);
	}
	return list;
}

NodeList* arrayToList(int* a, unsigned int n) {
	if (n < 1) {
		return NULL;
	}
	else {
		NodeList* result = NULL;
		NodeList* temp = NULL;
		NodeList* last = NULL;

		result = new NodeList();
		result->data = a[0];
		result->next = NULL;
		last = result;

		for (int i = 1; i <= n; i++) {
			temp = new NodeList();
			temp->data = a[i];
			temp->next = NULL;
			last->next = temp;
			last = temp;
		}
		return result;
	}
}

int main() {

	int A[] = { 2,1,6,3,30,52,14,26 };
	NodeList* list = createLinkedList(A, 8);

	int B[] = { 1,3,5,8,9,10 };
	NodeList* sortedList = createLinkedList(B, 6);

	int C[] = { 1,2,3,4,5,6,7,8 };
	NodeList* listTwo = createLinkedList(C, 8);

	int* p = A;
 
	//displayNodeListDataRec(list);
	//cout << nodeCounter(list);
	//cout << nodeCounterRec(list);
	//cout << nodeDataSum(list);
	//cout << nodeDataSumRec(list);
	//cout << maxNode(list);
	//cout << maxNodeRec(list);
	//cout << searchNode(list, 14);
	//cout << searchNodeRec(list, 14);
	//insertNodeAtPosition(list, 20, 8);
	//insertNodeInSortedList(sortedList, 4);
	//deleteNodeByPositionRec(list, 6);
	//displayNodeListData(sortedList);
	//NodeList* auxList = eraseRange(listTwo, 2, 5);
	//NodeList* auxList = eraseRangeRec(listTwo, 2, 5);
	NodeList* auxList = arrayToList(p, 8);
	displayNodeListData(auxList);
	

	return 0;
}
