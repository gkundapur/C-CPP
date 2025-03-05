/*-----------------preorder------------------*/
Recursive_preorder(TreeNode *root) // Root, left, Right
{
	if (root) {
		print root->val
		Recursive_preorder(root->left);
		Recursive_preorder(root->right);
	}
}

Iterative_Preorder(TreeNode *root)
{
	stack<TreeNode *>st;
	TreeNode *cur;

	st.push(root);
	while (!st.empty()) {
		cur = st.top();
		st.pop();
		print cur->val
		if (cur->right)
			st.push(cur->right);
		if (cur->left)
			st.push(cur->left);
	}
}


/*-------------InOrder--------------------------*/
Recursive_Inorder(TreeNode *root) // Left, Root, RIght
{
	if (root) {
		Recursive_Inorder(root->left);
		print root->val;
		Recursive_Inorder(root->right);
	}
}

Iterative Inorder(TreeNode *root)
{
	create empty stack
	stack<TreeNode *> st;
	TreeNode *cur = root;
	while (cur != NULL || !st.empty()) {
		if (cur != NULL) {
			st.push(cur);
			cur = cur->left;
		} else {
			cur = st.top();
			st.pop();
			print cur->val;
			cur = cur->right;
		}
	}
}
/*--------------------Postorder-------------------*/
Recursive_Postorder(TreeNode *root) // Left, Right, Root
{
	if (root) {
		Recursive_Postorder(root->left);
		Recursive_Postorder(root->right);
		print root->val;
	}
}

Iterative_Postorder_using2stack(TreeNode *root)
{
	stack<TreeNode *> st1, st2;
	TreeNode *cur;

	st.push(root);
	while (!st1.empty()) {
		cur = st1.top();
		st1.pop();
		st2.push(cur);
		if (cur->left)
			st1.push(cur->left);
		if (cur->right)
			st1.push(cur->right);
	}

	while(!st2.empty()) {
		cur = st2.top();
		st2.pop();
		print cur>val;
	}
}

Iterative_Postorder_using1stack(TreeNode *root)
{
	stack<TreeNode *> st;
	TreeNode *cur = root;
	TreeNode *prev = NULL;

	while (cur != NULL || !st.empty()) {
		if (cur != NULL) {
			st.push(cur);
			cur = cur->left;
		} else {
			cur = st.top();
			if (cur->right == NULL || cur->right == prev) {
				print cur->val
				st.pop();
				prev = cur;
				cur = NULL;
			} else
				cur = cur->right;
	}
}

/***************Level order **************/

int h = Height(root);
for level = 0 to h
	printlevel(root, level);

printlevel(root, level)
{
	if (root == NULL)
		return;

	if (level == 0)
		print root->val
	else {
		printlevel(root->left, level-1);
		printlevel(root->right, level-1);
	}
}

print_levelorder(TreeNode *root)
{
	queue<TreeNode *> que;
	TreeNode *cur;

	que.push(root)
	while (!que.empty()) {
		cur = que.front();
		print cur->val
		que.pop();
		if (cur->left)
			que.push(cur->left);
		if (cur->right)
			que.push(cur->right);
	}
}

/*********Morris(Inorder)---------------------*/
Morris_inorder(TreeNode *root) // left, root, right
{
	TreeNode *cur = root;

	while (cur != NULL) {
		if (cur->left == NULL) {
			print cur->val;
			cur = cur->right;
		} else {
			predecessor = findpredecessor(cur);
			if (predecessor->righ == NULL) {
				// create virtual link
				predecessor->right = cur;
				cur = cur->left;
			} else {
				// remove virtual link
				predecessor->right = NULL;
				print cur->val;
				cur = cur->right;
			}
		}
	}
}

/**********Morris Preorder----------------------*/
Morris_Preorder(TreeNode *root) 
{
	TreeNode *cur = root;
	while (cur != NULL) {
		if (cur->left == NULL) {
			print cur->val;
			cur = cur->right;
		} else {
			pred = findpred(cur);
			if (pred->right == NULL) {
				pred->right = cur;
				print cur->val;
				cur = cur->left;
			} else {
				pred->right = NULL;
				cur = cur->right;
			}
		}
	}
}

/*************Morris PostOrder****************/
Morris_postorder(TreeNode *root) 
{
	stack<TreeNode *> st;
	TreeNode *cur = root;
	while (cur != NULL) {
		if (cur->right == NULL) {
			st.push(cur);
			cur = cur->left;
		} else {
			TreeNode *pred = findpred(cur);
			if (pred->left == NULL) {
				pred->left = cur;
				st.push(cur);
				cur = cur->right;
			} else {
				pred->left = NULL;
				cur = cur->right;
			}
		}
	}

	while (!st.empty()) {
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;
}


/*------------------------zig zag traversal----------*/
// using recursion - O(n^2) not efficient
bool ltr = false

h = height(root);
for level = 0 to h
	printlevel(root, level, ltr);
	ltr = !ltr;

printlevel(root, level, ltr)
{
	if (root == NULL)
		return;

	if (level == 0)
		print root->val
	else if level > 0 {
		if (ltr == true) { // left to right
			printlevel(root->left, level-1, ltr);
			printlevel(root->right, level-1, ltr);
		} else { //right to left
			printlevel(root->right, level-1, ltr);
			printlevel(root->left, level-1, ltr);
		}
	}
}


// using queue+stack
zig-zag(TreeNode *root) 
{
	queue<TreeNode *> que;
	stack<TreeNode *> st;
	bool ltr = false;

	que.push(root) {
	while (!que.empty()) {
		size = que.size();
		while (size) {
			size--;
			TreeNode *cur = que.front();
			que.pop();
			if (ltr == true)
				print cur->val;
			else
				st.push(cur);
			if (cur->left)
				que.push(cur->left);
			if (cur->right)
				que.push(cur->right);
		}
		if (ltr == false)
			pop and print contents of stack
		ltr = !ltr; // togle ltr
	}
}

//using 2 stacks
zig-zag(TreeNode *root)
{
	stack<TreeNode *> st1, st2;

	st1.push(root);
	while (!st1.emptry() || !st2.empty()) {
		while (!st1.empty()) {
			TreeNode *cur = st1.top();
			st1.pop();
			print cur->val;
			if (cur->right)
				st2.push(cur->right);
			if (cur->left)
				st2.push(cur->left);
		} 
		while (!st2.empty()) {
			TreeNode *cur = st2.top();
			st2.pop();
			print cur->val
			if (cur->left)
				st1.push(cur->left);
			if (cur->right)
				st1.push(cur->right);
		}
	}
}

// using deque
zig-zag(TreeNode *root)
{
	dequeue<TreeNode *>deq;
	bool ltr = false;

	deq.push_front(root);
	while (!deq.empty()) {
		size = deq.size();
		while (size--) {
			if (ltr == false) {
				TreeNode *cur = deq.pop_front();
				print cur->val
				if (cur->left)
					deq.push_back(cur->left);
				if (cur->right)
					deq.push_back(cur->right);
			} else {
				TreeNode *cur = deq.pop_back()
				print cur->val;
				if (cur->right)
					deq.push_front(cur->right);
				if (cur->left)
					deq.push_front(cur->left);
			}
		}
		ltr = !ltr;
	}
}
	while (!st2
