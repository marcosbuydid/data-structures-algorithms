#include <iostream>

using namespace std;

/*
* IntQueue using two pointers called front and back
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
* PriorityIntQueue using two dinamic arrays and
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


/*
* PriorityIntQueue using a Binary Search Tree and
* a variable elementQuantity.
* Implementation is unbounded.
*/

struct QueueNode {
	int data;
	unsigned int priority;
	QueueNode* left;
	QueueNode* right;
};

struct PriorityQueue {
	QueueNode* elements;
	unsigned int elementQuantity;
};

/* Auxiliary methods*/

void insertNode(QueueNode*& root, int data, unsigned int priority) {

	QueueNode* t = root;
	QueueNode* p;
	QueueNode* r = NULL;

	// root is empty
	if (root == NULL) {
		p = new QueueNode();
		p->data = data;
		p->priority = priority;
		p->left = NULL;
		p->right = NULL;
		root = p;
		return;
	}

	while (t != NULL) {
		r = t;
		if (priority < t->priority) {
			t = t->left;
		}
		else if (priority > t->priority) {
			t = t->right;
		}
		else {
			return;
		}
	}

	// Now t points at NULL and r points at insert location
	p = new QueueNode();
	p->data = data;
	p->priority = priority;
	p->left = NULL;
	p->right = NULL;

	if (priority < r->priority) {
		r->left = p;
	}
	else {
		r->right = p;
	}
}

bool elementDefined(QueueNode* r, unsigned int p) {
	if (r == NULL) {
		return false;
	}
	if (r->priority == p) {
		return true;
	}
	if (p < r->priority) {
		return elementDefined(r->left, p);
	}
	else {
		return elementDefined(r->right, p);
	}
}

unsigned int maxPriority(QueueNode* r) {

	if (r == NULL) {
		return 0;
	}
	else {
		while (r->right != NULL) {
			r = r->right;
		}
		return r->priority;
	}
}

void deleteNode(QueueNode*& root, unsigned int p) {
	if (root != NULL) {
		if (p < root->priority) {
			deleteNode(root->left, p);
		}
		else if (p > root->priority) {
			deleteNode(root->right, p);
		}
		else {
			//node with priority p is found
			if (root->left == NULL) {
				QueueNode* nodeToDelete = root;
				root = root->right;
				delete nodeToDelete;
			}
			else if (root->right == NULL) {
				QueueNode* nodeToDelete = root;
				root = root->left;
				delete nodeToDelete;
			}
			else {
				unsigned int max = maxPriority(root->left);
				root->priority = max;
				deleteNode(root->left, max);
			}
		}
	}
}

QueueNode* clone(QueueNode* r) {
	if (r == NULL) {
		return NULL;
	}
	else {
		QueueNode* clonedNode = new QueueNode();
		clonedNode->data = r->data;
		clonedNode->priority = r->priority;
		clonedNode->left = clone(r->left);
		clonedNode->right = clone(r->right);
		return clonedNode;
	}
}

void displayData(QueueNode* r) {
	if (r != NULL) {
		displayData(r->left);
		cout << r->data << "|" << r->priority << flush;
		cout << endl;
		displayData(r->right);
	}
}

/* End of auxiliary methods*/

PriorityQueue* createQueue() {
	PriorityQueue* pq = new PriorityQueue();
	pq->elements = NULL;
	pq->elementQuantity = 0;
	return pq;
}

bool insertElement(PriorityQueue* &pq, int e, unsigned int p) {
	if (!elementDefined(pq->elements, p)) {
		insertNode(pq->elements, e, p);
		pq->elementQuantity++;
		return true;
	}
	else {
		return false;
	}
}

bool isEmpty(PriorityQueue* pq) {
	return pq->elementQuantity == 0;
}

unsigned int deleteElement(PriorityQueue* &pq) {
	if (!isEmpty(pq)) {
		unsigned int maxPriorityValue = maxPriority(pq->elements);
		deleteNode(pq->elements, maxPriorityValue);
		pq->elementQuantity--;
		return maxPriorityValue;
	}
}

unsigned int numberOfElements(PriorityQueue* pq) {
	return pq->elementQuantity;
}

