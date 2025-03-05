#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
	int val;
	struct list *next;
} ListNode;

ListNode *
getnode(int val)
{
	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	node->val = val;
	node->next = NULL;

	return node;
}

void
printll(ListNode *head)
{
	while (head) {
		printf("%d->", head->val);
		head = head->next;
	}
	printf("NULL\n");
}

ListNode *mergeSortedLists_iter(ListNode *list1, ListNode *list2)
{
	ListNode *getnode(int);

	ListNode *dummy = getnode(-1);
	ListNode *res = dummy;

	while (list1 && list2) {
		if (list1->val <= list2->val) {
			res->next = list1;
			list1 = list1->next;
		} else {
			res->next = list2;
			list2 = list2->next;
		}
		res = res->next;
	}

	if (list1 != NULL)
		res->next = list1;
	else
		res->next = list2;

	return dummy->next;
}

ListNode *mergeSortedLists(ListNode *list1, ListNode *list2)
{
	if (list1 == NULL && list2 == NULL)
		return NULL;

	if (list1 == NULL) return list2;
	if (list2 == NULL) return list1;

	ListNode *res;

	if (list1->val <= list2->val) {
		res = list1;
		res->next = mergeSortedLists(list1->next, list2);
	} else {
		res = list2;
		res->next = mergeSortedLists(list1, list2->next);
	}

	return res;
}

ListNode *findMiddle(ListNode *head)
{
	if (head == NULL || head->next == NULL)
		return head;

	ListNode *slowPtr = head;
	ListNode *fastPtr = head->next;

	while (fastPtr != NULL && fastPtr->next != NULL) {
		slowPtr = slowPtr->next;
		fastPtr = fastPtr->next->next;
	}

	return slowPtr;
}

ListNode *
sortLL(ListNode *head)
{
	if (head == NULL || head->next == NULL)
		return head;

	ListNode *midNode = findMiddle(head);

	ListNode *right = midNode->next;
	midNode->next = NULL;
	ListNode *left = head;

	left = sortLL(left);
	right = sortLL(right);

	return mergeSortedLists(left, right);
}

int
main(void)
{
	ListNode *head = getnode(3);
	head->next = getnode(2);
	head->next->next = getnode(5);
	head->next->next->next = getnode(4);
	head->next->next->next->next = getnode(1);

	printf("List :");
	printll(head);

	head = sortLL(head);
	printf("List after sorting: ");
	printll(head);

	return 0;
}
