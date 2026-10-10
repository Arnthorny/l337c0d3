from collections import deque


class Solution:
    def evalRPN(self, tokens: list[str]) -> int:
        """
        Evaluates an arithmetic expression written in Reverse Polish
        Notation (RPN).

        Algorithm Kind:
            Stack-Based Expression Evaluation

        Intuition:
            In RPN, operators appear after their operands.

            For example:
                ["2", "1", "+", "3", "*"]

            represents:
                (2 + 1) * 3 = 9

            A stack allows us to process the expression from left to
            right without needing parentheses or operator precedence
            rules.

            1. If the token is a number, convert it to an integer and
               push it onto the stack.

            2. If the token is an operator, pop the two most recent
               operands:
                   - tmp_op_2 is the right operand.
                   - tmp_op_1 is the left operand.

            3. Apply the operator to tmp_op_1 and tmp_op_2, then push
               the result back onto the stack.

            4. After all tokens have been processed, the stack contains
               the final result, which is returned.

        Why operand order matters:
            For subtraction and division, the order of the popped
            operands is important.

            For example, with:
                ["10", "3", "-"]

            The first pop gives 3, and the second gives 10.
            The correct operation is 10 - 3 = 7, not 3 - 10.

        Division:
            The expression int(tmp_op_1 / tmp_op_2) truncates the
            result toward zero, as required by the usual RPN problem
            specification.

        Time Complexity:
            O(n), where n is the number of tokens. Each token is
            processed once, and each stack operation is O(1).

        Space Complexity:
            O(n) in the worst case, because the stack can hold a
            number of operands proportional to the number of tokens.
        """
        operators = set("+-/*")
        tmp_op_2 = 0
        tmp_op_1 = 0

        stck = deque()

        for t in tokens:
            if t not in operators:
                stck.append(int(t))
            else:
                tmp_op_2 = stck.pop()
                tmp_op_1 = stck.pop()

                if t == '+': stck.append(int(tmp_op_1 + tmp_op_2))
                if t == '-': stck.append(int(tmp_op_1 - tmp_op_2))
                if t == '/': stck.append(int(tmp_op_1 / tmp_op_2))
                if t == '*': stck.append(int(tmp_op_1 * tmp_op_2))
        
        return stck.pop()
