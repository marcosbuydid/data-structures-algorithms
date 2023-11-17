#include <iostream>

using namespace std;

/*ADT WorkShopWaitingList using four pointers.
* biggerPriority and dequeue operations are made
* with O(1) in the worst case.
* Implementation is unbounded.
*/

enum Priority { withInsurance, withoutInsurance };

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

void enqueueAux(WorkShopNode*& head, WorkShopNode*& last, WorkShopNode* node) {
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
	return wwl->headInsuranceCarList == NULL;
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

void display(WorkShopWaitingList* wwl) {
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

unsigned int carWaitingList(WorkShopWaitingList* wwl) {
	if (!isEmpty(wwl)) {
		int quantity = 0;
		while (!isEmpty(wwl)) {
			dequeue(wwl);
			quantity++;
		}
		return quantity;
	}
}


/*ADT CommentManagement using two pointers and
* two variables commentsQuantity and maxCommentsThreshold.
* addComment, numberOfComments and recentArticle operations
* are made with O(1) in the worst case.
* Implementation is unbounded.
*/

struct CommentNode {
	unsigned int articleNumber;
	char* text;
	CommentNode* next;
};

struct CommentManagement {
	CommentNode* recent;
	CommentNode* last;
	unsigned int commentsQuantity;
	unsigned int maxCommentsThreshold;
};

/* Aux methods */
void destroyList(CommentNode*& list) {
	while (list != NULL) {
		CommentNode* nodeToDelete = list;
		list = list->next;
		delete nodeToDelete;
	}
	delete list;
	list = NULL;
}

int stringLength(char* str) {
	int length = 0;
	while (str[length] != '\0') {
		length++;
	}
	return length;
}

char* copyString(char* str) {
	int length = stringLength(str);
	char* strCopy = new char[length + 1];

	for (int i = 0;i < length;i++) {
		strCopy[i] = str[i];
	}
	strCopy[length] = '\0';

	return strCopy;
}

CommentNode* cloneList(CommentNode* list) {
	if (list == NULL) {
		return NULL;
	}
	else {
		CommentNode* clonedList = new CommentNode();
		clonedList->articleNumber = list->articleNumber;
		clonedList->text = copyString(list->text);
		clonedList->next = cloneList(list->next);
		return clonedList;
	}
}
/* End of aux methods */

CommentManagement* createCommentManagement(unsigned int k) {
	if (k > 0) {
		CommentManagement* cm = new CommentManagement();
		cm->recent = NULL;
		cm->last = NULL;
		cm->commentsQuantity = 0;
		cm->maxCommentsThreshold = k;

		return cm;
	}
}

bool isEmpty(CommentManagement* cm) {
	return cm->commentsQuantity == 0;
}

void addComment(CommentManagement*& cm, char* text, unsigned int articleNumber) {
	CommentNode* c = new CommentNode();
	c->text = text;
	c->articleNumber = articleNumber;
	c->next = NULL;

	if (isEmpty(cm)) {
		cm->recent = c;
		cm->last = c;
		cm->commentsQuantity++;
	}
	else if (cm->commentsQuantity <= cm->maxCommentsThreshold) {
		cm->recent->next = c;
		cm->recent = c;

		if (cm->commentsQuantity == cm->maxCommentsThreshold) {
			CommentNode* commentToDelete = cm->last;
			cm->last = cm->last->next;
			delete commentToDelete;
		}
		else {
			cm->commentsQuantity++;
		}
	}
}

void deleteComment(CommentManagement*& cm, unsigned int articleNumber) {
	if (!isEmpty(cm)) {
		CommentNode* iterator = cm->last;
		while (iterator != NULL) {
			if (iterator->articleNumber == articleNumber) {
				CommentNode* commentToDelete = iterator;
				iterator = iterator->next;
				delete commentToDelete;
				cm->commentsQuantity--;
			}
		}
	}
}

unsigned int recentArticle(CommentManagement* cm) {
	if (!isEmpty(cm)) {
		return cm->recent->articleNumber;
	}
}

char* recentText(CommentManagement* cm) {
	if (!isEmpty(cm)) {
		return cm->recent->text;
	}
}

unsigned int numberOfComments(CommentManagement* cm) {
	return cm->commentsQuantity;
}

CommentManagement* clone(CommentManagement* cm) {
	CommentManagement* cloned = createCommentManagement(cm->maxCommentsThreshold);
	cloned->commentsQuantity = cm->commentsQuantity;
	cloned->maxCommentsThreshold = cm->maxCommentsThreshold;
	cloned->last = cloneList(cm->last);
	cloned->recent = cloneList(cm->recent);
	return cloned;
}

void destroy(CommentManagement*& cm) {
	destroyList(cm->last);
	cm->commentsQuantity = 0;
	cm->maxCommentsThreshold = 0;
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

	//cout << carWaitingList(wwlClone);

	//display(wwlClone);


	CommentManagement* cm = createCommentManagement(3);
	char c1[14] = "Great Article";
	char c2[12] = "Bad Article";
	char c3[19] = "Incredible Article";
	char c4[14] = "Bored Article";

	addComment(cm, c1, 345678);
	addComment(cm, c2, 345678);
	addComment(cm, c3, 345678);
	addComment(cm, c4, 345678);

	//deleteComment(cm, 345678);

	CommentManagement* cmClone = clone(cm);

	destroy(cm);

	return 0;
}

