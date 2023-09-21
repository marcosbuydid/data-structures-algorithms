#include <iostream>
#include <stdio.h>
using namespace std;

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

void preOrder(NodeAB* p) {
    if (p) {
        cout << p->data << ", " << flush;
        preOrder(p->left);
        preOrder(p->right);
    }
}

void inOrder(NodeAB* p) {
    if (p) {
        inOrder(p->left);
        cout << p->data << ", " << flush;
        inOrder(p->right);
    }
}

void postOrder(NodeAB* p) {
    if (p) {
        postOrder(p->left);
        postOrder(p->right);
        cout << p->data << ", " << flush;
    }
}


int main() {

    int data[] = { 1, 2, 3, 4, 5, 6, 6, 6, 6 };
    int n = sizeof(data) / sizeof(data[0]);
    NodeAB* root = createBinaryTree(data, 0, n);
    preOrder(root);

    return 0;
}
