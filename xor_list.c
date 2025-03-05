#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct xorlist 
{
	int data;
	struct xorlist *ptrdiff;
	struct xorlist *last;
} XORlist_t;

XORlist_t *
XOR(XORlist_t *x, XORlist_t *y)
{
	return (XORlist_t *)((uintptr_t)(x) ^ (uintptr_t)(y));
}

XORlist_t *
insert_front(XORlist_t *head, int data)
{
	XORlist_t *newnode = (XORlist_t *)malloc(sizeof(XORlist_t));
	newnode->data = data;
	newnode->ptrdiff = XOR(NULL, head);

	if (head) {
		head->ptrdiff = XOR(head->ptrdiff, newnode);
		head->last = newnode;
	}

	head = newnode;
	return head;
}

XORlist_t *
insert_end(XORlist_t *head, int data)
{
	XORlist_t *newnode = (XORlist_t *)malloc(sizeof(XORlist_t));
	newnode->data = data;

	if (head) {
		head->last->ptrdiff = XOR(XOR(head->last->ptrdiff, NULL), newnode);
	} else {
		head = newnode;
	}
	head->last = newnode;
	return head;
}

void
printlist(XORlist_t *head)
{
	XORlist_t *cur = head;
	XORlist_t *prev = NULL;

	while (cur) {
		printf("%d->", cur->data);
		XORlist_t *next = XOR(prev, cur->ptrdiff);
		prev = cur;
		cur = next;
	}
	printf("NULL\n");
}

int
main(void)
{
	XORlist_t *head;

	head = insert_front(head, 10);
	head = insert_front(head, 20);
	head = insert_front(head, 30);
	head = insert_front(head, 40);

	printlist(head);
	//head = insert_end(head, 100);
	//printlist(head);

	return 0;
}

