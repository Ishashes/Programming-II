int main() {
    char expression[100];
    
    printf("Enter RPN expression: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0'; // Remove newline character
    
    double result = calculateRPN(expression);
    printf("Result: %lf\n", result);
    
    return 0;
}
