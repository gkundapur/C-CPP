#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
} Node_t;

Node_t *
newnode(int data)
{
	Node_t *node = (Node_t *)malloc(sizeof(Node_t));
	node->data = data;
	node->next = NULL;
}

void
printlist(Node_t *head)
{
	Node_t *cur = head;

	while (cur) {
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

int
findlength(Node_t *head)
{
	int len = 0;
	Node_t *cur = head;

	while (cur) {
		len++;
		cur = cur->next;
	}

	return len;
}

void
reverse(Node_t *head, int count, Node_t **rightNode, Node_t **afterRightNode)
{
	Node_t *newHead, *cur, *next;

	newHead = NULL;
	cur = head;
	while (count) {
		next = cur->next;
		cur->next = newHead;
		newHead = cur;
		cur = next;
		count--;
	}
	*rightNode = newHead;
	*afterRightNode = next;
}

Node_t *
reverseKGroup(Node_t *head, int k)
{
	if (head == NULL || k == 1)
		return head;

	int len = findlength(head);

	Node_t *beforeLeftNode = NULL;
	Node_t *leftNode = head;

	for (int i = 0; i < len/k; i++) {
		Node_t *rightNode = NULL;
		Node_t *afterRightNode = NULL;

		reverse(leftNode, k, &rightNode, &afterRightNode);

		if (i == 0)
			head = rightNode;
		else
			beforeLeftNode->next = rightNode;

		leftNode->next = afterRightNode;
		beforeLeftNode = leftNode;
		leftNode = afterRightNode;
	}

	return head;
}

int
main(void)
{
	Node_t *head = newnode(1);
	head->next = newnode(2);
	head->next->next = newnode(3);
	head->next->next->next = newnode(4);
	head->next->next->next->next = newnode(5);
	head->next->next->next->next->next = newnode(6);
	head->next->next->next->next->next->next = newnode(7);
	head->next->next->next->next->next->next->next = newnode(8);

	printf("List: ");
	printlist(head);

	int k = 3;
	head = reverseKGroup(head, k);
	printf("List after reversing in groups of %d: ", k);
	printlist(head);

	return 0;
}

