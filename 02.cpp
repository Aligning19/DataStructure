#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct storage{
    int qty;
    char name[25];
    char category[20];
    struct storage *left;
    struct storage *right;
};

struct storage *newNode(const char *name, const char *category){
    struct storage *curr = (struct storage *) malloc(sizeof(struct storage));
    curr->qty = 1;
    strcpy(curr->name, name);
    strcpy(curr->category, category);
    curr->left = NULL;
    curr->right = NULL;
    return curr;
}

struct storage *insert(struct storage *root, const char *name, const char *category){
    if (!root) {
    	return newNode(name, category);
	}
	
	if (strcmp(name, root->name) > 0) {
		root->right = insert(root->right, name, category);
	} else if (strcmp(name, root->name) < 0) {
		root->left = insert(root->left, name, category);
	} else if (strcmp(name, root->name) == 0) {
		root->qty++;
	}
    
    return root;
}

struct storage *predecessor(struct storage *root){
    root = root->left;
    while (root->right) {
    	root = root->right;
	}
	return root;
}

struct storage *successor(struct storage *root){
    root = root->right;
    while (root->left) {
    	root = root->left;
	}
	return root;
}

struct storage *deleteKey(struct storage *root, const char *name){
    if (!root) {
    	return NULL;
	}
	
	if (strcmp(name, root->name) > 0) {
		root->right = deleteKey(root->right, name);
	} else if (strcmp(name, root->name) < 0) {
		root->left = deleteKey(root->left, name);
	} else if (strcmp(name, root->name) == 0) {
		if (root->qty == 1) {
			if (!root->left && !root->right) {
				free(root);
				root = NULL;
			} else if (!root->left) {
				storage* temp = root->right;
				free(root);
				root = temp;
			} else if (!root->right) {
				storage* temp = root->left;
				free(root);
				root = temp;
			} else {
				storage* temp = predecessor(root);
				
				root->qty = temp->qty;
				temp->qty = 1;
				strcpy(root->name, temp->name);
				strcpy(root->category, temp->category);
				
				root->left = deleteKey(root->left, temp->name);
			}
		} else {
			root->qty--;
		}
	}
    
    return root;
}

void inOrder(struct storage *root){
    if(root){
    	inOrder(root->left);
    	printf("%s (%-3d)\n", root->name, root->qty);
    	inOrder(root->right);
    }
}

struct storage *freeAll(struct storage *root){
    if(root){
        freeAll(root->left);
        freeAll(root->right);
        free(root);
        root = NULL;
    }
    return root;
}

int main(){
    struct storage *root = NULL;

    root = insert(root, "Sate Ayam", "Daging");
    root = insert(root, "Gulai Kambing", "Daging");
    root = insert(root, "Kangkung", "Sayuran");
    root = insert(root, "Coca Cola", "Minuman");
    root = insert(root, "Sate Kambing", "Daging");
    root = insert(root, "Opor Ayam", "Daging");
    root = insert(root, "Sprite", "Minuman");
    root = insert(root, "Fanta", "Minuman");
    root = insert(root, "Ayam Kalasan", "Daging");
    root = insert(root, "Kangkung", "Sayuran");
    root = insert(root, "Fanta", "Minuman");
    root = insert(root, "Coca Cola", "Minuman");
    root = insert(root, "Opor Ayam", "Daging");

    printf("Predecessor : %s\n", predecessor(root)->name);
    printf("Successor : %s\n", successor(root)->name);

    printf("\nInorder : \n");
    inOrder(root);

    root = deleteKey(root, "Sate Ayam");
    root = deleteKey(root, "Gulai Kambing");
    root = deleteKey(root, "Coca Cola");
    root = deleteKey(root, "Opor Ayam");
    root = deleteKey(root, "Sate Kambing");
    root = deleteKey(root, "Ayam Kalasan");
    printf("\nAfter Del Inorder : \n");
    inOrder(root);
    
    freeAll(root);
    return 0;
}
