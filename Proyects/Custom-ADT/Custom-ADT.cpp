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

/*ADT BookShop using a binary search tree.
* addBook, searchAuthor and returnBook operations are made
* with O(log(n)) in average.
* Implementation is unbounded.
*/

struct BookNode {
	char* title;
	char* author;
	unsigned int copies;
	unsigned int onLoan;
	BookNode* left;
	BookNode* right;
};

struct BookShop {
	BookNode* books;
	unsigned int numberOfBooks;
};

/* Auxiliary methods */
void addBookToBookShop(BookNode*& bookshop, char* title, char* author, unsigned int copies) {

	BookNode* t = bookshop;
	BookNode* p;
	BookNode* r = NULL;

	// bookshop is empty
	if (bookshop == NULL) {
		p = new BookNode();
		p->title = title;
		p->author = author;
		p->copies = copies;
		p->onLoan = 0;
		p->left = NULL;
		p->right = NULL;
		bookshop = p;
		return;
	}

	while (t != NULL) {
		r = t;
		if (title > t->title) {
			t = t->left;
		}
		else if (title < t->title) {
			t = t->right;
		}
		else {
			return;
		}
	}

	//Now t points at NULL and 
	//r points at insert location

	p = new BookNode();
	p->title = title;
	p->author = author;
	p->copies = copies;
	p->onLoan = 0;
	p->left = NULL;
	p->right = NULL;

	if (title > r->title) {
		r->left = p;
	}
	else {
		r->right = p;
	}
}

BookNode* bookOnBookShop(BookNode* b, char* title) {
	if (b == NULL) {
		return NULL;
	}
	else if (b->title == title) {
		return b;
	}
	else if (title < b->title) {
		return bookOnBookShop(b->right, title);
	}
	else {
		return bookOnBookShop(b->left, title);
	}
}

char* bookAuthor(BookNode* b, char* title) {
	if (b == NULL) {
		return NULL;
	}
	else if (b->title == title) {
		return b->author;
	}
	else if (title < b->title) {
		return bookAuthor(b->right, title);
	}
	else {
		return bookAuthor(b->left, title);
	}
}
/* End of auxiliary methods */

BookShop* createBookShop() {
	BookShop* bs = new BookShop();
	bs->books = NULL;
	bs->numberOfBooks = 0;
	return bs;
}

bool isEmpty(BookShop* bs) {
	return bs->numberOfBooks == 0;
}

bool exists(BookShop* bs, char* title) {
	if (isEmpty(bs)) {
		return false;
	}
	else {
		BookNode* b = bookOnBookShop(bs->books, title);
		if (b != NULL) {
			return true;
		}
		else {
			return false;
		}
	}
}

void addBook(BookShop*& bs, char* title, char* author, unsigned int copies) {
	if (isEmpty(bs)) {
		bs = createBookShop();
	}
	if (!exists(bs, title)) {
		addBookToBookShop(bs->books, title, author, copies);
		bs->numberOfBooks++;
	}
}

char* findAuthor(BookShop* bs, char* title) {
	if (exists(bs, title)) {
		return bookAuthor(bs->books, title);
	}
}

void borrowBook(BookShop* bs, char* title) {
	if (exists(bs, title)) {
		BookNode* book = bookOnBookShop(bs->books, title);
		if (book->copies > book->onLoan) {
			book->copies--;
			book->onLoan++;
		}
	}
}

void returnBook(BookShop* bs, char* title) {
	if (exists(bs, title)) {
		BookNode* book = bookOnBookShop(bs->books, title);
		if (book->copies < book->onLoan) {
			book->copies++;
			book->onLoan--;
		}
	}
}

int numberOfBooks(BookShop*& bs) {
	return bs->numberOfBooks;
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


	BookShop* bs = createBookShop();

	char title1[11] = "Clean Code";
	char title2[26] = "Practical C++ Programming";
	char title3[12] = "Refactoring";
	char title4[16] = "C++ Primer Plus";

	char author1[16] = "Robert C Martin";
	char author2[15] = "Steve Oualline";
	char author3[16] = "Martin Fowler";
	char author4[14] = "Stephen Prata";

	addBook(bs, title1, author1, 4);
	addBook(bs, title2, author2, 2);
	addBook(bs, title3, author3, 1);
	addBook(bs, title4, author4, 3);

	//cout << findAuthor(bs, title4);

	//cout << bs->numberOfBooks;

	borrowBook(bs, title3);
	
	returnBook(bs, title3);

	
	return 0;
}

