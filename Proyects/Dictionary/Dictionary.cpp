#include <iostream>

using namespace std;

/*
* IntDictionary using a pointer to a pointer of a NodeList
* and two variables, capacity and elementQuantity.
* Add, erase and belongs operations are made in O(1) on average.
* Open hashing is used with module operation suited as hash function.
* Implementation is unbounded.
*/

struct NodeList {
	int data;
	NodeList* next;
};

struct IntDictionary {
	NodeList** keys;
	unsigned int capacity;
	unsigned int elementQuantity;
};

/*Auxiliary methods */

int modHash(int element, int capacity) {
	//capacity should be prime
	int position = element % capacity;
	if (position < 0) {
		position = position * -1;
	}
	return position;
}

void addElement(NodeList*& list, int e) {
	NodeList* node = new NodeList();
	node->data = e;
	node->next = list;
	list = node;
}

NodeList* cloneList(NodeList* list) {
	if (list == NULL) {
		return NULL;
	}
	else {
		NodeList* clonedList = new NodeList();
		clonedList->data = list->data;
		clonedList->next = cloneList(list->next);
		return clonedList;
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
	}
}

void displayData(NodeList* l) {
	if (l == NULL) {
		return;
	}
	else {
		cout << l->data << " ";
		displayData(l->next);
	}
}

/*End of auxiliary methods */

IntDictionary* createIntDictionary(unsigned int quantity) {
	IntDictionary* dictionary = new IntDictionary();
	dictionary->capacity = quantity;
	dictionary->elementQuantity = 0;
	dictionary->keys = new NodeList* [quantity];

	//initialize the table
	for (int i = 0;i < quantity;i++) {
		dictionary->keys[i] = NULL;
	}
	return dictionary;
}

bool isEmpty(IntDictionary* dictionary) {
	return dictionary->elementQuantity == 0;
}

int numberOfElements(IntDictionary* dictionary) {
	return dictionary->elementQuantity;
}

bool belongs(IntDictionary* dictionary, int e) {
	if (isEmpty(dictionary)) {
		return false;
	}
	else {
		int elementKey = modHash(e, dictionary->capacity);
		NodeList* aux = dictionary->keys[elementKey];
		while (aux != NULL) {
			if (aux->data == e) {
				return true;
			}
			aux = aux->next;
		}
		return false;
	}
}

void add(IntDictionary*& dictionary, int e) {
	int elementKey = modHash(e, dictionary->capacity);
	if (!belongs(dictionary, e)) {
		addElement(dictionary->keys[elementKey], e);
		dictionary->elementQuantity++;
	}
}

void erase(IntDictionary*& dictionary, int e) {
	int elementKey = modHash(e, dictionary->capacity);
	if (belongs(dictionary, e)) {
		NodeList* actualNode = dictionary->keys[elementKey];
		NodeList* previousNode = NULL;

		while (actualNode != NULL && actualNode->data != e) {
			previousNode = actualNode;
			actualNode = actualNode->next;
		}
		if (previousNode != NULL) {
			previousNode->next = actualNode->next;
		}
		else {
			dictionary->keys[elementKey] = actualNode->next;
			delete actualNode;
		}
		dictionary->elementQuantity--;
	}
}

int element(IntDictionary*& dictionary) {
	if (!isEmpty(dictionary)) {
		//return the first element found
		for (int i = 0; i < dictionary->capacity; i++) {
			if (dictionary->keys[i] != NULL) {
				return dictionary->keys[i]->data;
			}
		}
	}
}

IntDictionary* clone(IntDictionary* dictionary) {
	IntDictionary* clonedDictionary = createIntDictionary(dictionary->capacity);
	if (isEmpty(dictionary)) {
		return clonedDictionary;
	}
	else {
		for (int i = 0; i < dictionary->capacity; i++) {
			clonedDictionary->keys[i] = cloneList(dictionary->keys[i]);
		}
		clonedDictionary->elementQuantity = dictionary->elementQuantity;
		return clonedDictionary;
	}
}

void destroy(IntDictionary*& dictionary) {
	for (int i = 0; i < dictionary->capacity; i++) {
		destroyList(dictionary->keys[i]);
	}
	delete dictionary->keys;
	dictionary->capacity = 0;
	dictionary->elementQuantity = 0;
}

void display(IntDictionary*& id) {
	if (!isEmpty(id)) {
		for (int i = 0; i < id->capacity; i++) {
			cout << i << "-";
			displayData(id->keys[i]);
		}
	}
}


int main() {

	IntDictionary* d = createIntDictionary(13);
	add(d, 987654329);
	add(d, 987456123);
	add(d, 123098564);
	add(d, 123421456);
	add(d, 123651456);
	add(d, 123653456);

	//erase(d, 123653456);

	//IntDictionary* clonedDictionary = clone(d);

	//destroy(clonedDictionary);

	display(d);
}

