#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
	char c;
	struct list *next;
} Node_t;

int
findlength(Node_t *head, Node_t **lastNode)
{
	int len = 1;

	while (head->next) {
		len++;

		head = head->next;
	}
	*lastNode = head;

	return len;
}

Node_t *
rotatell(Node_t *head, int k)
{
	Node_t *lastNode;
	int len;

	if (head == NULL || k == 0)
		return head;

	len = findlength(head, &lastNode);

	// connect last node to head
	lastNode->next = head;

	// if k > len, rotate k % l times
	k = k % len;

	// move lastNode by len-k times
	for (int i = 0; i < len -k; i++)
		lastNode = lastNode->next;

	head = lastNode->next;
	lastNode->next = NULL;

	return head;
}

Node_t *
newnode(char c)
{
	Node_t *node = (Node_t *)malloc(sizeof(Node_t));
	node->c = c;
	node->next = NULL;

	return node;
}

Node_t *
createll(void)
{
	Node_t *head = newnode('A'); // A 
	head->next = newnode('B');  // A->B
	head->next->next = newnode('C'); //A->B->C
	head->next->next->next = newnode('D'); //A->B->C-D
	head->next->next->next->next = newnode('E'); //A->B->C-D->E
	head->next->next->next->next->next = newnode('F'); //A->B->C-D->E->F
	head->next->next->next->next->next->next = newnode('G'); //A->B->C-D->E->F->G

	return head;
}

void
printll(Node_t *head)
{
	while (head) {
		printf("%c ", head->c);
		head = head->next;
	}
	printf("\n");
}

int
main(void)
{
	int k;

	Node_t *head = createll();
	printf("Linked list: ");
	printll(head);

	k = 1;
	Node_t *newhead = rotatell(head, k);
	printf("list after rotating right by %d places: ", k);
	printll(newhead);

	head = createll();
	k = 4;
	newhead = rotatell(head, k);
	printf("list after rotating right by %d places: ", k);
	printll(newhead);

	head = createll();
	k = 7;
	newhead = rotatell(head, k);
	printf("list after rotating right by %d places: ", k);
	printll(newhead);

	head = createll();
	k = 12;
	newhead = rotatell(head, k);
	printf("list after rotating right by %d places: ", k);
	printll(newhead);

	return 0;
}


