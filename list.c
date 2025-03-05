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
iterative_reverse(Node_t *head)
{
	Node_t *cur, *newhead, *next;

	if (head == NULL)
		return head;

	newhead = NULL;
	cur = head;
	while (cur != NULL) {
		next = cur->next;
		cur->next = newhead;
		newhead = cur;
		cur = next;
	}
	return newhead;
}
	
Node_t *
recursive_reverse(Node_t *head)
{
	Node_t *temp;

	if (head == NULL || head->next == NULL)
		return head;

	temp = recursive_reverse(head->next);
	head->next->next = head;
	head->next = NULL;

	return temp;
}

Node_t *
recursive_reverse1(Node_t *head)
{
	Node_t *p, *revrest;

	if (head == NULL || head->next == NULL)
		return head;

	p = head->next;
	head->next = NULL;
	revrest = recursive_reverse(p);
	p->next = head;
	return revrest;
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
swap_pairs(Node_t *head)
{
	printf("head before return: %d\n", head->data);
	if (head == NULL || head->next == NULL)
		return head;

//#if 0
	//1->2->3->4
	//head = 1
	//head->next = 2
	//head->next->next = 3

	Node_t *temp = head->next;
	printf("head = %d, temp = %d\n", head->data, temp->data);
	head->next = swap_pairs(head->next->next);
	if (head->next == NULL) 
		printf("%d->next = NULL\n", head->data);
	printf("after return: head = %d\n", head->data);
	temp->next = head;

	return temp;
//#endif
#if 0
	// Reverse 1st pair
	Node_t *temp = head->next;
	head->next = temp->next;
	temp->next = head;
	head = temp;

	// recurse for rest of the list
	head->next->next = swap_pairs(head->next->next);
	return head;
	/***************************************************
	Node_t *remHead = head->next->next;
	Node_t *newHead = head->next;
	newHead->next = head;
	head->next = swap_pairs(remHead);
	return newHead;
	***************************************************/
#endif
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

#if 0
	head = iterative_reverse(head);
	printf("reversed list:");
	print_slist(head);

	//head = recursive_reverse(head);
	head = recursive_reverse1(head);
	printf("list after recurse reverse:");
	print_slist(head);

#endif
	head = swap_pairs(head);
	//head = iterative_swap_pairs(head);
	//recursive_swap_pairs_values(head);
	printf("list after swapping pairs:");
	print_slist(head);

	return 0;
}
