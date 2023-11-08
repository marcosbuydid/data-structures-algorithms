#include <iostream>

using namespace std;

/*
* IntStringTable using a double pointer called table and two variables,
* capacity and elementQuantity.
* Add, erase, isDefined and recovery operations are made in O(1) on average.
* Open hashing is used with module operation suited as hash function.
* Implementation is unbounded.
*/

struct NodeList {
	int domain;
	char* range;
	NodeList* next;
};

struct IntStringTable {
	NodeList** table;
	unsigned int capacity;
	unsigned int elementQuantity;
};

/* Auxiliary methods*/

int modHash(int element, int capacity) {
	int position = element % capacity;
	if (position < 0) {
		position = position * -1;
	}
	return position;
}

int stringLength(const char* str) {
	const char* strAux = str;
	int length = 0;
	while (strAux[length] != '\0') {
		length++;
	}
	return length;
}

char* copyString(const char* str) {
	int length = stringLength(str);
	char* strCopy = new char[length + 1];

	for (int i = 0;i < length;i++) {
		strCopy[i] = str[i];
	}
	strCopy[length] = '\0';

	return strCopy;
}

NodeList* cloneList(NodeList* l) {
	if (l == NULL) {
		return NULL;
	}
	else {
		NodeList* result = new NodeList();
		result->domain = l->domain;
		result->range = copyString(l->range);
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
	}
}

void displayData(NodeList* l) {
	if (l == NULL) {
		return;
	}
	else {
		cout << l->domain << "|" << l->range << " ";
		displayData(l->next);
	}
}

/*End of auxiliary methods*/

IntStringTable* createTable(unsigned int quantity) {
	IntStringTable* t = new IntStringTable();
	t->capacity = quantity;
	t->elementQuantity = 0;
	t->table = new NodeList * [quantity];
	for (int i = 0; i < quantity; i++) {
		t->table[i] = NULL;
	}
	return t;
}

bool isEmpty(IntStringTable* t) {
	return t->elementQuantity == 0;
}

bool isDefined(IntStringTable* t, int domain) {
	if (isEmpty(t)) {
		return false;
	}
	else {
		int position = modHash(domain, t->capacity);
		NodeList* aux = t->table[position];
		while (aux != NULL) {
			if (aux->domain == domain) {
				return true;
			}
			aux = aux->next;
		}
		return false;
	}
}

void add(IntStringTable*& t, int d, const char* r) {
	int position = modHash(d, t->capacity);
	NodeList* aux = t->table[position];

	while (aux != NULL && aux->domain != d) {
		aux = aux->next;
	}

	if (aux == NULL) {
		NodeList* node = new NodeList();
		node->domain = d;
		node->range = copyString(r);
		node->next = t->table[position];
		t->table[position] = node;
		t->elementQuantity++;
	}
	else {
		aux->range = copyString(r);
	}
}

unsigned int numberOfElements(IntStringTable* t) {
	return t->elementQuantity;
}

int element(IntStringTable* t) {
	if (!isEmpty(t)) {
		//return the first domain found in the table
		for (int i = 0; i < t->capacity; i++) {
			if (t->table[i] != NULL) {
				return t->table[i]->domain;
			}
		}
	}
}

const char* recover(IntStringTable* t, int d) {
	if (isDefined(t, d)) {
		int position = modHash(d, t->capacity);
		NodeList* aux = t->table[position];
		while (aux != NULL) {
			if (aux->domain == d) {
				const char* result = copyString(aux->range);
				return result;
			}
			aux = aux->next;
		}
	}
}

void erase(IntStringTable*& t, int d) {
	int position = modHash(d, t->capacity);
	if (isDefined(t, d)) {
		NodeList* actualNode = t->table[position];
		NodeList* previousNode = NULL;

		while (actualNode != NULL && actualNode->domain != d) {
			previousNode = actualNode;
			actualNode = actualNode->next;
		}
		if (previousNode != NULL) {
			previousNode->next = actualNode->next;
		}
		else {
			t->table[position] = actualNode->next;
			delete actualNode;
		}
		t->elementQuantity--;
	}
}

IntStringTable* clone(IntStringTable*& t) {
	IntStringTable* clonedTable = createTable(t->capacity);
	if (isEmpty(t)) {
		return clonedTable;
	}
	else {
		for (int i = 0; i < t->capacity; i++) {
			NodeList* aux = t->table[i];
			clonedTable->table[i] = cloneList(aux);
		}
		clonedTable->capacity = t->capacity;
		clonedTable->elementQuantity = t->elementQuantity;
		return clonedTable;
	}
}

void destroy(IntStringTable*& t) {
	for (int i = 0; i < t->capacity; i++) {
		destroyList(t->table[i]);
	}
	delete t->table;
	t->capacity = 0;
	t->elementQuantity = 0;
}

void display(IntStringTable* t) {
	if (!isEmpty(t)) {
		for (int i = 0; i < t->capacity; i++) {
			if (t->table[i] != NULL) {
				displayData(t->table[i]);
				cout << endl;
			}
		}
	}
}


int main() {
	IntStringTable* table = createTable(13);

	add(table, 0, "Montevideo");
	add(table, 1, "Artigas");
	add(table, 2, "Durazno");
	add(table, 3, "Salto");
	add(table, 4, "Paysandu");
	add(table, 5, "Tacuarembo");
	add(table, 6, "Maldonado");

	add(table, 6, "Florida");

	//cout << element(table);
	// 
	//cout << recover(table, 4);

	//erase(table, 5);

	//IntStringTable* clonedTable = clone(table);

	//destroy(table);

	display(table);

	return 0;
}