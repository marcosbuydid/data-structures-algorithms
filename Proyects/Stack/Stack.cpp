#include <iostream>

using namespace std;

/*
* IntStack using LinkedList and a variable elementQuantity.
* Push, Top, Pop and numberOfEelements operations are made
* in constant order in the worst case.
* Implementation is unbounded.
*/

struct NodeList {
	int data;
	NodeList* next;
};

struct IntStack {
	NodeList* list;
	int elementQuantity;
};

IntStack* createIntStack() {
	IntStack* s = new IntStack();
	s->list = NULL;
	s->elementQuantity = 0;
	return s;
}

bool isEmpty(IntStack* s) {
	return s->elementQuantity == 0;
}

void push(IntStack*& s, int x) {
	if (isEmpty(s)) {
		s = createIntStack();
	}
	NodeList* node = new NodeList();
	node->data = x;
	node->next = s->list;
	s->list = node;
	s->elementQuantity++;
};

int top(IntStack* s) {
	if (!isEmpty(s)) {
		return s->list->data;
	}
}

void pop(IntStack*& s) {
	if (!isEmpty(s)) {
		NodeList* nodeToDelete = s->list;
		s->list = s->list->next;
		delete nodeToDelete;
		s->elementQuantity--;
	}
}

int numberOfElements(IntStack* s) {
	return s->elementQuantity;
}

void destroy(IntStack*& s) {
	if (isEmpty(s)) {
		delete s;
	}
	else {
		while (s->list != NULL) {
			NodeList* nodeToDelete = s->list;
			s->list = s->list->next;
			delete nodeToDelete;
		}
		delete s;
	}
}

IntStack* clone(IntStack* s) {
	IntStack* clone = createIntStack();
	if (s->list == NULL) {
		return clone;
	}
	else {
		IntStack* aux = createIntStack();
		NodeList* iterator = s->list;
		while (iterator != NULL) {
			push(aux, iterator->data);
			iterator = iterator->next;
		}
		iterator = aux->list;
		while (iterator != NULL) {
			push(clone, iterator->data);
			iterator = iterator->next;
		}
		destroy(aux);
		return clone;
	}
}

void display(IntStack* s) {
	NodeList* iterator = s->list;
	while (iterator != NULL) {
		cout << iterator->data << " ";
		iterator = iterator->next;
	}
	cout << endl;
}


int main()
{
	IntStack* s = createIntStack();

	push(s, 10);
	push(s, 20);
	push(s, 30);
	push(s, 40);
	push(s, 50);

	//pop(s);

	//cout << numberOfElements(s);

	//display(s);

	IntStack* clonedStack = clone(s);

	display(clonedStack);
}

