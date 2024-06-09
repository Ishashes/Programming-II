double peek(Stack* s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    return s->items[s->top];
}

void processOperand(Stack* s, double operand) {
    push(s, operand);
}
