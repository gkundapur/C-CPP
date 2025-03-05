
#include <stdio.h>
#include <stdlib.h>

// Tree Node
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}Node_t;

Node_t *queue[100];
int front = -1;
int rear = 0;


void
enqueue(Node_t *node) 
{
	queue[rear++] = node;
}

Node_t *
dequeue(void)
{
	return queue[++front];
}

// Function to do level order traversal of given
// Binary Tree using a Queue
void 
levelOrderTraversal(Node_t *root) {
    if (root == NULL) return; 

    enqueue(root);
    while (rear - 1 != front) {
        Node_t *curr = dequeue();
        printf("%d ", curr->data);
        if (curr->left != NULL) enqueue(curr->left);
        if (curr->right != NULL) enqueue(curr->right);
    }
	printf("\n");
}

struct Node* newNode(int x) {
    Node_t *node = (Node_t *)malloc(sizeof(Node_t));
    node->data = x;
    node->left = node->right = NULL;
    return node;
}

int 
main() {
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->right = newNode(6);
    levelOrderTraversal(root);
    return 0;
}

