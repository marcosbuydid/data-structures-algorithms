#include <iostream>

using namespace std;

/*
* IntMultiset using a pointer called list and a variable
* elementQuantity.
* Implementation is unbounded.
*/

struct NodeList {
	int data;
	NodeList* next;
};

struct IntMultiset {
	NodeList* container;
	unsigned int elementQuantity;
};

/* Auxiliary methods */

void addOrdered(NodeList*& list, int e) {
	if (list == NULL || list->data > e) {
		NodeList* node = new NodeList();
		node->data = e;
		node->next = list;
		list = node;
	}
	else {
		addOrdered(list->next, e);
	}
}

void eraseElement(NodeList*& list, int e) {
	if (list == NULL) {
		return;
	}
	else {
		if (list->data == e) {
			NodeList* nodeToDelete = list;
			list = list->next;
			delete nodeToDelete;
		}
		else {
			eraseElement(list->next, e);
		}
	}
}

NodeList* cloneList(NodeList* l) {
	if (l == NULL) {
		return NULL;
	}
	else {
		NodeList* result = new NodeList();
		result->data = l->data;
		result->next = cloneList(l->next);
		return result;
	}
}

void destroyList(NodeList*& list) {
	if (list != NULL) {
		destroyList(list->next);
		delete list;
		list = NULL;
	}
}

/* End of auxiliary methods */

IntMultiset* createIntMultiset() {
	IntMultiset* m = new IntMultiset();
	m->container = NULL;
	m->elementQuantity = 0;
	return m;
}

bool isEmpty(IntMultiset* m) {
	return m->elementQuantity == 0;
}

void add(IntMultiset*& m, int e, unsigned int occurrences) {
	if (isEmpty(m)) {
		m = createIntMultiset();
	}
	while (occurrences > 0) {
		addOrdered(m->container, e);
		m->elementQuantity++;
		occurrences--;
	}
}

bool belongs(IntMultiset* m, int e) {
	if (isEmpty(m)) {
		return false;
	}
	else {
		NodeList* aux = m->container;
		while (aux != NULL) {
			if (aux->data == e) {
				return true;
			}
			aux = aux->next;
		}
		return false;
	}
}

void erase(IntMultiset*& m, int e) {
	if (belongs(m, e)) {
		eraseElement(m->container, e);
		m->elementQuantity--;
	}
}

int element(IntMultiset* m) {
	if (!isEmpty(m)) {
		NodeList* aux = m->container;
		if (aux != NULL) {
			return aux->data;
		}
	}
}

unsigned int numberOfElements(IntMultiset* m) {
	return m->elementQuantity;
}

IntMultiset* unionSet(IntMultiset* m1, IntMultiset* m2) {

	IntMultiset* result = createIntMultiset();

	NodeList* iteratorM1 = m1->container;
	NodeList* iteratorM2 = m2->container;

	while (iteratorM1 != NULL && iteratorM2 != NULL) {
		if (iteratorM1->data == iteratorM2->data) {
			addOrdered(result->container, iteratorM1->data);
			result->elementQuantity++;
			iteratorM1 = iteratorM1->next;
			iteratorM2 = iteratorM2->next;
		}
		else if (iteratorM1->data < iteratorM2->data) {
			addOrdered(result->container, iteratorM1->data);
			iteratorM1 = iteratorM1->next;
			result->elementQuantity++;
		}
		else {
			addOrdered(result->container, iteratorM2->data);
			iteratorM2 = iteratorM2->next;
			result->elementQuantity++;
		}
	}

	while (iteratorM1 != NULL) {
		addOrdered(result->container, iteratorM1->data);
		iteratorM1 = iteratorM1->next;
		result->elementQuantity++;
	}

	while (iteratorM2 != NULL) {
		addOrdered(result->container, iteratorM2->data);
		iteratorM2 = iteratorM2->next;
		result->elementQuantity++;
	}
	return result;
}

IntMultiset* intersectionSet(IntMultiset* m1, IntMultiset* m2) {

	IntMultiset* result = createIntMultiset();

	NodeList* iteratorM1 = m1->container;
	NodeList* iteratorM2 = m2->container;

	while (iteratorM1 != NULL && iteratorM2 != NULL) {
		if (iteratorM1->data == iteratorM2->data) {
			addOrdered(result->container, iteratorM1->data);
			result->elementQuantity++;
			iteratorM1 = iteratorM1->next;
			iteratorM2 = iteratorM2->next;
		}
		else if (iteratorM1->data < iteratorM2->data) {
			iteratorM1 = iteratorM1->next;
		}
		else {
			iteratorM2 = iteratorM2->next;
		}
	}
	return result;
}

