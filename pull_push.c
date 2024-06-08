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