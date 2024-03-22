#include <stdio.h>
#include <stdlib.h>

//groupwork of: Wangari Joy Wanjiru - SCT221-0210/2022
			// Margaret Karanja - SCT221-0229/2022
			//Lisa Wanjiku - SCT221-0562/2022

struct Node {
    int key;
    struct Node *left, *right;
};

//  create a new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}


struct Node* insert(struct Node* node, int key) {
    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = root->right;
        while (temp && temp->left != NULL)
            temp = temp->left;

        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}


int height(struct Node* node) {
    if (node == NULL)
        return -1;
    else {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}


void printLevelAndHeight(struct Node* root, int key, int level) {
    if (root == NULL) {
        printf("Node with key %d not found in the BST.\n", key);
        return;
    }
    if (key == root->key) {
        printf("Level of node with key %d is %d.\n", key, level);
        printf("Height of node with key %d is %d.\n", key, height(root));
        return;
    }
    if (key < root->key)
        printLevelAndHeight(root->left, key, level + 1);
    else
        printLevelAndHeight(root->right, key, level + 1);
}


void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

int main() {
    int keys[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(keys) / sizeof(keys[0]);
    struct Node* root = NULL;
	int i;
    // Creating the BST
    for( i = 0; i < n; i++){
        root = insert(root, keys[i]);
  }
    printf("In-order traversal of the BST: ");
    inorder(root);
    printf("\n");

    
    int keyToDelete = 25;
    root = deleteNode(root, keyToDelete);
    printf("In-order traversal after deleting node with key %d: ", keyToDelete);
    inorder(root);
    printf("\n");

    
    printf("Height of the BST: %d\n", height(root));

    // Printing level and height of a specific node (for example, node with key 20)
    int keyToFind = 20;
    printLevelAndHeight(root, keyToFind, 0);

    return 0;
}
