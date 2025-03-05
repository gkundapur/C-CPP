#include <stdio.h>
#include <stdlib.h>

// Stack structure
struct Stack {
    int top;
    int capacity;
    int* array;
};

// Function to create a stack
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)
                                malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int item) {
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
    return stack->array[stack->top--];
}

int peek(struct Stack* stack) {
    return stack->array[stack->top];
}

// Function to calculate the maximum rectangular area
int getMaxArea(int arr[], int n) {
    struct Stack* s = createStack(n);
    int res = 0, tp, curr;
    
    // Traverse all bars of the histogram
    for (int i = 0; i < n; i++) {  
        
        // Process the stack while the current element 
        // is smaller than the element corresponding to 
        // the top of the stack
        while (!isEmpty(s) && arr[peek(s)] >= arr[i]) {
            tp = pop(s);
            
            // Calculate width and update result
            int width = isEmpty(s) ? i : i - peek(s) - 1;
            res = (res > arr[tp] * width) ? res : arr[tp] * width;
        }
        push(s, i);
    }

    // Process remaining elements in the stack
    while (!isEmpty(s)) {
        tp = pop(s);
        curr = arr[tp] * (isEmpty(s) ? n : n - peek(s) - 1);
        res = (res > curr) ? res : curr;
    }

    return res;
}

int main() {
    int arr[] = {60, 20, 50, 40, 10, 50, 60};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", getMaxArea(arr, n));
    return 0;
}
