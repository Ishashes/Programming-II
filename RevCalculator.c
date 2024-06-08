#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXSTACK 100

typedef struct {
    double items[MAXSTACK];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == MAXSTACK - 1;
}

void push(Stack* s, double value) {
    if (isFull(s)) {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
    s->items[++(s->top)] = value;
}

double pop(Stack* s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    return s->items[(s->top)--];
}

double peek(Stack* s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    return s->items[s->top];
}

void processOperator(Stack* s, char operator) {
    double a, b, result;
    if (isEmpty(s)) {
        fprintf(stderr, "Error: not enough operands\n");
        exit(1);
    }
    b = pop(s);
    if (isEmpty(s)) {
        fprintf(stderr, "Error: not enough operands\n");
        exit(1);
    }
    a = pop(s);
    
    switch (operator) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': 
            if (b == 0) {
                fprintf(stderr, "Error: division by zero\n");
                exit(1);
            }
            result = a / b; break;
        default: 
            fprintf(stderr, "Unknown operator: %c\n", operator);
            exit(1);
    }
    
    push(s, result);
}

void processOperand(Stack* s, double operand) {
    push(s, operand);
}

double calculateRPN(const char* expression) {
    Stack s;
    initStack(&s);
    char token[100];
    int i = 0, j = 0;
    
    while (expression[i] != '\0') {
        if (isspace(expression[i])) {
            i++;
            continue;
        }
        
        if (isdigit(expression[i]) || (expression[i] == '-' && isdigit(expression[i+1]))) {
            // Read a number
            j = 0;
            while (isdigit(expression[i]) || expression[i] == '.' || (expression[i] == '-' && j == 0)) {
                token[j++] = expression[i++];
            }
            token[j] = '\0';
            processOperand(&s, atof(token));
        } else if (strchr("+-*/", expression[i]) != NULL) {
            // Read an operator
            processOperator(&s, expression[i]);
            i++;
        } else {
            fprintf(stderr, "Invalid token: %c\n", expression[i]);
            exit(1);
        }
    }
    
    if (s.top != 0) {
        fprintf(stderr, "Error: too many operands\n");
        exit(1);
    }
    
    return pop(&s);
}

int main() {
    char expression[100];
    
    printf("Enter RPN expression: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0'; // Remove newline character
    
    double result = calculateRPN(expression);
    printf("Result: %lf\n", result);
    
    return 0;
}


