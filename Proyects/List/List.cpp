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

void destroy(PositionList* pl) {
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
			pl->arrayList = extendedList;
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



void display(PositionList* pl) {
	if (!isEmpty(pl)) {
		for (int i = 0; i < pl->index + 1;i++) {
			cout << pl->arrayList[i] << " ";
		}
		cout << endl;
	}
}

int main()
{
	PositionList* pList = createPositionList();

	int i = 0;
	int elements = 10;
	while (i < elements) {
		add(pList, i * 2, i);
		i++;
	}

	add(pList, 89, 0);

	add(pList, 99, 11);

	add(pList, 109, 6);

	//cout << element(pList, 12);

	//destroy(pList);

	PositionList* p = clone(pList);

	//display(pList);
	display(p);

	return 0;
}

