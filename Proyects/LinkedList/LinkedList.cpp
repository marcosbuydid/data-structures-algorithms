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

	for (int i = 1; i < n; i++) {
		temp = (struct NodeList*)malloc(sizeof(struct NodeList));
		temp->data = A[i];
		temp->next = NULL;
		last->next = temp;
		last = temp;
	}
	return first;
}

void displayNodeListData(NodeList* l) {

	while (l != NULL) {
		printf("%d \n", l->data);
		l = l->next;
	}
}

void displayNodeListDataRec(NodeList* l) {

	if (l != NULL) {
		printf("%d \n", l->data);
		displayNodeListDataRec(l->next);
	}
}

int listLength(NodeList* l) {

	int quantity = 0;
	if (l == NULL) {
		return quantity;
	}
	else {
		while (l != NULL) {
			quantity++;
			l = l->next;
		}
		return quantity;
	}
}

int listLengthRec(NodeList* l) {

	if (l == NULL) {
		return 0;
	}
	else {
		return 1 + listLengthRec(l->next);
	}
}

int nodeDataSum(NodeList* l) {

	int sum = 0;
	if (l == NULL) {
		return sum;
	}
	else {
		while (l != NULL) {
			sum = sum + l->data;
			l = l->next;
		}
		return sum;
	}
}

