
#define MAX_TOKENS_LEN 10001
#include <stdio.h>

/**
 * Converts a numeric string into an integer.
 *
 * Intuition:
 * Processes the string from left to right, building the number
 * one digit at a time. If the string begins with '-', the sign
 * is set to -1 and the remaining characters are parsed as digits.
 *
 * For each digit:
 *   1. Multiply the current number by 10 to shift its digits left.
 *   2. Add the integer value of the current digit.
 *
 * Finally, apply the sign to the accumulated number.
 *
 * Time Complexity: O(m), where m is the length of the string.
 * Space Complexity: O(1), as only a fixed number of variables
 * are used.
 */
int strToint(char *str) {
    int i = 0, num = 0;
    int sign = 1;
    
    if (str[i] == '-') {
        sign = -1; i++;
    }

    while (str[i])
    {
        num *= 10;
        num += str[i] - '0';
        i++;
    }

    return sign * num;
}

/**
 * Evaluates an expression represented in Reverse Polish Notation.
 *
 * Intuition:
 * RPN places each operator after its operands. For example,
 * "4 5 +" represents 4 + 5.
 *
 * A stack is used to keep track of operands and intermediate results:
 *   1. If a token is a number, convert it to an integer and push it.
 *   2. If a token is an operator, pop the right operand first,
 *      then pop the left operand.
 *   3. Apply the operator to the two operands and push the result.
 *   4. After processing all tokens, the stack's top contains
 *      the final result.
 *
 * tmp_op_2 stores the right operand because it is popped first;
 * tmp_op_1 stores the left operand. This ordering is important
 * for subtraction and division.
 *
 * The fixed-size array t_stack serves as the stack, while
 * t_stack_idx tracks the index of its current top element.
 *
 * Time Complexity: O(n), where n is the number of tokens,
 * assuming each token has bounded length. Each token is processed
 * once, and each stack operation takes O(1) time.
 *
 * Space Complexity: O(n), for the stack that stores operands
 * and intermediate results.
 *
 * Assumes the input is a valid RPN expression and the stack
 * capacity is sufficient.
 */
int evalRPN(char** tokens, int tokensSize) {
 int t_stack[MAX_TOKENS_LEN] = {0};
 int t_stack_idx = -1, i = 0;
 int tmp_op_1 = 0, tmp_op_2 = 0;


 for (i = 0; i < tokensSize; i++) {
        if ((tokens[i][0] >= '0' && tokens[i][0] <= '9') || (tokens[i][0] == '-' && tokens[i][1] != '\0')) {
            t_stack[++t_stack_idx] = strToint(tokens[i]);
        }

        else
        {
            tmp_op_2 = t_stack[t_stack_idx--];
            tmp_op_1 = t_stack[t_stack_idx--];

            if(tokens[i][0] == '+') t_stack[++t_stack_idx] = tmp_op_1 + tmp_op_2;
            if(tokens[i][0] == '-') t_stack[++t_stack_idx] = tmp_op_1 - tmp_op_2;
            if(tokens[i][0] == '/') t_stack[++t_stack_idx] = tmp_op_1 / tmp_op_2;
            if(tokens[i][0] == '*') t_stack[++t_stack_idx] = tmp_op_1 * tmp_op_2;
        }
    }
 return t_stack[t_stack_idx];
}


int main(void) {
    char *tokens[] = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
    printf("%d\n", evalRPN(tokens, 13));
}