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


/*
* IntFloatTable using a double pointer called table and two variables,
* capacity and elementQuantity.
* InsertTable and recoveryTable operations are made in O(1) on average.
* Open hashing is used with module operation suited as hash function.
* Implementation is unbounded.
*/

struct TableNode {
	int domain;
	float range;
	TableNode* next;
};

struct IntFloatTable {
	TableNode** table;
	unsigned int capacity;
	unsigned int elementQuantity;
};

/* Auxiliary methods */
int hashModule(int element, int capacity) {
	int position = element % capacity;
	if (position < 0) {
		position = position * -1;
	}
	return position;
}

void destroyList(TableNode* &list){
	if(list == NULL){
		return;
	}
	else {
		while (list != NULL) {
			TableNode* nodeToDelete = list;
			list = list->next;
			delete nodeToDelete;
		}
	}
	delete list;
	list = NULL;
}

void displayData(TableNode* l) {
	if (l == NULL) {
		return;
	}
	else {
		while (l != NULL) {
			cout << l->domain << "|" << l->range << " ";
			l = l->next;
		}
	}
}

/*End of auxiliary methods*/

IntFloatTable* create(int size) {
	IntFloatTable* t = new IntFloatTable();
	t->capacity = size;
	t->elementQuantity = 0;
	t->table = new TableNode* [size];

	for (int i = 0; i < size; i++) {
		t->table[i] = NULL;
	}
	return t;
}

bool isEmpty(IntFloatTable* t) {
	return t->elementQuantity == 0;
}

void insert(unsigned int d, float r, IntFloatTable*& t) {
	int positionElement = hashModule(d, t->capacity);
	TableNode* aux = t->table[positionElement];

	if (aux == NULL) {
		TableNode* node = new TableNode();
		node->domain = d;
		node->range = r;
		node->next = t->table[positionElement];
		t->table[positionElement] = node;
		t->elementQuantity++;
	}
	else {
		while (aux != NULL) {
			if (aux->domain == d) {
				aux->range = r;
			}
			aux = aux->next;
		}
	}
}

bool isDefined(unsigned int d, IntFloatTable* t) {
	if (isEmpty(t)) {
		return false;
	}
	else {
		int elementPosition = hashModule(d, t->capacity);
		TableNode* aux = t->table[elementPosition];
		while (aux != NULL) {
			if (aux->domain == d) {
				return true;
			}
			aux = aux->next;
		}
		return false;
	}
}

int numberOfElements(IntFloatTable* t) {
	return t->elementQuantity;
}

float recover(unsigned int d, IntFloatTable* t) {
	if (isDefined(d, t)) {
		int elementPosition = hashModule(d, t->capacity);
		TableNode* aux = t->table[elementPosition];
		while (aux != NULL) {
			if (aux->domain == d) {
				return aux->range;
			}
			aux = aux->next;
		}
	}
	else {
		return 0.0;
	}
}

void deleteElement(unsigned int d, IntFloatTable*& t) {
	if (isDefined(d, t)) {
		int elementPosition = hashModule(d, t->capacity);
		while (t->table[elementPosition] != NULL) {
			if (t->table[elementPosition]->domain == d) {
				TableNode* nodeToDelete = t->table[elementPosition];
				t->table[elementPosition] = t->table[elementPosition]->next;
				delete nodeToDelete;
				t->elementQuantity--;
			}
			if (t->table[elementPosition] != NULL) {
				t->table[elementPosition] = t->table[elementPosition]->next;
			}
		}
	}
}

void destroyTable(IntFloatTable* t) {
	for (int i = 0; i < t->capacity; i++) {
		destroyList(t->table[i]);
	}
	t->elementQuantity = 0;
	t->capacity = 0;
	delete t->table;
}

void displayTable(IntFloatTable* t) {
	if (!isEmpty(t)) {
		for (int i = 0; i < t->capacity;i++) {
			if (t->table[i] != NULL) {
				displayData(t->table[i]);
				cout << endl;
			}
		}
	}
}

IntFloatTable* consolidateTables(IntFloatTable* t1, IntFloatTable* t2, int inf, int sup) {
	if (sup < inf) {
		return NULL;
	}
	else {
		int tableSize = max(t1->capacity, t2->capacity);
		IntFloatTable* result = create(tableSize);
		for (int i = inf; i < sup;i++) {
			if (isDefined(i, t1) && isDefined(i, t2)) {
				float salaryT1 = recover(i, t1);
				float salaryT2 = recover(i, t2);
				insert(i, salaryT1 + salaryT2, result);
				deleteElement(i, t1);
				deleteElement(i, t2);
			}
			else if (isDefined(i, t1)) {
				float salaryT1 = recover(i, t1);
				insert(i, salaryT1, result);
				deleteElement(i, t1);
			}
			else if (isDefined(i, t2)) {
				float salaryT2 = recover(i, t2);
				insert(i, salaryT2, result);
				deleteElement(i, t2);
			}
		}
		return result;
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

	//display(table);

	IntFloatTable* t = create(12);

	insert(1, 2.4, t);
	insert(1, 3.4, t);
	insert(4, 6.5, t);
	insert(6, 8.2, t);
	insert(3, 5.5, t);
	insert(10, 12.8, t);
	insert(9, 7.2, t);

	IntFloatTable* t1 = create(120);

	insert(1, 22000.40, t1);
	insert(1, 35000.40, t1);
	insert(4, 65000.50, t1);
	insert(6, 85000.20, t1);
	insert(3, 53000.50, t1);
	insert(10, 12000.80, t1);
	insert(9, 7500.20, t1);

	IntFloatTable* t2 = create(150);

	insert(1, 22000.40, t2);
	insert(11, 30000.40, t2);
	insert(41, 65000.50, t2);
	insert(60, 80000.20, t2);
	insert(30, 55000.50, t2);
	insert(100, 12880.80, t2);
	insert(90, 75000.20, t2);

	//cout << recover(4, t);
	//cout << isDefined(6, t);

	deleteElement(10, t);

	//destroyTable(t);

	IntFloatTable* mergedTables = consolidateTables(t1, t2, 1, 105);

	displayTable(mergedTables);

	//displayTable(t);

	return 0;
}