int nodeDataSumRec(NodeList* l) {

	if (l == NULL) {
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
		while (l != NULL) {
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
		while (l != NULL) {
			if (l->data == number) {
				return l;
			}
			l = l->next;
		}
		return NULL;
	}
}

NodeList* searchNodeRec(NodeList* l, int number) {

	if (l == NULL) {
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

	if (list == NULL || pos == 1) {
		insertNodeAtFront(list, number);
	}
	else {
		if (pos > 1) {
			NodeList* l = list;

			for (int i = 2; i < pos && l->next != NULL; i++) {
				l = l->next;
			}

			NodeList* node = new NodeList();
			node->data = number;
			node->next = l->next;
			l->next = node;
		}
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
	if (list != NULL && pos > 0) {
		if (pos == 1) {
			deleteNode(list, list->data);
		}
		else {
			pos--;
			deleteNodeByPositionRec(list->next, pos);
		}
	}
}

NodeList* eraseRange(NodeList*& l, int startPos, int finalPos) {
	if (l == NULL || startPos > finalPos || startPos < 1) {
		return NULL;
	}
	else {
		int posAux = 1;
		NodeList* result = NULL;
		while (l != NULL) {
			if (posAux == startPos) {
				while (startPos <= finalPos) {
					deleteNode(l, l->data);
					startPos++;
				}
			}
			if (l != NULL) {
				insertNodeAtLast(result, l->data);
				l = l->next;
			}
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
		eraseRangeRec(list->next, startPos - 1, finalPos - 1);
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

		for (int i = 1; i < n; i++) {
			temp = new NodeList();
			temp->data = a[i];
			temp->next = NULL;
			last->next = temp;
			last = temp;
		}
		return result;
	}
}

NodeList* commons(NodeList* l1, NodeList* l2) {
	NodeList* result = NULL;

	if (l1 == NULL || l2 == NULL) {
		return result;
	}
	else {
		while (l1 != NULL && l2 != NULL) {
			if (l1->data == l2->data) {
				insertNodeAtFront(result, l1->data);
				l1 = l1->next;
				l2 = l2->next;
			}
			else if (l1->data < l2->data) {
				l1 = l1->next;
			}
			else {
				l2 = l2->next;
			}
		}
	}
	return result;
}

void difference(NodeList*& l1, NodeList* l2) {
	if (l1 == NULL || l2 == NULL) {
		return;
	}
	while (l1->next != NULL && l2->next != NULL) {
		if (l1->data == l2->data) {
			deleteNode(l1, l1->data);
			l2 = l2->next;
		}
		else if (l1->data < l2->data) {
			l1 = l1->next;
		}
		else {
			l2 = l2->next;
		}
	}
}

void deleteFrom(NodeList*& l, unsigned int k) {
	int length = listLength(l);

	if (l == NULL || k < 1 || k >= length) {
		return;
	}
	int pos = 1;
	while (l != NULL && l->next != NULL) {
		if (pos > k) {
			while (k < length) {
				deleteNode(l, l->data);
				k++;
			}
		}
		else {
			pos++;
			l = l->next;
		}
	}
}

void addOrdered(NodeList*& list, int number) {

	if (list == NULL || number <= list->data) {
		insertNodeAtFront(list, number);
	}
	else {
		addOrdered(list->next, number);
	}
}

NodeList* sort(NodeList* l) {
	if (l == NULL) {
		return NULL;
	}
	NodeList* result = NULL;
	while (l != NULL) {
		addOrdered(result, l->data);
		l = l->next;
	}
	return result;
}

NodeList* impairPositionCopy(NodeList* l) {
	if (l == NULL) {
		return NULL;
	}
	NodeList* result = NULL;
	int pos = 1;
	while (l != NULL) {
		if (pos % 2 == 1) {
			insertNodeAtLast(result, l->data);
		}
		l = l->next;
		pos++;
	}
	return result;
}

void deleteNoInitialPos(NodeList* &l, int k) {
	int length = listLength(l);
	if (l == NULL || k > length) {
		return;
	}
	int pos = 1;
	while (l != NULL) {
		if (pos == k) {
			deleteNode(l, l->data);
		}
		if (l != NULL) {
			l = l->next;
		}
		pos++;
	}
}

NodeList* copyByPosition(NodeList* L, int p1, int p2) {
	// precondition 1≤ p1≤ p2≤ length(L)
	if (L == NULL) {
		return NULL;
	}
	int pos = 1;
	NodeList* result = NULL;
	while (L != NULL) {
		if (pos == p1) {
			while (p1 <= p2) {
				insertNodeAtFront(result, L->data);
				p1++;
				L = L->next;
			}
		}
		else {
			pos++;
			if (L != NULL) {
				L = L->next;
			}
		}
	}
	return result;
}

void insert(NodeList*& list, int number) {

	if (list == NULL || number >= list->data) {
		insertNodeAtFront(list, number);
	}
	else {
		insert(list->next, number);
	}
}

NodeList* merge(int* a1, int* a2, int n) {
	//precondition n > 0 so arrays have at least 1 element
	NodeList* result = NULL;
	int pos = 0;

	while (pos < n) {
		if (a1[pos] <= a2[pos]) {
			insert(result, a1[pos]);
			insert(result, a2[pos]);
		}
		else {
			insert(result, a2[pos]);
			insert(result, a1[pos]);
		}
		pos++;
	}
	return result;
}

int main() {

	int A[] = { 2,1,6,3,30,52,14,26 };
	NodeList* list = createLinkedList(A, 8);

	int B[] = { 1,3,5,8,9,10 };
	NodeList* sortedList = createLinkedList(B, 6);

	int C[] = { 1,2,3,4,5,6,7,8 };
	NodeList* listTwo = createLinkedList(C, 8);

	int D[] = { 1,3,4,8 };
	NodeList* listThree = createLinkedList(D, 4);

	int E[] = { 1,2,4,6,7,8,9 };
	NodeList* listFour = createLinkedList(E, 7);

	int F[] = { 1,3,4,8,10 };
	NodeList* listFive = createLinkedList(F, 5);

	int G[] = { 1,2,5,8,9,13 };
	NodeList* listSix = createLinkedList(G, 6);

	int H[] = { 5,2,3,9,8 };
	NodeList* listSeven = createLinkedList(H, 5);

	int* p = A;

	int I[] = { 2,4,4,6,7 };

	int J[] = { 1,2,4,8,9 };

	//displayNodeListDataRec(list);
	//cout << listLength(list);
	//cout << listLengthRec(list);
	//cout << nodeDataSum(list);
	//cout << nodeDataSumRec(list);
	//cout << maxNode(list);
	//cout << maxNodeRec(list);
	//cout << searchNode(list, 14);
	//cout << searchNodeRec(list, 14);
	//insertNodeAtPosition(list, 20, 7);
	//insertNodeInSortedList(sortedList, 4);
	//deleteNodeByPositionRec(list, 6);
	//NodeList* auxList = eraseRange(listTwo, 2, 5);
	//NodeList* auxList = eraseRangeRec(listTwo, 2, 5);
	//NodeList* auxList = arrayToList(p, 8);
	//NodeList* result = commons(listThree, listFour);
	//difference(listFive, listSix);
	//deleteFrom(listSeven, 3);
	//NodeList* result = sort(list);
	//NodeList* result = impairPositionCopy(listSeven);
	//deleteNoInitialPos(listSeven, 5);
	//NodeList* result = copyByPosition(listSeven, 2, 5);
	NodeList* result = merge(I, J, 5);
	displayNodeListData(result);
	
	return 0;
}
