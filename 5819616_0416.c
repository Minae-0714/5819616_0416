#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
    element* data;
    int capacity;
    int top;
} StackType;

void init(StackType* sptr, int capacity) {
    sptr->data = (element*)malloc(capacity * sizeof(element));
    if (!sptr->data) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    sptr->top = -1;
    sptr->capacity = capacity;
}

void ensure_capacity(StackType* sptr) {
    if (sptr->top >= sptr->capacity - 1) {
        sptr->capacity *= 2;
        sptr->data = (element*)realloc(sptr->data, sptr->capacity * sizeof(element));
        if (!sptr->data) {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(1);
        }
    }
}

int is_empty(StackType* sptr) {
    return sptr->top == -1;
}

void push(StackType* sptr, element item) {
    ensure_capacity(sptr);
    sptr->data[++sptr->top] = item;
}

element pop(StackType* sptr) {
    if (is_empty(sptr)) {
        fprintf(stderr, "Stack is empty\n");
        return -1; //error
    }
    return sptr->data[sptr->top--];
}

element peek(StackType* sptr) {
    if (is_empty(sptr)) {
        fprintf(stderr, "Stack is empty\n");
        return -1;
    }
    return sptr->data[sptr->top];
}

void stack_print(StackType* sptr) {
    for (int i = sptr->top; i >= 0; i--) {
        printf("[%d]", sptr->data[i]);
    }
    printf("\n");
}

int eval(char expr[]) {
    int len = strlen(expr);
    StackType s;
    init(&s, 20);

    for (int i = 0; i < len; i++) {
        char ch = expr[i];
        if (ch == ' ' || ch == '\n') continue; // Skip whitespace and newline

        if (ch >= '0' && ch <= '9') {
            push(&s, ch - '0');
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            int op1 = pop(&s);
            int op2 = pop(&s);
            switch (ch) {
            case '+': push(&s, op2 + op1); break;
            case '-': push(&s, op2 - op1); break;
            case '*': push(&s, op2 * op1); break;
            case '/': push(&s, op2 / op1); break;
            }
        }
        else {
            fprintf(stderr, "Abnormal character in expression\n");
            continue;
        }
        printf("Step [%d] '%c' => Stack: ", i, ch);
        stack_print(&s);
    }
    return pop(&s);
}

int main() {
    char expression[MAX_STACK_SIZE];
    printf("Postfix Expression: ");
    fgets(expression, sizeof(expression), stdin);

    int result = eval(expression);
    printf("Result: %d\n", result);

    return 0;
}
