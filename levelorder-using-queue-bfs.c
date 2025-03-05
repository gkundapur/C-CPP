#include <stdio.h>
#include <stdlib.h>

// Tree Node
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Queue is implemented using singly 
// Linked List
struct QNode {
    struct Node *tNode;
    struct QNode *next;
};
// Ideally we should not use global variables. We have used here
// to reduce code length. Below is the code without globals
// https://ide.geeksforgeeks.org/online-c-compiler/022957c0-7344-4773-b2b9-8c0695418af1
struct QNode *front = NULL;
struct QNode *rear = NULL;

// The following functions are defined later
// in this code
void enqueue(struct Node *tNode);
struct Node *dequeue();

// Function to do level order traversal of given
// Binary Tree using a Queue
void levelOrderTraversal(struct Node* root) {
    if (root == NULL) return; 

    enqueue(root);
    
    while (front != NULL) {
        struct Node* curr = dequeue();
        printf("%d ", curr->data);
        if (curr->left != NULL) enqueue(curr->left);
        if (curr->right != NULL) enqueue(curr->right);
    }
}

struct Node* newNode(int x) {
    struct Node* node = 
     (struct Node*)malloc(sizeof(struct Node));
    node->data = x;
    node->left = node->right = NULL;
    return node;
}
struct QNode* newQNode(struct Node* tNode) {
    struct QNode* qNode = 
     (struct QNode*)malloc(sizeof(struct QNode));
    qNode->tNode = tNode;
    qNode->next = NULL;
    return qNode;
}
void enqueue(struct Node *tNode) {
    struct QNode* qNode = newQNode(tNode);
    
    if (rear == NULL) {
        front = rear = qNode;
    } else {
        rear->next = qNode;
        rear = qNode;
    }
}
struct Node* dequeue() {
    if (front == NULL) return NULL; 
    struct Node* tNode = front->tNode;
    struct QNode* temp = front;
    front = front->next;
    if (front == NULL) rear = NULL; 
    free(temp);
    return tNode;
}
int main() {
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->right = newNode(6);
    levelOrderTraversal(root);
    return 0;
}

