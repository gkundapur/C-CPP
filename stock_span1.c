#include <stdio.h>
#include <string.h>

/**************************Stack implementation--------------------*/
int top = -1;
int N;

int Size()
{
	return top + 1;
}

int Empty()
{
	if (top < 0)
		return 1;
	else
		return 0;
}

void Push(int S[], int data)
{
	if (Size() == N) {
		printf("Stack is full\n");
		return;
	}
	S[++top] = data;
}

int Pop(int S[])
{
	if (Empty()) {
		printf("Stack is empty\n");
		return -1;
	}

	return S[top--];
}

int Top(int S[])
{
	if (Empty()) {
		printf("Stack is empty\n");
		return -1;
	}

	printf("stack top = %d\n", S[top]);
	return S[top];
}
/*****************************************************************/

void
calSpan(int price[], int S[], int N)
{
	int stack[N];

	Push(stack, 0);
	for (int i = 1; i < N; i++) {
		if (price[i] <= price[Top(stack)]) 
			Push(stack, i);
		else {
			while (price[i] > price[Top(stack)]) {
				int p = Pop(stack);
				S[i] = S[i] + S[p];
			}
			Push(stack, i);
		}
	}
}

void
calculateSpan(int price[], int S[], int N)
{
	int stack[N];

	memset(S, -1, N);
	Push(stack, 0);

	S[0] = 1;

	for (int i = 1; i < N; i++) {
		/* pop element from stack while stack is not empty and
		   top of stack is smaller than price[i]
		 */
		while (!Empty() && price[Top(stack)] <= price[i])
			 printf("i = %d, Popped = %d\n", i, Pop(stack));

		S[i] = Empty() ? i + 1 : i - Top(stack);

		Push(stack, i);
	}
}

void printArray(int S[], int n)
{
	for (int i = 0; i < n; i++)
		printf ("%d ", S[i]);
	printf("\n");
}

void iter_calculateSpan(int price[], int S[], int n)
{
	/* span value of first day is always 1 */
	S[0] = 1;

	for (int i = 1; i < n; i++) {
		S[i] = 1;  /* initialize span value */

		/* Traverse left while the next element on left is smaller than price[i] */
		for (int j = i - 1; j >= 0 && price[j] <= price[i]; j--)
			S[i]++;
	}
}

int
main(void)
{
	//int price[] = {10, 4, 5, 90, 120, 80};
	int price[] = {100, 80, 60, 70, 60, 75, 85};
	N = sizeof(price)/sizeof(price[0]);
	int S[N];

	memset(S, 0, N);
	calculateSpan(price, S, N);
	printf("Recursive: ");
	printArray(S, N);

	memset(S, 0, N);
	iter_calculateSpan(price, S, N);
	printf("\niterative: ");
	printArray(S, N);

#if 0
	for (int i = 0; i < N; i++)
		S[i] = 1;

	calSpan(price, S, N);
	printf("stock span: ");
	printArray(S, N);
#endif
	

	return 0;
}