IntMultiset* differenceSet(IntMultiset* m1, IntMultiset* m2) {

	IntMultiset* result = createIntMultiset();

	NodeList* iteratorM1 = m1->container;
	NodeList* iteratorM2 = m2->container;

	while (iteratorM1 != NULL && iteratorM2 != NULL) {
		if (iteratorM1->data == iteratorM2->data) {
			iteratorM1 = iteratorM1->next;
			iteratorM2 = iteratorM2->next;
		}
		else if (iteratorM1->data < iteratorM2->data) {
			addOrdered(result->container, iteratorM1->data);
			result->elementQuantity++;
			iteratorM1 = iteratorM1->next;
		}
		else {
			iteratorM2 = iteratorM2->next;
		}
	}

	while (iteratorM1 != NULL) {
		addOrdered(result->container, iteratorM1->data);
		iteratorM1 = iteratorM1->next;
		result->elementQuantity++;
	}

	while (iteratorM2 != NULL) {
		addOrdered(result->container, iteratorM2->data);
		iteratorM2 = iteratorM2->next;
		result->elementQuantity++;
	}

	return result;
}

bool containedIn(IntMultiset* m1, IntMultiset* m2) {
	IntMultiset* intersection = intersectionSet(m1, m2);

	NodeList* iteratorM1 = m1->container;
	NodeList* intersectionIterator = intersection->container;

	while (iteratorM1 != NULL && intersectionIterator != NULL) {
		if (iteratorM1->data == intersectionIterator->data) {
			iteratorM1 = iteratorM1->next;
			intersectionIterator = intersectionIterator->next;
		}
		else {
			return false;
		}
	}
	return true;
}

IntMultiset* clone(IntMultiset* m) {
	IntMultiset* multisetClone = createIntMultiset();
	if (isEmpty(m)) {
		return multisetClone;
	}
	else {
		multisetClone->container = cloneList(m->container);
		multisetClone->elementQuantity = m->elementQuantity;
		return multisetClone;
	}
}

void destroy(IntMultiset*& m) {
	destroyList(m->container);
	delete m;
	m = NULL;
}

IntMultiset* Xor(IntMultiset* m1, IntMultiset* m2) {
	IntMultiset* diffM1M2 = differenceSet(m1, m2);
	IntMultiset* diffM2M1 = differenceSet(m2, m1);

	return unionSet(diffM2M1, diffM1M2);
}

void display(IntMultiset* m) {
	if (!isEmpty(m)) {
		NodeList* aux = m->container;
		while (aux != NULL) {
			cout << aux->data << " ";
			aux = aux->next;
		}
		cout << endl;
	}
}

/*
* IntMultiset using a Binary Search Tree and a variable
* elementQuantity.
* Implementation is unbounded.
*/

struct MultisetNode {
	int data;
	unsigned int occurrences;
	MultisetNode* left;
	MultisetNode* right;
};

struct CustomIntMultiset {
	MultisetNode* container;
	unsigned int elementQuantity;
	int maxValue;
	int minValue;
};

/* Auxiliary Methods */

void insertNode(MultisetNode*& root, int data, unsigned int occurrences) {

	MultisetNode* t = root;
	MultisetNode* p;
	MultisetNode* r = NULL;

	// root is empty
	if (root == NULL) {
		p = new MultisetNode();
		p->data = data;
		p->occurrences = occurrences;
		p->left = NULL;
		p->right = NULL;
		root = p;
		return;
	}

	if (root->data == data) {
		root->occurrences += occurrences;
	}

	while (t != NULL) {
		r = t;
		if (data < t->data) {
			t = t->left;
		}
		else if (data > t->data) {
			t = t->right;
		}
		else {
			return;
		}
	}

	// Now t points at NULL and r points at insert location
	p = new MultisetNode();
	p->data = data;
	p->occurrences = occurrences;
	p->left = NULL;
	p->right = NULL;

	if (data < r->data) {
		r->left = p;
	}
	else {
		r->right = p;
	}
}

MultisetNode* searchNode(MultisetNode* m, int x) {
	if (m == NULL) {
		return NULL;
	}
	else if (m->data == x) {
		return m;
	}
	else if (x < m->data) {
		return searchNode(m->left, x);
	}
	else {
		return searchNode(m->right, x);
	}
}

int minimumNode(MultisetNode* m) {
	if (m != NULL) {
		while (m->left != NULL) {
			m = m->left;
		}
		return m->data;
	}
}

int maximumNode(MultisetNode* m) {
	if (m != NULL) {
		while (m->right != NULL) {
			m = m->right;
		}
		return m->data;
	}
}

void deleteNode(MultisetNode*& root, int x) {
	if (root != NULL) {
		if (x < root->data) {
			deleteNode(root->left, x);
		}
		else if (x > root->data) {
			deleteNode(root->right, x);
		}
		else {
			if (root->left == NULL) {
				MultisetNode* nodeToDelete = root;
				root = root->right;
				delete nodeToDelete;
			}
			else if (root->right == NULL) {
				MultisetNode* nodeToDelete = root;
				root = root->left;
				delete nodeToDelete;
			}
			else {
				unsigned int max = maximumNode(root->left);
				root->data = max;
				deleteNode(root->left, max);
			}
		}
	}
}

void displayData(MultisetNode* n) {
	if (n != NULL) {
		displayData(n->left);
		cout << n->data << "|" << n->occurrences << flush;
		cout << endl;
		displayData(n->right);
	}
}

/* End of Auxiliary Methods*/

