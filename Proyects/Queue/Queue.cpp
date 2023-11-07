#include <iostream>

using namespace std;

/*
* QueueList using two LinkedList front and back,
* and a variable elementQuantity.
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
		if (q->front == NULL) {
			q->back = NULL;
		}
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
		NodeList* iterator = q->front;
		while (iterator != NULL) {
			int element = iterator->data;
			enqueue(clone, element);
			iterator = iterator->next;
		}
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

void display(IntQueue* q) {
	if (!isEmpty(q)) {
		NodeList* iterator = q->front;
		while (iterator != NULL) {
			cout << iterator->data << " ";
			iterator = iterator->next;
		}
		cout << endl;
	}
}

/*
* PriorityQueueList using two dinamic arrays and
* a variable elementQuantity.
* Implementation is bounded.
*/

struct PriorityIntQueue {
	int* elements;
	int* priority;
	unsigned int bound;
	unsigned int elementQuantity;
};

PriorityIntQueue* createPriorityIntQueue(int bound) {
	PriorityIntQueue* pq = new PriorityIntQueue();
	pq->elements = new int[bound];
	pq->priority = new int[bound];
	pq->elementQuantity = 0;
	pq->bound = bound;
	return pq;
}

bool isEmpty(PriorityIntQueue* pq) {
	return pq->elementQuantity == 0;
}

bool isFull(PriorityIntQueue* pq) {
	return pq->elementQuantity == pq->bound;
}

unsigned int numberOfElements(PriorityIntQueue* pq) {
	return pq->elementQuantity;
}

void enqueue(PriorityIntQueue*& pq, int e, int p) {
	if (!isFull(pq)) {
		/*if we want the first elements with minor priority*/
		/*int index = numberOfElements(pq) - 1;
		while (index > -1 && p < pq->priority[index]) {
			pq->elements[index + 1] = pq->elements[index];
			pq->priority[index + 1] = pq->priority[index];
			index--;
		}
		pq->elements[index + 1] = e;
		pq->priority[index + 1] = p;
		pq->elementQuantity++;*/

		int index = numberOfElements(pq);

		//we shift the elements that have a priority
		//in the index bigger or equal to the one to enqueue.
		//queue elements are ordered from bigger priority to minor.
		while (index > -1 && p > pq->priority[index]) {
			pq->elements[index] = pq->elements[index - 1];
			pq->priority[index] = pq->priority[index - 1];
			index--;
		}
		pq->elements[index + 1] = e;
		pq->priority[index + 1] = p;
		pq->elementQuantity++;
	}
}

void dequeue(PriorityIntQueue*& pq) {
	if (!isEmpty(pq)) {
		for (int i = 1; i < pq->elementQuantity; i++) {
			pq->elements[i-1] = pq->elements[i];
			pq->priority[i - 1] = pq->priority[i];
		}
		pq->elementQuantity--;
	}
}

int beginning(PriorityIntQueue* pq) {
	if (!isEmpty(pq)) {
		return pq->elements[0];
	}
}

int priorityBeginning(PriorityIntQueue* pq) {
	if (!isEmpty(pq)) {
		return pq->priority[0];
	}
}

PriorityIntQueue* clone(PriorityIntQueue* pq) {
	PriorityIntQueue* clonedQueue = createPriorityIntQueue(pq->bound);
	
	for (int i = 0; i < pq->elementQuantity; i++) {
		clonedQueue->elements[i] = pq->elements[i];
		clonedQueue->priority[i] = pq->priority[i];
	}
	clonedQueue->elementQuantity = pq->elementQuantity;
	return clonedQueue;
}

void destroy(PriorityIntQueue* pq) {
	delete[] pq->elements;
	delete[] pq->priority;
	delete pq;
}

void display(PriorityIntQueue* pq) {
	if (!isEmpty(pq)) {
		for (int i = 0; i < pq->elementQuantity; i++) {
			cout << pq->elements[i] << "|" << pq->priority[i] << " ";
			cout << endl;
		}
	}
}

int main() {

	//IntQueue* iq = createIntQueue();

	/*for (int i = 0; i < 6; i++) {
		enqueue(iq, i);
	}*/

	//dequeue(iq);

	//cout << first(iq);

	//cout << numberOfElements(iq);
	
	//IntQueue* cloneQueue = clone(iq);

	//destroy(iq);

	//display(iq);

	PriorityIntQueue* pq = createPriorityIntQueue(10);

	enqueue(pq, 1, 4);
	enqueue(pq, 10, 3);
	enqueue(pq, 25, 13);
	enqueue(pq, 6, 4);
	enqueue(pq, 9, 14);
	enqueue(pq, 12, 6);
	enqueue(pq, 8, 2);
	enqueue(pq, 18, 1);
	enqueue(pq, 31, 5);
	enqueue(pq, -31, 5);


	//dequeue(pq);

	//cout << beginning(pq);

	//cout << priorityBeginning(pq);

	//PriorityIntQueue* clonedPQ = clone(pq);
	
	//destroy(pq);

	display(pq);

	return 0;
}
