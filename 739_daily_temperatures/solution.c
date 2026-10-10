#include <stdlib.h>
#include <stdio.h>
#define MAX_PSEUDO_STACK_SZ 100001

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

/**
 * Finds the number of days until a warmer temperature for each day.
 *
 * Intuition:
 * Traverses the temperature array from right to left so that
 * temperatures for future days have already been considered.
 *
 * A stack stores indices of candidate future days. The stack is
 * maintained so that temperatures decrease from bottom to top.
 *
 * For each day i:
 *   1. Pop indices whose temperatures are less than or equal to
 *      temperatures[i]. These days cannot be the next warmer day
 *      for i because the current day is at least as warm and is
 *      closer to any earlier day being processed.
 *   2. If the stack is empty, no warmer future day exists, so
 *      ans[i] remains 0.
 *   3. Otherwise, the index at the top identifies the nearest
 *      future day with a warmer temperature. The difference
 *      between the indices gives the number of days to wait.
 *   4. Push the current index so it can be considered for
 *      earlier days.
 *
 * The stack stores indices rather than temperatures because
 * indices are needed to calculate the waiting period.
 *
 * Time Complexity: O(n), where n is temperaturesSize.
 * Each index is pushed onto the stack once and popped at most
 * once, so the total number of stack operations is O(n).
 *
 * Space Complexity: O(n), for the stack and returned answer array.
 */
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    int i = 0, *ans = NULL;
    int stck[MAX_PSEUDO_STACK_SZ] = {0}, st_idx = -1;
    *returnSize = temperaturesSize;

    ans = calloc(temperaturesSize, sizeof(*ans));

    for (i = temperaturesSize - 1; i >= 0; i--)
    {
        while (st_idx > -1 && temperatures[i] >= temperatures[stck[st_idx]]) st_idx--;

        if (st_idx == -1){
            ans[i] = 0;
            stck[++st_idx] = i;
            continue;
        }
        ans[i] = stck[st_idx] - i;
        stck[++st_idx] = i;
    }
    return ans;
}


int main(void) {
    int temperatures[] = {89,62,70,58,47,47,46,76,100,70};
    int *ret_arr = NULL;
    int temperaturesSize = 10;
    int returnSize = 0;

    ret_arr = dailyTemperatures(temperatures, temperaturesSize, &returnSize);

    printf("[");
    for (int i = 0; i < returnSize; i++)
        printf("%d,", ret_arr[i]);
    printf("]\n");

    free(ret_arr);

    return 0;
}