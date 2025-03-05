#include <stdio.h>
#include <limits.h>
#include <string.h>

#define SIZE 10

int st[SIZE];
int top;

void
initializeStack() 
{
	top = -1;
}

int
isStackFull()
{
	if (top == SIZE - 1)
		return 1;
	return 0;
}

int
isStackEmpty()
{
	if (top == -1)
		return 1;
	return 0;
}

void
push(int ele)
{
	if (!isStackEmpty()) {
		st[++top] = ele;
	}
}

int
pop(void) 
{
	int poppedEle;

	if (!isStackEmpty())
		poppedEle = st[top--];
	else
		poppedEle = INT_MIN;
	
	return poppedEle;
}

void
calculateSpan(int price[], int n, int S[])
{
	S[0] = 1;

	for (int i = 1; i < n; i++) {
		S[i] = 1;

		// traverse left while next element on left is smaller than price[i]
		for (int j = i - 1; j >= 0 && price[i] >= price[j]; j--)
			S[i]++;
	}
}

void 
calculateSpan(int price[], int n, int S[])
{
	int i, j;

	for (i = 0; i < n; i++) {
		j = 1;
		while (j <= i && price[i] > price[i-j])
			j = j + 1;
		S[i] = j;
	}
}

void
calculateSpanUsingStack(int price[], int n, int S[])
{
	int p;
	initializeStack();

	push(0);
	S[0] = 1;

	for (int i = 1; i < n; i++) {
		while (!isStackEmpty() && price[st[top]] <= price[i])
			pop();
		S[i] = isStackEmpty() ? (i+1) : (i-st[top]);
		push(i);
	}
}

void 
calculateSpanUsingStack1(int price[], int n, int S[])
{
	int i = 0, p;

	for (i = 0; i < n; i++)
		S[i] = 1;

	push(0);
	for (i = 1; i < n; i++) {
		if (price[i] <= price[st[top]])
			push(i);
		else {
			while (price[i] > price[st[top]]) {
				p = pop();
				S[i] += S[p];
			}
			push(i);
		}
	}
}


void
printArray(int a[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int
main(void)
{
	int price[] = {10, 4, 5, 90, 120, 80};
	int n = sizeof(price)/sizeof(price[0]);
	int S[n];

	calculateSpan(price, n, S);
	printf("Using Iterative algo-----------\n");
	printf("Price array: ");
	printArray(price, n);

	printf("Span array: ");
	printArray(S, n);

	memset(S, 1, n);
	calculateSpanUsingStack1(price, n, S);
	printf("Using stack--------------------\n");
	printf("Price array: ");
	printArray(price, n);

	printf("Span array: ");
	printArray(S, n);

	return 0;
}
