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
		while (aux != NULL) {
			if (aux->data != NULL) {
				return aux->data;
			}
			aux = aux->next;
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

int main() {

	IntMultiset* multiset1 = createIntMultiset();
	add(multiset1, 1, 4);
	add(multiset1, 2, 2);
	add(multiset1, 4, 2);

	IntMultiset* multiset2 = createIntMultiset();
	add(multiset2, 1, 1);
	add(multiset2, 2, 1);
	add(multiset2, 3, 2);

	IntMultiset* multiset3 = createIntMultiset();
	add(multiset3, 1, 4);
	add(multiset3, 2, 2);
	add(multiset3, 4, 2);
	add(multiset3, 6, 2);
	add(multiset3, 8, 2);

	IntMultiset* multiset4 = createIntMultiset();
	add(multiset4, 1, 1);
	add(multiset4, 3, 1);
	add(multiset4, 4, 1);
	add(multiset4, 7, 1);

	IntMultiset* multiset5 = createIntMultiset();
	add(multiset5, 8, 1);
	add(multiset5, 1, 1);
	add(multiset5, 2, 1);
	add(multiset5, 3, 1);

	//IntMultiset* unionSetResult = unionSet(multiset1, multiset2);

	//IntMultiset* intersectionSetResult = intersectionSet(multiset1, multiset2);

	//IntMultiset* differenceSetResult = differenceSet(multiset1, multiset2);

	//display(unionSetResult);

	//display(intersectionSetResult);

	//bool result = containedIn(multiset1, multiset3);

	//IntMultiset* cloneM3 = clone(multiset3);

	//display(cloneM3);

	IntMultiset* XOR = Xor(multiset4, multiset5);

	display(XOR);

	return 0;
}
