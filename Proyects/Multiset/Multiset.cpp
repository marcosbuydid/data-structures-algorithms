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
	NodeList* set;
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
	if (list == NULL) {
		return;
	}
	else {
		while (list != NULL) {
			NodeList* nodeToDelete = list;
			list = list->next;
			delete nodeToDelete;
		}
		delete list;
		list = NULL;
	}
}

/* End of auxiliary methods */

IntMultiset* createIntMultiset() {
	IntMultiset* m = new IntMultiset();
	m->set = NULL;
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
		addOrdered(m->set, e);
		m->elementQuantity++;
		occurrences--;
	}
}

bool belongs(IntMultiset* m, int e) {
	if (isEmpty(m)) {
		return false;
	}
	else {
		while (m->set != NULL) {
			NodeList* aux = m->set;
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
		eraseElement(m->set, e);
		m->elementQuantity--;
	}
}

int element(IntMultiset* m) {
	if (!isEmpty(m)) {
		NodeList* aux = m->set;
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

	NodeList* iteratorM1 = m1->set;
	NodeList* iteratorM2 = m2->set;

	while (iteratorM1 != NULL && iteratorM2 != NULL) {
		if (iteratorM1->data == iteratorM2->data) {
			iteratorM1 = iteratorM1->next;
			iteratorM2 = iteratorM2->next;
		}
		else if (iteratorM1->data < iteratorM2->data) {
			addOrdered(result->set, iteratorM1->data);
			iteratorM1 = iteratorM1->next;
			result->elementQuantity++;
		}
		else {
			addOrdered(result->set, iteratorM2->data);
			iteratorM2 = iteratorM2->next;
			result->elementQuantity++;
		}
	}

	while (iteratorM1 != NULL) {
		addOrdered(result->set, iteratorM1->data);
		iteratorM1 = iteratorM1->next;
		result->elementQuantity++;
	}

	while (iteratorM2 != NULL) {
		addOrdered(result->set, iteratorM2->data);
		iteratorM2 = iteratorM2->next;
		result->elementQuantity++;
	}
	return result;
}

IntMultiset* intersectionSet(IntMultiset* m1, IntMultiset* m2) {

	IntMultiset* result = createIntMultiset();

	NodeList* iteratorM1 = m1->set;
	NodeList* iteratorM2 = m2->set;

	while (iteratorM1 != NULL && iteratorM2 != NULL) {
		if (iteratorM1->data == iteratorM2->data) {
			addOrdered(result->set, iteratorM1->data);
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

	NodeList* iteratorM1 = m1->set;
	NodeList* iteratorM2 = m2->set;

	while (iteratorM1 != NULL && iteratorM2 != NULL) {
		if (iteratorM1->data == iteratorM2->data) {
			iteratorM1 = iteratorM1->next;
			iteratorM2 = iteratorM2->next;
		}
		else if (iteratorM1->data < iteratorM2->data) {
			addOrdered(result->set, iteratorM1->data);
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

	NodeList* iteratorM1 = m1->set;
	NodeList* intersectionIterator = intersection->set;

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
		multisetClone->set = cloneList(m->set);
		multisetClone->elementQuantity = m->elementQuantity;
		return multisetClone;
	}
}

void destroy(IntMultiset*& m) {
	destroyList(m->set);
	delete m;
	m = NULL;
}

void display(IntMultiset* m) {
	if (!isEmpty(m)) {
		NodeList* aux = m->set;
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

	IntMultiset* unionSetResult = unionSet(multiset1, multiset2);

	IntMultiset* intersectionSetResult = intersectionSet(multiset1, multiset2);

	IntMultiset* differenceSetResult = differenceSet(multiset1, multiset2);

	//display(unionSetResult);

	//display(intersectionSetResult);

	bool result = containedIn(multiset1, multiset3);

	IntMultiset* cloneM3 = clone(multiset3);

	display(cloneM3);

	return 0;
}
