int
height(Node *root, int& diameter)
{
	if (root == NULL)
		return 0;

	int lh = height(root->left, diameter);
	int rh = height(root->right, diameter);

	diameter = max(diameter, lh+rh);

	return 1 + max(lh, rh);

}

// diameter
int
diameter(Node *root)
{
	int diameter = 0;
	height(root, diameter);
	return diameter;
}

/*************************************************************
Print path with given sum
                  1
			  /      \
			 2        3
		   /   \     /  \
		  4     5    6   7
		/   \      /  \   \
		8   9      10 11   12

***************************************************************/
int sum = 0;
void inorder(Node *root, int K)
{
	if (root == NULL)
		return;

	// Create stack S

	sum = sum + root->data;
	push(S, root->data);
	if (sum == K)
		printf("stack contents\n");
	inorder(root->left);
	inorder(root->right);

	sum = sum-root->data;
	pop(S);
}

/***************************************************************
Zig-Zag/spiral traveral

Create stack S1 and S2
Push root in S1
while (!isEmpty(S1))
	root = Pop()
	print(root->data)
	if (root->left != NULL)
		push(S2, root->left)
	if (root->right != NULL)
		push(S2, root->right);
	while (!isEmpty(S2) 
		root = Pop(S2);
		print(root->data);
		push(S1, root->right);
		push(S1, root->left);
}
******************************************************************/

//Lowest common ancestor of two nodes
Node *LCA(Node *root, Node *p, Node *q)
{
	if (root == NULL)
		return root;

	if (root == p || root == q)
		return root;

	Node *left = LCA(root->left, p, q);
	Node *right = LCA(root->right, p, q);

	if (left != NULL && right != NULL)
		return root;
	else
		return left ? left : right;
}




