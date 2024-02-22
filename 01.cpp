#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
	int val;
	Node *left;
	Node *right;
};

Node* root = NULL;

Node* createNode(int value) {
	Node* newNode = (Node*) malloc(sizeof(Node));
	
	newNode->val = value;
	newNode->left = newNode->right = NULL;
	
	return newNode;
}

Node* insert(Node* curr, int value) {
	if (!curr) {
		return createNode(value);
	}
	
	if (value < curr->val) {
		curr->left = insert(curr->left, value);
	} else if (value > curr->val) {
		curr->right = insert(curr->right, value);
	}
	
	return curr;
}

Node* getPredecessor(Node* curr) {
	curr = curr->left;
	while (curr->right != NULL) {
		curr = curr->right;
	}
	return curr;
}

Node* getSuccessor(Node* curr) {
	curr = curr->right;
	while (curr->left != NULL) {
		curr = curr->left;
	}
	return curr;
}

Node* deleteNode(Node* curr, int value) {
	if (!curr) {
		return NULL;
	}
	
	if (value < curr->val) {
		curr->left = deleteNode(curr->left, value);
	} else if (value > curr->val) {
		curr->right = deleteNode(curr->right, value);
	} else if (value == curr->val) {
		// gapunya anak (leaf node)
		if (!curr->left && !curr->right) {
			free(curr);
			curr = NULL;
		} else if (!curr->left) { // gapunya anak kiri, punya anak kanan
			Node* temp = curr->right;
			free(curr);
			curr = temp;
		} else if (!curr->right) {  // gapunya anak kanan, punya anak kiri
			Node* temp = curr->left;
			free(curr);
			curr = temp;
		} else { // punya 2 anak
			Node* temp = getPredecessor(curr);
			curr->val = temp->val;
			curr->left = deleteNode(curr->left, temp->val);
		}
	}
	
	return curr;
}

void preOrder(Node* curr) {
	if (curr) {
		printf("%d ", curr->val);
		preOrder(curr->left);
		preOrder(curr->right);
	}
}

void inOrder(Node* curr) {
	if (curr) {
		inOrder(curr->left);
		printf("%d ", curr->val);
		inOrder(curr->right);
	}
}

void postOrder(Node* curr) {
	if (curr) {
		postOrder(curr->left);
		postOrder(curr->right);
		printf("%d ", curr->val);
	}
}

int main(){
	root = insert(root, 4);
	root = insert(root, 2);
	root = insert(root, 1);
	root = insert(root, 3);
	root = insert(root, 5);
	root = insert(root, 7);
	
	inOrder(root);
	
	root = deleteNode(root, 4);
	inOrder(root);
	
	return 0;
}