CustomIntMultiset* createCustomIntMultiset() {
	CustomIntMultiset* cm = new CustomIntMultiset();
	cm->container = NULL;
	cm->elementQuantity = 0;
	cm->minValue = INT_MAX;
	cm->maxValue = INT_MIN;
	return cm;
}

void insert(CustomIntMultiset* &cm, int x, unsigned int n) {
	insertNode(cm->container, x, n);

	if (x < cm->minValue) {
		cm->minValue = x;
	}
	if (x > cm->maxValue) {
		cm->maxValue = x;
	}
	cm->elementQuantity++;
}

unsigned int numberOfElements(CustomIntMultiset* cm) {
	return cm->elementQuantity;
}

bool isEmpty(CustomIntMultiset* cm) {
	return cm->elementQuantity == 0;
}

unsigned int occurrences(CustomIntMultiset* cm, int x) {
	if (isEmpty(cm)) {
		return 0;
	}
	else {
		MultisetNode* node = searchNode(cm->container, x);
		if (node == NULL) {
			return 0;
		}
		else {
			return node->occurrences;
		}
	}
}

void deleteOcurrence(CustomIntMultiset*& cm, int x, unsigned int n) {
	if (occurrences(cm, x) <= n) {
		deleteNode(cm->container, x);
		cm->minValue = minimumNode(cm->container);
		cm->maxValue = maximumNode(cm->container);
		cm->elementQuantity--;
	}
	else {
		MultisetNode* node = searchNode(cm->container, x);
		if (node != NULL) {
			node->occurrences -= n;
		}
	}
}

int minimum(CustomIntMultiset* cm) {
	if (!isEmpty(cm)) {
		return cm->minValue;
	}
}

int maximum(CustomIntMultiset* cm) {
	if (!isEmpty(cm)) {
		return cm->maxValue;
	}
}

void display(CustomIntMultiset* cm) {
	displayData(cm->container);
}

void clearOutMultiset(CustomIntMultiset* &cm) {
	while (!isEmpty(cm)) {
		int minimumNodeValue = minimum(cm);
		int nodeOccurrence = occurrences(cm, minimumNodeValue);
		deleteOcurrence(cm, minimumNodeValue, nodeOccurrence);
	}
}

bool areSimilars(CustomIntMultiset* cm1, CustomIntMultiset* cm2) {

	bool result = false;

	while (!isEmpty(cm1) && !isEmpty(cm2)) {
		int minimumNodeValueCm1 = minimum(cm1);
		int minimumNodeValueCm2 = minimum(cm2);
		int nodeOccurrenceCm1 = occurrences(cm1, minimumNodeValueCm1);
		int nodeOccurrenceCm2 = occurrences(cm2, minimumNodeValueCm2);

		if (minimumNodeValueCm1 == minimumNodeValueCm2 &&
			nodeOccurrenceCm1 == nodeOccurrenceCm2) {
			result = true;
		}
		deleteOcurrence(cm1, minimumNodeValueCm1, nodeOccurrenceCm1);
		deleteOcurrence(cm2, minimumNodeValueCm1, nodeOccurrenceCm2);
	}

	return result;
}


int main() {

	IntMultiset* multiset1 = createIntMultiset();
	add(multiset1, 1, 4);
	add(multiset1, 2, 2);
	add(multiset1, 4, 2);

	IntMultiset* multiset2 = createIntMultiset();
	add(multiset2, 1, 1);
	add(multiset2, 2, 1);
	add(multiset2, 3, 2);

	IntMultiset* unionSetResult = unionSet(multiset1, multiset2);

	IntMultiset* intersectionSetResult = intersectionSet(multiset1, multiset2);

	IntMultiset* differenceSetResult = differenceSet(multiset1, multiset2);

	bool result = containedIn(multiset1, multiset2);

	IntMultiset* cloneM3 = clone(multiset2);

	IntMultiset* XOR = Xor(multiset1, multiset2);

	//display(XOR);

	CustomIntMultiset* cm = createCustomIntMultiset();

	insert(cm, 1, 4);
	insert(cm, 1, 10);
	insert(cm, 3, 21);
	insert(cm, 12, 43);
	insert(cm, 7, 14);

	//cout << occurrences(cm, 12);

	//cout << maximum(cm);

	//cout << minimum(cm);

	//deleteOcurrence(cm, 12, 6);

	//deleteOcurrence(cm, 3, 21);

	//clearOutMultiset(cm);

	CustomIntMultiset* cm1 = createCustomIntMultiset();
	insert(cm1, 1, 4);
	insert(cm1, 2, 2);
	insert(cm1, 4, 2);

	CustomIntMultiset* cm2 = createCustomIntMultiset();
	insert(cm2, 1, 1);
	insert(cm2, 2, 1);
	insert(cm2, 3, 2);

	CustomIntMultiset* cm3 = createCustomIntMultiset();
	insert(cm3, 1, 4);
	insert(cm3, 2, 2);
	insert(cm3, 4, 2);

	cout << areSimilars(cm1,cm3);

	//display(cm);

	return 0;
}
