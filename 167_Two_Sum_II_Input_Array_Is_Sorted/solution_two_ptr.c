#include <stdlib.h>
#include <stdio.h>

/**
 * Two Sum II - Input Array Is Sorted
 *
 * INTUITION
 * ---------
 * The array is sorted in non-decreasing order. This allows us to use
 * two pointers instead of searching for a complement for every element.
 *
 * We start with:
 *
 *     lPtr -> first (smallest) element
 *     rPtr -> last  (largest) element
 *
 * Example:
 *
 *     [2, 7, 11, 15]
 *      ^           ^
 *     lPtr        rPtr
 *
 * We calculate:
 *
 *     numbers[lPtr] + numbers[rPtr]
 *
 * There are three possible cases:
 *
 * 1. sum_tot < target
 *    -----------------
 *    The sum is too small, so we need a larger value.
 *
 *    Because the array is sorted, moving rPtr left would make the
 *    sum even smaller. Therefore, we move lPtr to the right:
 *
 *        lPtr++;
 *
 *    This eliminates the current smallest value from consideration.
 *
 *
 * 2. sum_tot > target
 *    -----------------
 *    The sum is too large, so we need a smaller value.
 *
 *    Because the array is sorted, moving lPtr right would make the
 *    sum even larger. Therefore, we move rPtr to the left:
 *
 *        rPtr--;
 *
 *    This eliminates the current largest value from consideration.
 *
 *
 * 3. sum_tot == target
 *    ------------------
 *    We have found the required pair, so we store their indices
 *    and stop searching.
 *
 *
 * WHY THIS IS O(n)
 * ----------------
 * Although the loop may examine many elements, neither pointer ever
 * moves backwards:
 *
 *     lPtr  -> -> -> ->
 *     rPtr  <- <- <- <-
 *
 * Each pointer can move across the array at most once. Therefore,
 * there are at most O(n) pointer movements in total.
 *
 * This gives:
 *
 *     Time Complexity:  O(n)
 *     Space Complexity: O(1) auxiliary space
 *
 *
 * WHY THE SORTED ARRAY MATTERS
 * ----------------------------
 * Without the sorted property, we could not safely eliminate a value
 * based on whether the current sum was too large or too small.
 *
 * For example:
 *
 *     sum = numbers[lPtr] + numbers[rPtr] > target
 *
 * Because rPtr points to the largest remaining value, we know that
 * this value cannot be part of a valid pair. Therefore rPtr can be
 * safely moved left.
 *
 * Similarly, if:
 *
 *     sum < target
 *
 * lPtr points to the smallest remaining value, so it cannot be part
 * of a valid pair and can be safely moved right.
 *
 *
 * RETURN VALUE
 * ------------
 * The problem requires 1-based indices rather than C's normal
 * 0-based array indices. Therefore:
 *
 *     lPtr + 1
 *     rPtr + 1
 *
 * are returned.
 *
 *
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int lPtr = 0, rPtr = numbersSize - 1, sum_tot = 0;

    int *ret_arr = calloc(2, sizeof(*ret_arr));
    *returnSize = 2;

    while(lPtr < rPtr)
    {
        sum_tot = numbers[lPtr] + numbers[rPtr];

        /*
         * The sum is too small.
         *
         * Since lPtr points to the smallest remaining value,
         * keeping it cannot produce a larger sum. Move lPtr
         * toward larger values.
         */
        if (sum_tot < target) lPtr++;

        /*
         * The sum is too large.
         *
         * Since rPtr points to the largest remaining value,
         * keeping it cannot produce a smaller sum. Move rPtr
         * toward smaller values.
         */
        if (sum_tot > target) rPtr--;
        
        /*
         * The exact target has been found.
         *
         * The problem expects 1-based indices, hence the +1.
         */
        if (sum_tot == target) {
            ret_arr[0] = lPtr + 1;
            ret_arr[1] = rPtr + 1;
            break;
        }
    }
    
    return ret_arr;
}

int main (void) {
    int ret = 0;
    int arr_ip[] = {-1,0};

    int *arr = twoSum(arr_ip, 2, -1, &ret);

    printf("[%d, %d]", arr[0], arr[1]);
}