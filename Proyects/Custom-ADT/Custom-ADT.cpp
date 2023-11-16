#include <iostream>

using namespace std;

/*ADT WorkShopWaitingList using four pointers.
* biggerPriority and dequeue operations are made 
* with O(1) in the worst case.
* Implementation is unbounded.
*/

enum Priority {withInsurance, withoutInsurance};

struct WorkShopNode {
    int data;
    WorkShopNode* next;
};

struct WorkShopWaitingList {
    WorkShopNode* headNoInsuranceCarList;
    WorkShopNode* lastNoInsuranceCarList;
    WorkShopNode* headInsuranceCarList;
    WorkShopNode* lastInsuranceCarList;
};

/* Aux methods*/

WorkShopNode* cloneList(WorkShopNode* list) {
    if (list == NULL) {
        return NULL;
    }
    else {
        WorkShopNode* clone = new WorkShopNode();
        clone->data = list->data;
        clone->next = cloneList(list->next);
        return clone;
    }
}

void destroyList(WorkShopNode*& list) {
    while (list != NULL) {
        WorkShopNode* nodeToDelete = list;
        list = list->next;
        delete nodeToDelete;
    }
    delete list;
    list = NULL;
}

/* End of aux methods*/

WorkShopWaitingList* createWorkShopWaitingList() {
    WorkShopWaitingList* wwl = new WorkShopWaitingList();
    wwl->headNoInsuranceCarList = NULL;
    wwl->lastNoInsuranceCarList = NULL;
    wwl->headInsuranceCarList = NULL;
    wwl->lastInsuranceCarList = NULL;

    return wwl;
}

bool belongs(WorkShopWaitingList* wwl, int carNumber) {
    bool result = false;
    WorkShopNode* iterator = wwl->headNoInsuranceCarList;
    while (iterator != NULL) {
        if (iterator->data == carNumber) {
            result = true;
        }
        iterator = iterator->next;
    }

    if (result) {
        return true;
    }
    else {
        WorkShopNode* iterator = wwl->headInsuranceCarList;
        while (iterator != NULL) {
            if (iterator->data == carNumber) {
                return true;
            }
            iterator = iterator->next;
        }
        return false;
    }
}

void enqueueAux(WorkShopNode* &head, WorkShopNode* &last, WorkShopNode* node) {
    if (head == NULL) {
        head = node;
        last = node;
    }
    else {
        last->next = node;
        last = node;
    }
}

bool isEmpty(WorkShopWaitingList* wwl) {
    return wwl->headNoInsuranceCarList == NULL &&
        wwl->headInsuranceCarList == NULL;
}

void enqueueWithPriority(WorkShopWaitingList*& wwl, int carNumber, Priority p) {
    if (isEmpty(wwl)) {
        wwl = createWorkShopWaitingList();
    }
    WorkShopNode* node = new WorkShopNode();
    node->data = carNumber;
    node->next = NULL;

    if (p == withInsurance) {
        enqueueAux(wwl->headInsuranceCarList, wwl->lastInsuranceCarList, node);
    }
    else {
        enqueueAux(wwl->headNoInsuranceCarList, wwl->lastNoInsuranceCarList, node);
    }
}

int biggerPriority(WorkShopWaitingList* wwl) {
    if (!isEmpty(wwl)) {
        return wwl->headInsuranceCarList->data;
    }
}

void dequeue(WorkShopWaitingList*& wwl) {
    if (!isEmpty(wwl)) {
        WorkShopNode* nodeToDelete = wwl->headInsuranceCarList;
        wwl->headInsuranceCarList = wwl->headInsuranceCarList->next;
        delete nodeToDelete;
    }
}

WorkShopWaitingList* clone(WorkShopWaitingList* wwl) {
    WorkShopWaitingList* wwlClone = createWorkShopWaitingList();
    wwlClone->headInsuranceCarList = cloneList(wwl->headInsuranceCarList);
    wwlClone->headNoInsuranceCarList = cloneList(wwl->headNoInsuranceCarList);
    wwlClone->lastInsuranceCarList = cloneList(wwl->lastInsuranceCarList);
    wwlClone->lastNoInsuranceCarList = cloneList(wwl->lastNoInsuranceCarList);

    return wwlClone;
}

void destroy(WorkShopWaitingList*& wwl) {
    destroyList(wwl->headNoInsuranceCarList);
    destroyList(wwl->headInsuranceCarList);
    destroyList(wwl->lastNoInsuranceCarList);
    destroyList(wwl->lastInsuranceCarList);
}

void display(WorkShopWaitingList*& wwl) {
    if (!isEmpty(wwl)) {
        WorkShopNode* iterator = wwl->headNoInsuranceCarList;
        while (iterator != NULL) {
            cout << "Without Insurance: " << iterator->data << " ";
            cout << endl;
            iterator = iterator->next;
        }
        iterator = wwl->headInsuranceCarList;
        while (iterator != NULL) {
            cout << "With Insurance: " << iterator->data << " ";
            cout << endl;
            iterator = iterator->next;
        }
    }
}



int main() {
    
    WorkShopWaitingList* wwl = createWorkShopWaitingList();
    
    enqueueWithPriority(wwl, 132456, withInsurance);
    enqueueWithPriority(wwl, 167890, withInsurance);
    enqueueWithPriority(wwl, 124562, withInsurance);
    enqueueWithPriority(wwl, 198723, withoutInsurance);
    enqueueWithPriority(wwl, 211098, withoutInsurance);

    WorkShopWaitingList* wwlClone = clone(wwl);

    dequeue(wwlClone);

    //cout << biggerPriority(wwlClone);

    //destroy(wwlClone);

    display(wwlClone);


    return 0;
}

