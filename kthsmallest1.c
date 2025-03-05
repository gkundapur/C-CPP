// A simple inorder traversal based C++ program to find k-th
// smallest element in a BST.
#include <stdio.h>
#include <stdlib.h>

// A BST node
typedef struct Node {
    int data;
    struct Node *left, *right;
    int lCount;
} Node;

Node* new_node(int x)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->data = x;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Recursive function to insert an key into BST
Node* insert(Node* root, int x)
{
    if (root == NULL)
        return new_node(x);

    // If a node is inserted in left subtree, then lCount of
    // this node is increased. For simplicity, we are
    // assuming that all keys (tried to be inserted) are
    // distinct.
    if (x < root->data) {
        root->left = insert(root->left, x);
        root->lCount++;
    }

    else if (x > root->data)
        root->right = insert(root->right, x);
    return root;
}

// Function to find k'th smallest element in BST
// Here count denotes the number of nodes processed so far
Node* kthSmallest(Node* root, int k)
{
    // base case
    if (root == NULL)
        return NULL;
    int count = root->lCount + 1;
    if (count == k)
        return root;
    if (count > k)
        return kthSmallest(root->left, k);
    // else search in right subtree
    return kthSmallest(root->right, k - count);
}

// main function
int main()
{
    Node* root = NULL;
    int keys[] = { 20, 8, 22, 4, 12, 10, 14 };
    int keys_size = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < keys_size; i++)
        root = insert(root, keys[i]);
    int k = 4;
    Node* res = kthSmallest(root, k);
    if (res == NULL)
        printf("There are less than k nodes in the BST\n");
    else
        printf("K-th Smallest Element is %d\n", res->data);
    return 0;
}

// This code is contributed by Aditya Kumar (adityakumar129)
