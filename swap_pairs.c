#include <stdio.h>
#include <stdlib.h>

typedef struct slist
{
	int data;
	struct slist *next;
	struct slist *last;
} Node_t;

Node_t *
insert (Node_t *head, int x)
{
	Node_t *temp = (Node_t *)malloc(sizeof(Node_t));
	temp->data = x;
	temp->next = NULL;

	if (head == NULL) {
		head = temp;
		head->last = temp;
	} else {
		head->last->next = temp;
		head->last = head->last->next;
	}

	return head;
}

void
print_slist(Node_t *head)
{
	while (head) {
		printf("%d->", head->data);
		head = head->next;
	}
	printf("NULL\n");
}

Node_t *
iterative_swap_pairs_with_dummy_node(Node_t *head)
{
	Node_t *dummy = (Node_t *)malloc(sizeof(Node_t));
	Node_t *prev = dummy;
	Node_t *cur = head;

	while (cur && cur->next) {
		prev->next = cur->next;
		cur->next = cur->next->next;
		prev->next->next = cur;
		prev = cur;
		cur = cur->next;
	}
	return dummy->next;
}

Node_t *
iterative_swap_pairs(Node_t *head)
{
	if (head == NULL || head->next == NULL)
		return head;

	Node_t *curNode = head;
	Node_t *newHead = head->next;

	while (curNode != NULL && curNode->next != NULL) {
		Node_t *temp = curNode->next;
		curNode->next = curNode->next->next;
		temp->next = curNode;
		curNode = curNode->next;

		if (curNode != NULL && curNode->next != NULL)
			temp->next->next = curNode->next;
	}

	return newHead;
}

void
swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void
iterative_swap_pairs_values(Node_t *head)
{
	Node_t *cur = head;

	while (cur != NULL && cur->next != NULL) {
		swap(&cur->data, &cur->next->data);

		cur = cur->next->next;
	}
}

void recursive_swap_pairs_values(Node_t *head)
{
	if (head != NULL && head->next != NULL) {
		swap(&head->data, &head->next->data);
		recursive_swap_pairs_values(head->next->next);
	}
}

Node_t *
swap_pairs_rec(Node_t *head)
{
	if (head == NULL || head->next == NULL)
		return head;

	Node_t *temp = head->next;
	head->next = swap_pairs_rec(head->next->next);
	temp->next = head;

	return temp;
}

int
main(void)
{
	int n;
	Node_t *head = NULL;

	printf("Enter elements\n");
	while (scanf("%d", &n))
		head = insert(head, n);

	printf("Original list:");
	print_slist(head);

	head = swap_pairs_rec(head);
	printf("list after swapping pairs:");
	print_slist(head);

	return 0;
}
