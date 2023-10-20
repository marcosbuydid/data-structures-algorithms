#include <iostream>

using namespace std;

//ADT Stack using LinkedList

class NodeList {
public:
	int data;
	NodeList* next;
};

class IntStack {
private:
	NodeList* list;
	int elementQuantity;
public:
	IntStack() {
		list = NULL;
		elementQuantity = 0;
	}
	void push(int x);
	int top();
	void pop();
	bool isEmpty();
	int numberOfElements();
	void display();
	IntStack clone();
	void destroy();
};

void IntStack::push(int x) {
	NodeList* node = new NodeList();
	node->data = x;
	node->next = list;
	list = node;
	elementQuantity++;
};

int IntStack::top() {
	if (!isEmpty()) {
		return list->data;
	}
}

void IntStack::pop() {
	if (!isEmpty()) {
		NodeList* nodeToDelete = list;
		list = list->next;
		delete nodeToDelete;
		elementQuantity--;
	}
}

bool IntStack::isEmpty() {
	return list == NULL;
}

int IntStack::numberOfElements() {
	return elementQuantity;
}

void IntStack::display() {
	NodeList* iterator = list;

	while (iterator != NULL) {
		cout << iterator->data << " ";
		iterator = iterator->next;
	}
	cout << endl;
}

IntStack IntStack::clone() {
	IntStack clone;
	IntStack aux;
	if (list == NULL) {
		return clone;
	}
	else {
		NodeList* iterator = list;
		while (iterator != NULL) {
			aux.push(iterator->data);
			iterator = iterator->next;
		}
		iterator = aux.list;
		while (iterator != NULL) {
			clone.push(iterator->data);
			iterator = iterator->next;
		}
		aux.destroy();
		return clone;
	}
}

void IntStack::destroy() {
	if (list == NULL) {
		delete list;
	}
	else {
		while (list != NULL) {
			NodeList* nodeToDelete = list;
			list = list->next;
			delete nodeToDelete;
		}
		delete list;
	}
}


int main()
{
	IntStack intStack;

	intStack.push(10);
	intStack.push(20);
	intStack.push(30);
	intStack.push(40);
	intStack.push(50);

	//intStack.pop();

	//cout << intStack.numberOfElements();

	IntStack clone = intStack.clone();

	//intStack.display();
	clone.display();
}

