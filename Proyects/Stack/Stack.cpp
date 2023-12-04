#include <iostream>

using namespace std;

/*
* IntStack using a LinkedList and a variable elementQuantity.
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
	if (isEmpty(s)) {
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

/*
* Custom IntStack using a pointer.
  Implementation is unbounded.
*/

struct CustomIntStack {
	NodeList* elements;
	unsigned int elementQuantity;
};

CustomIntStack* createCustomIntStack() {
	CustomIntStack* cs = new CustomIntStack();
	cs->elements = NULL;
	cs->elementQuantity = 0;
	return cs;
}

void insertElement(int x, CustomIntStack* &cs) {
	NodeList* node = new NodeList();
	node->data = x;
	node->next = cs->elements;
	cs->elements = node;
	cs->elementQuantity++;
}

bool isEmpty(CustomIntStack* cs) {
	return cs->elementQuantity == 0;
}

int deleteElement(CustomIntStack*& cs) {
	if (!isEmpty(cs)) {
		int data = cs->elements->data;
		NodeList* nodeToDelete = cs->elements;
		cs->elements = cs->elements->next;
		delete nodeToDelete;
		cs->elementQuantity--;
		return data;
	}
}

void destroyStack(CustomIntStack*& cs) {
	if (!isEmpty(cs)) {
		NodeList* iterator = cs->elements;
		while (iterator != NULL) {
			NodeList* nodeToDelete = iterator;
			iterator = iterator->next;
			delete nodeToDelete;
			cs->elementQuantity--;
		}
	}
	delete cs;
}

void display(CustomIntStack* c) {
	NodeList* iterator = c->elements;
	while (iterator != NULL) {
		cout << iterator->data << " ";
		iterator = iterator->next;
	}
	cout << endl;
}

void deleteRepeated(CustomIntStack*& s) {
	if (!isEmpty(s)) {
		CustomIntStack* auxStack = createCustomIntStack();
		int auxElement = 0;
		while (!isEmpty(s)) {
			int lastElement = deleteElement(s);
			if(auxElement != lastElement){
				auxElement = lastElement;
				insertElement(auxElement, auxStack);
			}
		}
		while (!isEmpty(auxStack)) {
			insertElement(deleteElement(auxStack), s);
		}
		destroyStack(auxStack);
	}
}

/*Custom Stack using one pointer and a 
* variable elementQuantity.
* Push, pop, top, isEmpty and isFull are
* made in O(1) in the worst case.
* Implementation is bounded.
*/

struct StackNode {
	int data;
	StackNode* next;
};

struct CustomStack {
	StackNode* elements;
	unsigned int elementQuantity;
	unsigned int capacity;
};

CustomStack* create(unsigned int capacity) {
	CustomStack* cs = new CustomStack();
	cs->capacity = capacity;
	cs->elementQuantity = 0;
	cs->elements = NULL;
	return cs;
}

bool isEmpty(CustomStack* cs) {
	return cs->elementQuantity == 0;
}

bool isFull(CustomStack* cs) {
	return cs->elementQuantity == cs->capacity;
}

void push(CustomStack*& cs, int e) {
	if (!isFull(cs)) {
		StackNode* node = new StackNode();
		node->data = e;
		node->next = cs->elements;
		cs->elements = node;
		cs->elementQuantity++;
	}
}

int top(CustomStack* cs) {
	if (!isEmpty(cs)) {
		return cs->elements->data;
	}
}

void pop(CustomStack*& cs) {
	if (!isEmpty(cs)) {
		StackNode* nodeToDelete = cs->elements;
		cs->elements = cs->elements->next;
		delete nodeToDelete;
		cs->elementQuantity--;
	}
}

void display(CustomStack* cs) {
	StackNode* iterator = cs->elements;
	while (iterator != NULL) {
		cout << iterator->data << " ";
		iterator = iterator->next;
	}
	cout << endl;
}

CustomStack* sortStack(CustomStack* cs) {
	CustomStack* sortedStack = create(cs->capacity);
	if (!isEmpty(cs)) {
		while (!isEmpty(cs)) {
			int element = top(cs);
			pop(cs);
			while (!isEmpty(sortedStack) && top(sortedStack) < element) {
				push(cs, top(sortedStack));
				pop(sortedStack);
			}
			push(sortedStack, element);
		}
		return sortedStack;
	}
	else {
		return sortedStack;
	}
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

	CustomIntStack* c = createCustomIntStack();
	insertElement(9, c);
	insertElement(9, c);
	insertElement(7, c);
	insertElement(6, c);
	insertElement(3, c);
	insertElement(3, c);
	insertElement(3, c);
	insertElement(2, c);

	deleteRepeated(c);

	//display(c);

	//display(clonedStack);

	CustomStack* cs = create(10);
	push(cs, 4);
	push(cs, 7);
	push(cs, 15);
	push(cs, 2);
	push(cs, 9);
	push(cs, 3);
	push(cs, 1);

	//pop(cs);

	//display(cs);

	CustomStack* sortedStack = sortStack(cs);

	display(sortedStack);

	return 0;
}

