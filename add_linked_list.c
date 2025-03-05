#include <stdio.h>
#include <stdlib.h>

typedef struct listnode {
	int data;
	struct listnode *next;
} ListNode_t;

ListNode_t *
createnode(int val)
{
	ListNode_t *node = (ListNode_t *)malloc(sizeof(ListNode_t));

	node->data = val;
	node->next = NULL;

	return node;
}


void
printList(ListNode_t *head)
{
	ListNode_t *cur = head;

	while (cur) {
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

ListNode_t *reverse(ListNode_t *head)
{
	if (head == NULL || head->next == NULL)
		return head;

	ListNode_t *newhead = reverse(head->next);
	head->next->next = head;
	head->next = NULL;

	return newhead;
}

ListNode_t *
addLists(ListNode_t *L1, ListNode_t *L2)
{
	ListNode_t *res = NULL, *cur = NULL;
	int carry = 0;

	L1 = reverse(L1);
	L2 = reverse(L2);

	// iterate till either L1 is not empty or L2 is not empty
	// or carry is greater than 0
	while (L1 != NULL || L2 != NULL || carry != 0) {
		int sum = carry;

		// if L1 is not empty, add it to sum
		if (L1 != NULL) {
			sum += L1->data;
			L1 = L1->next;
		}

		// if L2 is not empty, add it to sum
		if (L2 != NULL) {
			sum += L2->data;
			L2 = L2->next;
		}

		// create a new node with sum % 10 as its data
		ListNode_t *newnode = createnode(sum % 10);

		// store carry for next node
		carry = sum / 10;

		// if this is the first node, make this as head of resultant list
		if (res == NULL) {
			res = newnode;
			cur = newnode;
		} else {
			cur->next = newnode;
			cur = cur->next;
		}
	}

	// reverse the resultant list
	return reverse(res);
}

ListNode_t *insertBeg(ListNode_t *head, int val)
{
	ListNode_t *temp = (ListNode_t *)malloc(sizeof(ListNode_t));
	temp->data = val;
	temp->next = NULL;

	if (head == NULL)
		return temp;
	temp->next = head;
	return temp;
}

int
findLen(ListNode_t *head)
{
	int len = 0;
	while (head) {
		len++;
		head = head->next;
	}
	return len;
}

// adding without reversing input list
ListNode_t *
addLists_1(ListNode_t *L1, ListNode_t *L2)
{
	int n1 = findLen(L1);
	int n2 = findLen(L2);
	int carry = 0;
	ListNode_t *result = NULL;

	// add node values
	while (n1 != 0 || n2 != 0) {
		int sum = carry;
		if (n1 == n2) {
			sum += L1->data + L2->data;
			L1 = L1->next;
			L2 = L2->next;
			n1--;
			n2--;
		} else if (n1 > n2) {
			sum += L1->data;
			L1 = L1->next;
			n1--;
		} else {
			sum += L2->data;
			L2 = L2->next;
			n2--;
		}
		result = insertBeg(result, sum);
	}

	ListNode_t *cur, *prev;

	carry = 0;
	cur = result;
	prev = NULL;
	while (cur) {
		int digit = (cur->data + carry) % 10;
		carry = (cur->data + carry) / 10;
		cur->data = digit;
		prev = cur;
		cur = cur->next;
	}

	if (carry) 
		prev->next = createnode(carry);

	return reverse(result);
}

int
main(void)
{
	// list1: 1->2->3
	ListNode_t *list1 = createnode(1);
	list1->next = createnode(2);
	list1->next->next = createnode(3);

	//list2: 9->9->9
	ListNode_t *list2 = createnode(9);
	list2->next = createnode(9);
	list2->next->next = createnode(9);

	printf("List1: ");
	printList(list1);
	printf("List2: ");
	printList(list2);

	ListNode_t *sum = addLists(list1, list2);
	//ListNode_t *sum = addLists_1(list1, list2);
	printList(sum);

	return 0;
}
