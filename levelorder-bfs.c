#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

// Function prototypes
void printCurrentLevel(struct node* root, int level);
int height(struct node* node);
int Height(struct node* node);
struct node* newNode(int data);

// Print nodes at a current level
void printCurrentLevel(struct node* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->data);
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}

int
max (int a, int b)
{
	return a > b ? a : b;
}

int Height(struct node *node)
{
	if (node == NULL)
		return 0;

	return 1 + max(Height(node->left), Height(node->right));
}

// Function to print level order traversal a tree
void printLevelOrder(struct node* root)
{
    //int h = height(root);
    int h = Height(root);
    int i;
    for (i = 1; i <= h; i++)
        printCurrentLevel(root, i);
	printf("\n");
}

// Compute the "height" of a tree -- 
int height(struct node* node)
{
    if (node == NULL)
        return 0;
    else {
        int lheight = height(node->left);
        int rheight = height(node->right);
        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

struct node* newNode(int data)
{
    struct node* node
        = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return (node);
}
int main()
{
    struct node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    printLevelOrder(root);
    return 0;
}
