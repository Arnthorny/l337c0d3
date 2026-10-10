#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SZ 30001

/**
 * MinStack
 *
 * Algorithm Kind:
 *     Stack + Auxiliary Stack
 *
 * Intuition:
 *
 * A normal stack can give us the top element in O(1), but finding
 * the minimum element would normally require scanning the entire
 * stack, which would take O(n).
 *
 * To avoid this, this implementation maintains two stacks:
 *
 *     s[]      -> stores the actual stack values
 *     s_min[]  -> stores the minimum value at every stack position
 *
 * The two stacks are kept synchronized by `s_idx` and `s_min_idx`.
 *
 * ---------------------------------------------------------------
 * Example:
 *
 * Push 5:
 *
 *     s:
 *     [5]
 *
 *     s_min:
 *     [5]
 *
 *     Minimum = 5
 *
 * Push 3:
 *
 *     s:
 *     [5, 3]
 *
 *     s_min:
 *     [5, 3]
 *
 *     Minimum = 3
 *
 * Push 7:
 *
 *     s:
 *     [5, 3, 7]
 *
 *     s_min:
 *     [5, 3, 3]
 *
 *     Minimum = 3
 *
 * Push 2:
 *
 *     s:
 *     [5, 3, 7, 2]
 *
 *     s_min:
 *     [5, 3, 3, 2]
 *
 *     Minimum = 2
 *
 * Notice that `s_min[i]` represents:
 *
 *     minimum value among s[0 ... i]
 *
 * Therefore, the current minimum is always:
 *
 *     s_min[s_min_idx]
 *
 * ---------------------------------------------------------------
 * minStackCreate:
 *
 * Allocates and initializes a MinStack.
 *
 * Both indices start at -1 because the stack is initially empty.
 *
 * ---------------------------------------------------------------
 * minStackPush:
 *
 * The value is first pushed onto the normal stack.
 *
 * The same position in `s_min` is then populated with the minimum
 * between:
 *
 *     1. The newly pushed value
 *     2. The previous minimum
 *
 * Therefore:
 *
 *     s_min[i] = min(value, s_min[i - 1])
 *
 * This means the minimum can always be retrieved in O(1).
 *
 * ---------------------------------------------------------------
 * minStackPop:
 *
 * Both stack indices are decremented.
 *
 * Because `s` and `s_min` correspond position-for-position, removing
 * the top value also removes the minimum information associated with
 * that position.
 *
 * ---------------------------------------------------------------
 * minStackTop:
 *
 * Returns the value at the top of the normal stack.
 *
 * ---------------------------------------------------------------
 * minStackGetMin:
 *
 * Returns the value at the top of the minimum stack.
 *
 * Because every position of `s_min` stores the minimum up to that
 * position, the top of `s_min` is always the minimum of the entire
 * current stack.
 *
 * ---------------------------------------------------------------
 * Time Complexity:
 *
 * minStackCreate:
 *     O(1)
 *
 * minStackPush:
 *     O(1)
 *
 * minStackPop:
 *     O(1)
 *
 * minStackTop:
 *     O(1)
 *
 * minStackGetMin:
 *     O(1)
 *
 * minStackFree:
 *     O(1)
 *
 * ---------------------------------------------------------------
 * Space Complexity:
 *
 * Two arrays of size MAX_STACK_SZ are maintained:
 *
 *     s[]      -> O(n)
 *     s_min[]  -> O(n)
 *
 * Therefore:
 *
 *     O(n)
 *
 * auxiliary space, where n is the maximum number of elements stored
 * in the stack.
 */
typedef struct {
    int s_idx;
    int s_min_idx;
    int s[MAX_STACK_SZ];
    int s_min[MAX_STACK_SZ];
} MinStack;


/**
 * Creates and initializes an empty MinStack.
 *
 * Both stack indices are initialized to -1 to represent an empty
 * stack.
 */
MinStack* minStackCreate() {
    MinStack *stck = NULL;

    stck = calloc(1, sizeof(*stck));
    stck->s_idx = -1;
    stck->s_min_idx = -1;

    return stck;
}


/**
 * Pushes a value onto the stack.
 *
 * The value is stored in the normal stack, while the auxiliary
 * minimum stack stores the minimum value seen up to this position.
 */
void minStackPush(MinStack* obj, int value) {
    obj->s_idx += 1;
    obj->s[obj->s_idx] = value;

    if (obj->s_min_idx == -1){
        obj->s_min_idx++;
        obj->s_min[obj->s_min_idx] = value;
    }
    else
    {
        obj->s_min_idx++;
        obj->s_min[obj->s_min_idx] = value < obj->s_min[(obj->s_min_idx) - 1] ? 
        value : obj->s_min[(obj->s_min_idx) - 1];
    }

}


/**
 * Removes the top element from the stack.
 *
 * Both the value stack and the minimum stack are moved back one
 * position because they correspond to the same logical stack depth.
 */
void minStackPop(MinStack* obj) {
    obj->s_idx--;
    obj->s_min_idx--;
}


/**
 * Returns the value currently at the top of the stack.
 */
int minStackTop(MinStack* obj) {
    return obj->s[obj->s_idx];
}


/**
 * Returns the minimum value currently contained in the stack.
 *
 * The top of the auxiliary minimum stack always contains the
 * minimum value of the entire current stack.
 */
int minStackGetMin(MinStack* obj) {
    return obj->s_min[obj->s_min_idx];
}


/**
 * Frees the memory allocated for the MinStack structure.
 */
void minStackFree(MinStack* obj) {
    free(obj);
}
