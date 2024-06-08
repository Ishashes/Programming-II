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
