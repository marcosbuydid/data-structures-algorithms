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
	else {
		printRange(t->right, min, max);
		if (t->data >= min && t->data <= max) {
			cout << t->data << ", " << flush;
		}
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
	NodeAB* result = rangeCopy(root, 1, 12);
	preOrder(result);
	
	return 0;
}
