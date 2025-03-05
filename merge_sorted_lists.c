#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
	int data;
	struct list *next;
} List_t;

List_t *
CreateNode(int data)
{
	List_t *node = (List_t *)malloc(sizeof(node));
	node->data = data;
	node->next = NULL;

	return node;
}

void
printlist(List_t *head)
{
	while (head) {
		printf("%d -> ", head->data);
		head = head->next;
	}
	printf(" NULL\n");
}

List_t *
mergeTwoLists(List_t *list1, List_t *list2) 
{
	List_t *result = NULL;

	if (list1 == NULL)
		return list2;

	if (list2 == NULL)
		return list1;
        
	if (list1->data <= list2->data) {
		result = list1;
		result->next = mergeTwoLists(list1->next, list2);
	} else {
		result = list2;
		result->next = mergeTwoLists(list1, list2->next);
	}
	return result;
}

List_t *
mergeTwoLists_iter(List_t *list1, List_t *list2)
{
	List_t *head, *cur;

	if (list1 == NULL)
		return list2;
	if (list2 == NULL)
		return list1;

	if (list1->data <= list2->data) {
		head = list1;
		list1 = list1->next;
	} else {
		head = list2;
		list2 = list2->next;
	}

	cur = head;
	while (list1 != NULL && list2 != NULL) {
		if (list1->data < list2->data) {
			cur->next = list1;
			list1 = list1->next;
		} else {
			cur->next = list2;
			list2 = list2->next;
		}
		cur = cur->next;
	}

	if (list1 != NULL)
		cur->next = list1;
	else
		cur->next = list2;

	return head;
}
      
int 
main(void)
{
	List_t *list1 = CreateNode(1);
	list1->next = CreateNode(2);
	list1->next->next = CreateNode(4);

	List_t *list2 = CreateNode(1);
	list2->next = CreateNode(3);
	list2->next->next = CreateNode(4);

	printf("list1: ");
	printlist(list1);

	printf("list2: ");
	printlist(list2);

	//List_t *mergedList = mergeTwoLists(list1, list2);
	//printf("merged list: ");
	//printlist(mergedList);

	List_t *iterlist = mergeTwoLists_iter(list1, list2);
	printf("iter merged list: ");
	printlist(iterlist);

	return 0;
}


