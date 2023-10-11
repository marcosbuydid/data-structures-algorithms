#include <iostream>
#include <stdio.h>
using namespace std;

struct NodeList {
	int data;
	NodeList* next = NULL;
};

struct NodeAB {
	int data;
	NodeAB* left;
	NodeAB* right;
};

struct NodeAG {
	int data;
	NodeAG* firstChild;
	NodeAG* nextSibling;
};

NodeAB* createNode(int data) {
	NodeAB* node = (NodeAB*)malloc(sizeof(NodeAB));
	node->data = data;
	node->left = node->right = NULL;
	return node;
}


NodeAB* createBinaryTree(int nodeData[], int i, int n) {
	NodeAB* root = NULL;

	if (i < n) {
		root = createNode(nodeData[i]);
		root->left = createBinaryTree(nodeData, 2 * i + 1, n);
		root->right = createBinaryTree(nodeData, 2 * i + 2, n);
	}
	return root;
}

void insertNodeInABB(NodeAB*& root, int data) {

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

NodeAB* createBinarySearchTree(int nodeData[], int i, int n) {
	NodeAB* root = NULL;

	for (int i = 0; i < n;i++) {
		int data = nodeData[i];
		insertNodeInABB(root, data);
	}
	return root;
}

void preOrder(NodeAB* root) {
	if (root != NULL) {
		cout << root->data << ", " << flush;
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrder(NodeAB* root) {
	if (root != NULL) {
		inOrder(root->left);
		cout << root->data << ", " << flush;
		inOrder(root->right);
	}
}

void postOrder(NodeAB* root) {
	if (root != NULL) {
		postOrder(root->left);
		postOrder(root->right);
		cout << root->data << ", " << flush;
	}
}

int minLevelK(NodeAB* root, int k) {
	if (root == NULL || k < 1) {
		return NULL;
	}

	if (k == 1) {
		return root->data;
	}
	else {
		int minIzq = minLevelK(root->left, k - 1);
		int minDer = minLevelK(root->right, k - 1);

		if (minIzq < minDer) {
			return minIzq;
		}
		else {
			return minDer;
		}
	}
}

int maxNode(NodeAB* root) {
	if (root == NULL) {
		return 0;
	}
	else {
		int maximum = max(maxNode(root->left), maxNode(root->right));
		if (maximum > root->data) {
			return maximum;
		}
		else {
			return root->data;
		}
	}
}

void printRange(NodeAB* t, int min, int max) {
	if (t == NULL) {
		return;
	}

	if (min > t->data || max > t->data) {
		printRange(t->right, min, max);
	}

	if (t->data >= min && t->data <= max) {
		cout << t->data << ", " << flush;
	}

	if (min < t->data || max < t->data) {
		printRange(t->left, min, max);
	}
}

NodeAB* rangeCopy(NodeAB* a, int inf, int sup) {
	if (a == NULL) {
		return NULL;
	}
	NodeAB* result = NULL;

	if (a->data > inf && a->data < sup) {
		result = new NodeAB();
		result->data = a->data;
		result->left = rangeCopy(a->left, inf, sup);
		result->right = rangeCopy(a->right, inf, sup);
		return result;
	}
	if (inf < a->data || sup < a->data) {
		rangeCopy(a->left, inf, sup);
	}
	else if (inf > a->data || sup > a->data) {
		rangeCopy(a->right, inf, sup);
	}
}

void eraseTree(NodeAB*& root) {
	if (root == NULL) {
		return;
	}
	eraseTree(root->left);
	eraseTree(root->right);
	delete root;
	root = NULL;
}

NodeAB* nodeInAB(NodeAB* root, int x) {
	if (root == NULL) {
		return NULL;
	}
	if (root->data == x) {
		return root;
	}
	else if (x < root->data) {
		nodeInAB(root->left, x);
	}
	else if (x > root->data) {
		nodeInAB(root->right, x);
	}
}

NodeAB* cloneABTree(NodeAB* root) {
	if (root == NULL) {
		return NULL;
	}
	else {
		NodeAB* clone = new NodeAB();
		clone->data = root->data;
		clone->left = cloneABTree(root->left);
		clone->right = cloneABTree(root->right);
		return clone;
	}
}

NodeAB* subTreeCopy(NodeAB* root, int x) {
	if (root == NULL) {
		return NULL;
	}
	if (nodeInAB(root, x) != NULL) {
		NodeAB* nodeFound = nodeInAB(root, x);
		NodeAB* result = new NodeAB();
		result->data = nodeFound->data;
		result->left = cloneABTree(nodeFound->left);
		result->right = cloneABTree(nodeFound->right);
		return result;
	}
}


NodeAG* searchNodeAG(NodeAG* root, int x) {
	if (root == NULL) {
		return NULL;
	}

	if (root->data == x) {
		return root;
	}

	NodeAG* firstChildNode = searchNodeAG(root->firstChild, x);
	if (firstChildNode != NULL) {
		return firstChildNode;
	}
	else {
		return searchNodeAG(root->nextSibling, x);
	}
}

//Precondition: The AG not have repeeated nodes
//Poscondition: Insert a child as first child of a father node 
// if father exist in the tree and the child is not.

void insertNodeInAG(NodeAG*& a, int father, int child) {
	NodeAG* fatherNode = searchNodeAG(a, father);

	if (fatherNode != NULL && searchNodeAG(a, child) == NULL) {
		NodeAG* childNode = new NodeAG();
		childNode->data = child;
		childNode->firstChild = NULL;
		childNode->nextSibling = fatherNode->nextSibling;
		fatherNode->firstChild = childNode;
	}
}

void childAG(NodeAG* tree, int x, NodeList*& list) {
	if (tree == NULL) {
		return;
	}

	NodeAG* nodeAG = searchNodeAG(tree, x);

	if (nodeAG != NULL) {
		if (nodeAG->firstChild != NULL) {
			NodeList* node = new NodeList();
			node->data = nodeAG->firstChild->data;
			node->next = list;
			list = node;
		}
		if (nodeAG->nextSibling != NULL) {
			NodeAG* aux = nodeAG->nextSibling;
			while (aux->nextSibling != NULL) {
				NodeList* node = new NodeList();
				node->data = aux->data;
				node->next = list;
				list = node;
				aux = aux->nextSibling;
			}
		}
	}
}

NodeList* childs(NodeAG* A, int e) {
	NodeList* result = NULL;
	childAG(A, e, result);
	return result;
}

void pairLevelInList(NodeAB* t, int k, NodeList*& l) {
	if (t == NULL) {
		return;
	}
	if (k == 1 && t->data % 2 == 0) {
		NodeList* node = new NodeList();
		node->data = t->data;
		node->next = l;
		l = node;
	}
	else {
		pairLevelInList(t->left, k - 1, l);
		pairLevelInList(t->right, k - 1, l);
	}
}

void rangeList(NodeAB* t, int inf, int sup, NodeList*& l) {
	if (t == NULL) {
		return;
	}

	if (inf > t->data || sup > t->data) {
		rangeList(t->right, inf, sup, l);
	}
	
	if (t->data > inf && t->data < sup) {
		NodeList* node = new NodeList();
		node->data = t->data;
		node->next = l;
		l = node;
	}

	if (inf < t->data || sup < t->data) {
		rangeList(t->left, inf, sup, l);
	}
}

NodeAB* searchNodeAB(NodeAB* t, int e) {
	if (t == NULL) {
		return NULL;
	}
	if (t->data == e) {
		return t;
	}
	NodeAB* node = searchNodeAB(t->left, e);
	if (node != NULL) {
		return node;
	}
	else {
		return searchNodeAB(t->right, e);
	}
}

int minNode(NodeAB* t) {
	if (t == NULL) {
		return 0;
	}
	int min = t->data;
	if (t->left != NULL) {
		int leftMin = minNode(t->left);
		if (min > leftMin) {
			min = leftMin;
		}
	}
	if (t->right != NULL) {
		int rightMin = minNode(t->right);
		if (min > rightMin) {
			min = rightMin;
		}
	}
	return min;
}

NodeAB* minimum(NodeAB* t) {
	int min = minNode(t);
	return searchNodeAB(t, min);
}

int main() {

	//int data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int data[] = { 7, 4, 11, 2, 5, 8, 3, 10 };
	int n = sizeof(data) / sizeof(data[0]);
	//NodeAB* root = createBinaryTree(data, 0, n);
	NodeAB* root = createBinarySearchTree(data, 0, n);
	//preOrder(root);
	//inOrder(root);
	//postOrder(root);
	//cout << minLevelK(root, 2);
	//cout << maxNode(root);
	//printRange(root, 3, 9);
	//NodeAB* result = rangeCopy(root, 1, 12);
	//preOrder(result);
	//eraseTree(root);
	//NodeAB* result = subTreeCopy(root, 4);
	//NodeList* result = NULL;
	//pairLevelInList(root, 4, result);
	//rangeList(root, 1, 12, result);
	NodeAB* result = minimum(root);
	preOrder(result);

	return 0;
}
