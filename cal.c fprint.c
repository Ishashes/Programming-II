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
