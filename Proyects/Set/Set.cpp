#include <iostream>

using namespace std;

/*
* IntSet using a double pointer called container and two variables,
* capacity and elementQuantity.
* Open hashing is used with module operation suited as hash function.
* Implementation is unbounded.
*/

struct SetNode {
    int data;
    SetNode* next;
};

struct IntSet {
    SetNode** container;
    unsigned int size;
    unsigned int elementQuantity;
};

/* Auxiliary methods*/

int hashModule(int element, unsigned int capacity) {
    int positionElement = element % capacity;
    if (positionElement < 0) {
        positionElement = positionElement * -1;
    }
    return positionElement;
}

void addOrdered(SetNode*& list, int e) {
	if (list == NULL || e < list->data) {
		SetNode* node = new SetNode();
		node->data = e;
		node->next = list;
		list = node;
	}
    else {
        addOrdered(list->next, e);
    }
}

int minimumValue(SetNode* l) {
    if (l != NULL) {
        int min = INT_MAX;
        while (l != NULL) {
            if (l->data < min) {
                min = l->data;
            }
            l = l->next;
        }
        return min;
    }
    else {
        return INT_MIN;
    }
}

void displayData(SetNode* l) {
    if (l == NULL) {
        return;
    }
    else {
        while (l != NULL) {
            cout << l->data << " ";
            l = l->next;
        }
    }
}

/* End of auxiliary methods*/

IntSet* createIntSet(unsigned int capacity) {
    IntSet* cs = new IntSet();
    cs->size = capacity;
    cs->elementQuantity = 0;
    cs->container = new SetNode* [capacity];
    for (int i = 0; i < capacity;i++) {
        cs->container[i] = NULL;
    }
    return cs;
}

bool isEmpty(IntSet* s) {
    return s->elementQuantity == 0;
}

bool belongs(IntSet* s, int e) {
    if (isEmpty(s)) {
        return false;
    }
    else {
        int elementPosition = hashModule(e, s->size);
        SetNode* aux = s->container[elementPosition];
        while (aux != NULL) {
            if (aux->data == e) {
                return true;
            }
            aux = aux->next;
        }
        return false;
    }
}

void add(IntSet* &s, int e) {
    if (!belongs(s, e)) {
        int elementPosition = hashModule(e, s->size);
        addOrdered(s->container[elementPosition], e);
        s->elementQuantity++;
    }
}

int minimum(IntSet* s) {
    if (!isEmpty(s)) {
        int min = INT_MAX;
        for (int i = 0; i < s->size; i++) {
            if (s->container[i] != NULL) {
                if (minimumValue(s->container[i]) < min) {
                    min = minimumValue(s->container[i]);
                }
            }
        }
        return min;
    }
}

void display(IntSet* s) {
	if (!isEmpty(s)) {
		for (int i = 0; i < s->size;i++) {
			if (s->container[i] != NULL) {
				displayData(s->container[i]);
				cout << endl;
			}
		}
	}
}

int main() {

    IntSet* s = createIntSet(20);

    add(s, -5);
    add(s, 1);
    add(s, 3);
    add(s, 9);
    add(s, 12);

    //cout << minimum(s);

    display(s);


    return 0;
}
