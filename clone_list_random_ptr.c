#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
	int data;
	struct node *next;
	struct node *random;
} Node_t;

Node_t *
CreateNode(int data)
{
	Node_t *node = (Node_t *)malloc(sizeof(Node_t));
	node->data = data;
	node->next = NULL;
	node->random = NULL;

	return node;
}

void
printList(Node_t *head)
{
	while (head) {
		printf("%d(", head->data);
		if (head->random)
			printf("%d)", head->random->data);
		else
			printf("NULL)");
		if (head->next)
			printf(" -> ");
		head = head->next;
	}
	printf("\n");
}

Node_t *
copyRandomList(Node_t *head)
{
	if (head == NULL)
		return head;

	// Create new nodes and insert them next to the original nodes
	Node_t *cur = head;
	while (cur) {
		Node_t *newNode = CreateNode(cur->data);
		newNode->next = cur->next;
		cur->next = newNode;
		cur = newNode->next;
	}

	// Set the random pointers of the new nodes
	cur = head;
	while (cur && cur->next) {
		if (cur->random == NULL)
			cur->next->random = NULL;
		else
			cur->next->random = cur->random->next;
		cur = cur->next->next;
	}

	// Seperate the new nodes from the original nodes
	Node_t *clonedHead = head->next;
	Node_t *clone = clonedHead;
	cur = head;

	while (cur && clone) {
		cur->next = cur->next ? cur->next->next : NULL;
		clone->next = clone->next ? clone->next->next : NULL;

		cur = cur->next;
		clone = clone->next;
	}

	return clonedHead;
}


int
main(void)
{
	Node_t *head = CreateNode(1);
	head->next = CreateNode(2);
	head->next->next = CreateNode(3);
	head->next->next->next = CreateNode(4);
	head->next->next->next->next = CreateNode(5);

	head->random = head->next->next;
	head->next->random = head;
	head->next->next->random = head->next->next->next->next;
	head->next->next->next->random = head->next->next;
	head->next->next->next->next->random = head->next;

	printf("Original list:");
	printList(head);

	Node_t *clonedList = copyRandomList(head);
	printf("Cloned list:");
	printList(clonedList);

	return 0;
}
