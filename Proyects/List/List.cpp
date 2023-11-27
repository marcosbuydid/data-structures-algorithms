#include <iostream>

using namespace std;

/*
* PositionList using a dinamic array, a variable maxSize,
* and a variable top.
* Element and numberOfElements operations are made in
* constant order in the worst case.
* Implementation is unbounded.
*/

struct PositionList {
	int* arrayList;
	unsigned int maxSize;
	int index;
};

PositionList* createPositionList() {
	PositionList* pl = new PositionList();
	pl->maxSize = 10;
	pl->arrayList = new int[pl->maxSize];
	pl->index = -1;
	return pl;
}

bool isEmpty(PositionList* pl) {
	return pl->index == -1;
}

void destroy(PositionList* &pl) {
	delete[] pl->arrayList;
	pl->index = -1;
	pl->maxSize = 0;
}

int numberOfElements(PositionList* pl) {
	return pl->index + 1;
}

void add(PositionList*& pl, int e, int pos) {
	if (isEmpty(pl)) {
		pl = createPositionList();
	}
	if (pl->index + 1 >= pos) {
		//if array is full we extend his size.
		if (pl->index + 1 == pl->maxSize) {
			int extendedSize = pl->maxSize + 10;
			int* extendedList = new int[extendedSize];
			pl->maxSize = extendedSize;
			for (int i = 0; i < pl->index + 1; i++) {
				extendedList[i] = pl->arrayList[i];
			}
			int* aux = pl->arrayList;
			pl->arrayList = extendedList;
			pl->maxSize = extendedSize;
			delete aux;
		}
		//we shift the position of the elements in the arraylist
		//so we can save the new element in the position selected.
		for (int i = pl->index + 1; i > pos; i--) {
			pl->arrayList[i] = pl->arrayList[i - 1];
		}
		pl->arrayList[pos] = e;
		pl->index++;
	}
	else {
		//if the position we want to add the element is the same
		//position of the maximum size of the arraylist, we extend it
		//and add the element in the next available position of the
		//resized arraylist.
		if (pl->index + 1 == pl->maxSize) {
			int extendedSize = pl->maxSize + 10;
			int* extendedList = new int[extendedSize];
			for (int i = 0; i <= pl->index; i++) {
				extendedList[i] = pl->arrayList[i];
			}
			int* aux = pl->arrayList;
			pl->arrayList = extendedList;
			pl->maxSize = extendedSize;
			delete aux;
		}

		pl->arrayList[pl->index + 1] = e;
		pl->index++;
	}
}

int element(PositionList* pl, int pos) {
	if (pos >= 0 && pos < pl->index + 1) {
		return pl->arrayList[pos];
	}
}

PositionList* clone(PositionList* pl) {
	PositionList* clone = createPositionList();
	if (isEmpty(pl)) {
		return clone;
	}
	else {
		int cloneIndex = pl->index;
		int cloneMaxSize = pl->maxSize;
		for (int i = 0; i <= cloneIndex;i++) {
			clone->arrayList[i] = pl->arrayList[i];
		}
		clone->index = cloneIndex;
		clone->maxSize = cloneMaxSize;
		return clone;
	}
}

void erase(PositionList*& pl, int pos) {
	if (pos < 0 || pos >= pl->index + 1) {
		return;
	}
	int* temp = new int[pl->maxSize];
	if (pos == 0) {
		for (int i = 1; i < pl->index + 1; i++) {
			temp[i-1] = pl->arrayList[i];
		}
	}
	else {
		int auxIndex = 0;
		for (int i = 0; i < pos; i++) {
			temp[i] = pl->arrayList[i];
			auxIndex = i;
		}
		for (int i = pos+1; i <= pl->index; i++) {
			temp[auxIndex + 1] = pl->arrayList[i];
			auxIndex++;
		}
	}
	int* aux = pl->arrayList;
	pl->arrayList = temp;
	delete aux;

	pl->index--;
}



void display(PositionList* pl) {
	if (!isEmpty(pl)) {
		for (int i = 0; i < pl->index + 1;i++) {
			cout << pl->arrayList[i] << " ";
		}
		cout << endl;
	}
}

/*
* SortedIntList using a binary search tree and 
* a variable elementQuantity.
* Add, erase, exists operations are made in O(log2n) 
* in average and numberOfElements in O(1).
* Implementation is unbounded.
*/