PriorityQueue* clone(PriorityQueue* pq) {
	PriorityQueue* clonedQueue = createQueue();
	if (isEmpty(pq)) {
		return clonedQueue;
	}
	else {
		clonedQueue->elements = clone(pq->elements);
		clonedQueue->elementQuantity = pq->elementQuantity;
		return clonedQueue;
	}
}

void display(PriorityQueue* pq) {
	displayData(pq->elements);
}

/*
* CustomIntQueue using two pointers called front and back
* and a variable elementQuantity.
* Implementation is unbounded.
*/

struct CustomQueueNode {
	int data;
	CustomQueueNode* next;
};

struct CustomIntQueue {
	CustomQueueNode* front;
	CustomQueueNode* back;
	unsigned int elementQuantity;
};

CustomIntQueue* create() {
	CustomIntQueue* cq = new CustomIntQueue();
	cq->front = NULL;
	cq->back = NULL;
	cq->elementQuantity = 0;
	return cq;
}

bool isEmpty(CustomIntQueue* cq) {
	return cq->elementQuantity == 0;
}

void insert(int x, CustomIntQueue*& cq) {
	CustomQueueNode* n = new CustomQueueNode();
	n->data = x;
	n->next = NULL;
	if (isEmpty(cq)) {
		cq->front = n;
		cq->back = n;
	}
	else {
		cq->back->next = n;
		cq->back = n;
	}
	cq->elementQuantity++;
}

int deleteElement(CustomIntQueue*& cq) {
	if (!isEmpty(cq)) {
		int element = cq->front->data;
		CustomQueueNode* nodeToDelete = cq->front;
		cq->front = cq->front->next;
		if (cq->front == NULL) {
			cq->back = NULL;
		}
		delete nodeToDelete;
		cq->elementQuantity--;
		return element;
	}
}

void destroyQueue(CustomIntQueue*& cq) {
	if (!isEmpty(cq)) {
		while (cq->front != NULL) {
			CustomQueueNode* nodeToDelete = cq->front;
			cq->front = cq->front->next;
			delete nodeToDelete;
			cq->elementQuantity--;
		}
	}
	delete cq;
}

void display(CustomIntQueue* cq) {
	if (!isEmpty(cq)) {
		while (cq->front != NULL) {
			cout << cq->front->data << " ";
			cq->front = cq->front->next;
		}
		cout << endl;
	}
}

int timesRepeated(CustomIntQueue*& c, int x) {
	if (isEmpty(c)) {
		return 0;
	}
	else {
		int quantity = 0;
		CustomIntQueue* auxQueue = create();
		while (!isEmpty(c)) {
			int lastElement = deleteElement(c);
			if (lastElement == x) {
				quantity++;
			}
			insert(lastElement, auxQueue);
		}
		while (!isEmpty(auxQueue)) {
			int lastElement = deleteElement(auxQueue);
			insert(lastElement, c);
		}
		destroyQueue(auxQueue);
		return quantity;
	}
}

bool deleteRepeatedElement(CustomIntQueue*& c, int x) {
	if (isEmpty(c)) {
		return false;
	}
	else {
		CustomIntQueue* auxQueue = create();
		int auxElement = 0;
		int elementRepeated = INT_MIN;

		if (timesRepeated(c, x) > 1) {
			elementRepeated = x;

			while (!isEmpty(c)) {
				int lastElement = deleteElement(c);
				if (lastElement != elementRepeated) {
					insert(lastElement, auxQueue);
				}
			}
			while (!isEmpty(auxQueue)) {
				auxElement = deleteElement(auxQueue);
				insert(auxElement, c);
			}
			return true;
		}
		else {
			return false;
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

	//display(pq);

	PriorityQueue* p = createQueue();

	insertElement(p, 1, 4);
	insertElement(p, 3, 5);
	insertElement(p, 5, 9);
	insertElement(p, 7, 1);

	//cout << deleteElement(p);

	//display(p);

	CustomIntQueue* cq = create();
	insert(8, cq);
	insert(3, cq);
	insert(4, cq);
	insert(3, cq);
	insert(6, cq);
	insert(7, cq);
	insert(9, cq);
	insert(3, cq);

	//deleteElement(cq);

	//destroyQueue(cq);

	deleteRepeatedElement(cq,3);

	display(cq);

	return 0;
}
