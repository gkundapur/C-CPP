#include <stdio.h>


List_t *mid(List_t *head)
{
	List_t *fast = head;
	List_t *slow = head;
	List_t *prev = head;

	while (fast != NULL and fast->next != NULL) {
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	if (prev != NULL)
		prev->next = NULL;
	return slow;
}

Tree_t *
sortedListToBST(List_t *head)
{
	if (head == NULL)
		return NULL;

	List_t *mid = mid(head);
	Tree_t *root = new treenode(mid->data);

	if (head == mid)
		return root;

	root->left = sortedListToBST(head);
	root->right = sortedListToBST(mid->next);
	return root;
}