struct NodeAB {
	int data;
	NodeAB* left;
	NodeAB* right;
};

struct SortedIntList {
	NodeAB* list;
	unsigned int elementQuantity;
};

/*
* Auxiliary methods of SortedIntList
*/

void insertNodeInABB(NodeAB* &root, int data) {

	NodeAB* t = root;
	NodeAB* p;
	NodeAB* r = NULL;

	// root is empty
	if (root == NULL) {
		p = new NodeAB();
		p->data = data;
		p->left = NULL;
		p->right = NULL;
		root = p;
		return;
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
	p = new NodeAB();
	p->data = data;
	p->left = NULL;
	p->right = NULL;

	if (data < r->data) {
		r->left = p;
	}
	else {
		r->right = p;
	}
}

void inOrder(NodeAB* root) {
	if (root != NULL) {
		inOrder(root->left);
		cout << root->data << ", " << flush;
		inOrder(root->right);
	}
}

int maxNode(NodeAB* root) {
	if (root == NULL) {
		return INT_MIN;
	}
	else {
		int maximum = maxNode(root->right);
		if (maximum > root->data) {
			return maximum;
		}
		else {
			return root->data;
		}
	}
}

int minNode(NodeAB* root) {
	if (root == NULL) {
		return INT_MAX;
	}
	else {
		int minimum = minNode(root->left);
		if (minimum < root->data) {
			return minimum;
		}
		else {
			return root->data;
		}
	}
}

void deleteNodeAB(NodeAB* &tree, int e) {
	if (tree != NULL) {
		if (e < tree->data) {
			deleteNodeAB(tree->left, e);
		}
		else if (e > tree->data) {
			deleteNodeAB(tree->right, e);
		}
		else {
			if (tree->left == NULL) {
				NodeAB* nodeToDelete = tree;
				tree = tree->right;
				delete nodeToDelete;
			}
			else if (tree->right == NULL) {
				NodeAB* nodeToDelete = tree;
				tree = tree->left;
				delete nodeToDelete;
			}
			else {
				int maximum = maxNode(tree->left);
				tree->data = maximum;
				deleteNodeAB(tree->left, maximum);
			}
		}
	}
}

bool nodeInAB(NodeAB* root, int x) {
	if (root == NULL) {
		return false;
	}
	if (root->data == x) {
		return true;
	}
	else if (x < root->data) {
		return nodeInAB(root->left, x);
	}
	else if (x > root->data) {
		return nodeInAB(root->right, x);
	}
}

NodeAB* cloneAB(NodeAB* tree) {
	if (tree == NULL) {
		return NULL;
	}
	NodeAB* clonedTree = new NodeAB();
	clonedTree->data = tree->data;
	clonedTree->left = cloneAB(tree->left);
	clonedTree->right = cloneAB(tree->right);
	return clonedTree;
}

void eraseAB(NodeAB* tree) {
	if (tree != NULL) {
		eraseAB(tree->left);
		eraseAB(tree->right);
		delete tree;
		tree = NULL;
	}
}

/*
* End of auxiliary methods of SortedIntList
*/

SortedIntList* createSortedIntList() {
	SortedIntList* sl = new SortedIntList();
	sl->list = NULL;
	sl->elementQuantity = 0;
	return sl;
}

bool isEmpty(SortedIntList* l) {
	return l->elementQuantity == 0;
}

void add(SortedIntList* &l, int e) {
	if (isEmpty(l)) {
		l = createSortedIntList();
	}
	insertNodeInABB(l->list, e);
	l->elementQuantity++;
}

void erase(SortedIntList* &l, int e) {
	if (nodeInAB(l->list, e)) {
		deleteNodeAB(l->list, e);
		l->elementQuantity--;
	}
}

void eraseMax(SortedIntList*& l) {
	int maximum = maxNode(l->list);
	if (maximum != INT_MIN) {
		deleteNodeAB(l->list, maximum);
		l->elementQuantity--;
	}
}

void eraseMin(SortedIntList*& l) {
	int minimum = minNode(l->list);
	if (minimum != INT_MAX) {
		deleteNodeAB(l->list, minimum);
		l->elementQuantity--;
	}
}

int minimum(SortedIntList* l) {
	if (!isEmpty(l)) {
		return minNode(l->list);
	}
}

int maximum(SortedIntList* l) {
	if (!isEmpty(l)) {
		return maxNode(l->list);
	}
}

bool exists(SortedIntList* l, int e) {
	return nodeInAB(l->list, e);
}

unsigned int numberOfElements(SortedIntList* l) {
	return l->elementQuantity;
}

SortedIntList* clone(SortedIntList* l) {
	SortedIntList* clonedList = createSortedIntList();
	if (isEmpty(l)) {
		return clonedList;
	}
	else {
		clonedList->list = cloneAB(l->list);
		clonedList->elementQuantity = l->elementQuantity;
		return clonedList;
	}
}

void destroy(SortedIntList* l) {
	eraseAB(l->list);
	l->elementQuantity = 0;
}

void display(SortedIntList* l) {
	inOrder(l->list);
}


/*
* IntList using two pointers and
* a variable elementQuantity.
* Create, insert, isEmpty, first and last 
* operations are made in O(1) in the worst case.
* Implementation is unbounded.
*/

struct NodeList {
	int data;
	NodeList* next;
};

struct IntList {
	NodeList* first;
	NodeList* last;
	unsigned int elementQuantity;
};

IntList* createIntList() {
	IntList* l = new IntList();
	l->first = NULL;
	l->last = NULL;
	l->elementQuantity = 0;
	return l;
}

bool isEmpty(IntList* l) {
	return l->elementQuantity == 0;
}

void insert(int x, IntList* &l) {
	if (isEmpty(l)) {
		l = createIntList();
	}
	NodeList* node = new NodeList();
	node->data = x;
	node->next = NULL;
	if (l->first == NULL) {
		l->first = node;
		l->last = node;
	}
	else {
		l->last->next = node;
		l->last = node;
	}
	l->elementQuantity++;
}

int first(IntList* &l) {
	if (!isEmpty(l)) {
		int data = l->first->data;
		NodeList* nodeToDelete = l->first;
		l->first = l->first->next;
		delete nodeToDelete;
		l->elementQuantity--;
		return data;
	}
}

int last(IntList* &l) {
	if (!isEmpty(l)) {
		int data = l->last->data;
		NodeList* nodeToDelete = l->last;
		l->last = l->last->next;
		delete nodeToDelete;
		l->elementQuantity--;
		return data;
	}
}

IntList* cloneList(IntList* l) {
	IntList* clonedList = createIntList();
	NodeList* iterator = l->first;
	while (iterator != NULL) {
		insert(iterator->data, clonedList);
		iterator = iterator->next;
	}
	clonedList->elementQuantity = l->elementQuantity;
	return clonedList;
}

void destroyList(NodeList*& list) {
	if (list != NULL) {
		while (list != NULL) {
			NodeList* nodeToDelete = list;
			list = list->next;
			delete nodeToDelete;
		}
	}
	delete list;
	list = NULL;
}

void destroy(IntList* &l) {
	destroyList(l->first);
	l->elementQuantity = 0;
	delete l;
}

void display(IntList* l) {
	NodeList* iterator = l->first;
	while (iterator != NULL) {
		cout << iterator->data << " ";
		cout << endl;
		iterator = iterator->next;
	}
}

int main() {
	//PositionList* pList = createPositionList();

	/*int i = 0;
	int elements = 10;
	while (i < elements) {
		add(pList, i * 2, i);
		i++;
	}*/

	//add(pList, 89, 0);

	//add(pList, 99, 11);

	//add(pList, 109, 6);

	//cout << element(pList, 12);

	//destroy(pList);

	//PositionList* p = clone(pList);

	//erase(pList, 0);
	//erase(pList, 4);
	//erase(pList, 12);

	//display(pList);

	SortedIntList* sl = new SortedIntList();

	add(sl, -1234);
	add(sl, 8);
	add(sl, 4);
	add(sl, 5);
	add(sl, 10);
	add(sl, 12);
	add(sl, 13);
	add(sl, 455677);

	//erase(sl, 13);
	//eraseMax(sl);
	//eraseMin(sl);

	//cout << minimum(sl);
	//cout << maximum(sl);

	//exists(sl, 13);

	//cout << numberOfElements(sl);

	//SortedIntList* clonedList = clone(sl);

	//destroy(sl);

	//display(sl);

	IntList* l = createIntList();
	insert(4, l);
	insert(3, l);
	insert(10, l);
	insert(6, l);
	insert(8, l);

	//cout << first(l);
	//cout << last(l);

	//IntList* clonedList = cloneList(l);
	
	destroy(l);

	display(l);

	return 0;
}

