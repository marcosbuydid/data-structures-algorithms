#include <iostream>

using namespace std;

/*
* QueueList using a LinkedList with two pointers
* front and back and a variable elementQuantity.
* Enqueue, first, dequeue and numberOfElements
* operations are made in constant order in the worst case.
* Implementation is unbounded.
*/

struct NodeList {
	int data;
	NodeList* next;
};

struct IntQueue {
	NodeList* front;
	NodeList* back;
	unsigned int elementQuantity;
};

IntQueue* createIntQueue() {
	IntQueue* q = new IntQueue();
	q->front = NULL;
	q->back = NULL;
	q->elementQuantity = 0;
	return q;
}

bool isEmpty(IntQueue* q) {
	return q->elementQuantity == 0;
}

void enqueue(IntQueue*& q, int e) {
	NodeList* node = new NodeList();
	node->data = e;
	node->next = NULL;
	if (isEmpty(q)) {
		q->front = node;
		q->back = node;
	}
	else {
		q->back->next = node;
		q->back = node;
	}
	q->elementQuantity++;
}

int first(IntQueue* q) {
	if (!isEmpty(q)) {
		return q->front->data;
	}
}

void dequeue(IntQueue*& q) {
	if (!isEmpty(q)) {
		NodeList* node = q->front;
		q->front = q->front->next;
		delete node;
		q->elementQuantity--;
	}
}

unsigned int numberOfElements(IntQueue* q) {
	return q->elementQuantity;
}

IntQueue* clone(IntQueue* q) {
	IntQueue* clone = createIntQueue();
	if (isEmpty(q)) {
		return clone;
	}
	else {
		IntQueue* aux = createIntQueue();
		while (q->front != NULL) {
			int element = q->front->data;
			enqueue(aux, element);
			q->front = q->front->next;
		}
		while (!isEmpty(aux)) {
			int element = first(aux);
			enqueue(clone, element);
			dequeue(aux);
		}
		delete aux;
		return clone;
	}
}

void destroy(IntQueue*& q) {
	if (isEmpty(q)) {
		delete q;
	}
	else {
		while (q->front != NULL) {
			NodeList* nodeToDelete = q->front;
			q->front = q->front->next;
			delete nodeToDelete;
		}
		delete q;
	}
}

int main() {
	return 0;
}
