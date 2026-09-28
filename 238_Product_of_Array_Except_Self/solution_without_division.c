#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 100001

/**
 * Calculates the product of every element in nums except nums[i].
 *
 * Intuition:
 * For each index i, the result can be split into two independent parts:
 *
 *     result[i] = product of elements to the LEFT of i
 *               * product of elements to the RIGHT of i
 *
 * For example:
 *
 *     nums = [1, 2, 3, 4]
 *
 *     i = 2
 *
 *     left  = 1 * 2 = 2
 *     right = 4
 *
 *     result[2] = 2 * 4 = 8
 *
 * To efficiently obtain these products, we precompute:
 *
 * 1. pref_arr[i]:
 *      Product of nums[0] through nums[i].
 *
 * 2. suff_arr[i]:
 *      Product of nums[i] through nums[numsSize - 1].
 *
 * Then:
 *
 *     result[i] = pref_arr[i - 1] * suff_arr[i + 1]
 *
 * The first element has no elements to its left, so its result is
 * simply suff_arr[1]. Similarly, the last element has no elements
 * to its right, so its result is pref_arr[numsSize - 2].
 *
 * This approach also handles zeroes naturally because we never divide
 * by an element. For example, if nums contains one zero, the prefix
 * and suffix products still correctly produce zero for every position
 * except the zero's position.
 *
 * Complexity:
 *     Time:  O(n)
 *     Space: O(n)
 *
 * The returned array is dynamically allocated and must be freed by
 * the caller.
 *
 * Note: The prefix and suffix arrays use MAX_SIZE stack storage.
 * Therefore, this implementation is not strictly O(1) auxiliary space.
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int i, prev_val = 1, next_val = 1;

    *returnSize = numsSize;

    /*
     * pref_arr[i] contains the product of all elements from
     * nums[0] through nums[i].
     *
     * Example:
     *     nums      = [1, 2, 3, 4]
     *     pref_arr  = [1, 2, 6, 24]
     */
    int pref_arr[MAX_SIZE] = {1};

    /*
     * suff_arr[i] contains the product of all elements from
     * nums[i] through nums[numsSize - 1].
     *
     * Example:
     *     nums      = [1, 2, 3, 4]
     *     suff_arr  = [24, 24, 12, 4]
     */
    int suff_arr[MAX_SIZE] = {1};

    /*
     * Allocate the result dynamically because the caller is responsible
     * for freeing the returned array.
     */
    int *ret_arr = calloc(numsSize, sizeof(*ret_arr));

    /*
     * Build the prefix-product array.
     *
     * pref_arr[i] = pref_arr[i - 1] * nums[i]
     *
     * For i == 0, there is no previous element, so the previous
     * product is treated as 1.
     */
    for (i = 0; i < numsSize; i++) {
        prev_val = i == 0 ? 1 : pref_arr[i - 1];
        pref_arr[i] = prev_val * nums[i];
    }

    /*
     * Build the suffix-product array.
     *
     * suff_arr[i] = suff_arr[i + 1] * nums[i]
     *
     * For the last element, there is no element after it, so the
     * suffix product starts with 1.
     */
    for (i = numsSize - 1; i >= 0; i--) {
        next_val = i == numsSize - 1 ? 1 : suff_arr[i + 1];
        suff_arr[i] = next_val * nums[i];
    }

    /*
     * Combine the prefix and suffix products.
     *
     * Everything before i is represented by pref_arr[i - 1].
     * Everything after i is represented by suff_arr[i + 1].
     *
     * Therefore:
     *
     *     ret_arr[i] = pref_arr[i - 1] * suff_arr[i + 1]
     *
     * The first and last elements are special cases because they have
     * no prefix or suffix respectively.
     */
    for (i = 0; i < numsSize; i++) {

        if (i == 0) {
            // No elements exist to the left of index 0.
            ret_arr[i] = suff_arr[i + 1];
            continue;
        }

        if (i == numsSize - 1) {
            // No elements exist to the right of the last index.
            ret_arr[i] = pref_arr[i - 1];
            continue;
        }

        // Multiply everything before i by everything after i.
        ret_arr[i] = pref_arr[i - 1] * suff_arr[i + 1];
    }

    return ret_arr;
}

int main(void) {
    int nums[] = {-1, 1, 0, -3, 3};
    int *ret_arr = NULL;
    int numsSize = 5;
    int returnSize = 0;

    ret_arr = productExceptSelf(nums, numsSize, &returnSize);

    printf("[");
    for (int i = 0; i < returnSize; i++)
        printf("%d,", ret_arr[i]);
    printf("]\n");

    free(ret_arr);

    return 0;
}
