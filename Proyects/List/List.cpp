#include <iostream>

using namespace std;

/*
* PositionList using dinamic array, a variable maxSize,
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
* SortedIntList using a binary search tree pointer 
* and a variable elementQuantity.
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
	int elementQuantity;
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
		return 0;
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

void display(SortedIntList* l) {
	inOrder(l->list);
}

int main()
{
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

	add(sl, 8);
	add(sl, 4);
	add(sl, 5);
	add(sl, 10);
	add(sl, 12);
	add(sl, 13);

	display(sl);

	return 0;
}

