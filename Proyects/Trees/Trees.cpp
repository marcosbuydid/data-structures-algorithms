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


int main() {

    //int data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int data[] = { 7, 4, 11, 2, 5, 8, 3, 10 };
    int n = sizeof(data) / sizeof(data[0]);
    NodeAB* root = createBinaryTree(data, 0, n);
    //preOrder(root);
    //inOrder(root);
    //postOrder(root);
    //cout << minLevelK(root, 2);
    //cout << maxNode(root);
    printRange(root, 3, 9);

    return 0;
}
