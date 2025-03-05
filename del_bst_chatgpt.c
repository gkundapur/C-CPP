#include <stdio.h>
#include <stdlib.h>

// Definition of the structure of a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node in the BST
struct Node* insert(struct Node* root, int data) {
    struct Node* newNode = createNode(data);
    if (root == NULL)
        return newNode;
    
    struct Node* parent = NULL;
    struct Node* current = root;

    // Find the correct position for the new node
    while (current != NULL) {
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    // Attach the new node
    if (data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

// Function to find the minimum value node in the right subtree (successor)
struct Node* findMin(struct Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Iterative function to delete a node in a BST
struct Node* deleteNode(struct Node* root, int key) {
    struct Node* parent = NULL;
    struct Node* current = root;

    // Search for the node to be deleted and track its parent
    while (current != NULL && current->data != key) {
        parent = current;
        if (key < current->data)
            current = current->left;
        else
            current = current->right;
    }

    // If the node was not found, return the original root
    if (current == NULL)
        return root;

    // Case 1: Node with no children (leaf node)
    if (current->left == NULL && current->right == NULL) {
        if (current != root) {
            if (parent->left == current)
                parent->left = NULL;
            else
                parent->right = NULL;
        } else {
            root = NULL;
        }
        free(current);
    }

    // Case 2: Node with two children
    else if (current->left != NULL && current->right != NULL) {
        // Find the inorder successor (minimum value in the right subtree)
        struct Node* successor = findMin(current->right);

        // Store the successor's value in the current node
        int val = successor->data;
        
        // Recursively delete the successor
        root = deleteNode(root, successor->data);
        
        // Replace current node's data with successor's value
        current->data = val;
    }

    // Case 3: Node with one child
    else {
        struct Node* child = (current->left) ? current->left : current->right;

        // If the node to be deleted is not the root
        if (current != root) {
            if (current == parent->left)
                parent->left = child;
            else
                parent->right = child;
        } else {
            root = child;
        }
        free(current);
    }

    return root;
}

// In-order traversal of the BST
void inorderTraversal(struct Node* root) {
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

// Main function to demonstrate the delete operation
int main() {
    struct Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("In-order traversal before deletion: \n");
    inorderTraversal(root);
    printf("\n");

    root = deleteNode(root, 50); // Delete node with key 50

    printf("In-order traversal after deletion: \n");
    inorderTraversal(root);
    printf("\n");

    return 0;
}

