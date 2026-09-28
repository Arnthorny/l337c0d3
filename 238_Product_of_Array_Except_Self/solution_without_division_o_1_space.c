#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 100001

/**
 * Calculates the product of every element in nums except nums[i].
 *
 * Intuition:
 * -------------
 * For every index i, the answer is:
 *
 *     product of everything to the LEFT of i
 *     *
 *     product of everything to the RIGHT of i
 *
 * Instead of maintaining separate prefix and suffix arrays, this
 * implementation stores the prefix products directly in ret_arr.
 *
 * Example:
 *
 *     nums = [1, 2, 3, 4]
 *
 * After the first pass:
 *
 *     ret_arr = [1, 2, 6, 24]
 *
 * Each position contains the product of nums[0..i].
 *
 * We then build a suffix-product array:
 *
 *     suff_arr = [24, 24, 12, 4]
 *
 * During the final pass, we combine:
 *
 *     prefix product before i
 *     *
 *     suffix product after i
 *
 * For example, at i = 2:
 *
 *     prefix = ret_arr[1] = 1 * 2 = 2
 *     suffix = suff_arr[3] = 4
 *
 *     result[2] = 2 * 4 = 8
 *
 * The key optimization is that we do not need a separate prefix array.
 * ret_arr initially serves as the prefix-product array and is then
 * overwritten with the final answers during the reverse pass.
 *
 * Zeroes are handled naturally because the algorithm never performs
 * division.
 *
 * Complexity:
 *     Time:  O(n)
 *     Space: O(n)
 *
 * The O(n) space comes from suff_arr. ret_arr is required for the
 * returned result and is therefore not considered auxiliary space.
 *
 * Note: The returned array is dynamically allocated and must be freed
 * by the caller.
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int i;
    int prev_val = 1;
    int next_val = 1;

    *returnSize = numsSize;

    /*
     * suff_arr[i] stores the product of all elements from i
     * through the end of the array.
     *
     * Example:
     *
     *     nums     = [1, 2, 3, 4]
     *     suff_arr = [24, 24, 12, 4]
     */
    int suff_arr[MAX_SIZE] = {1};

    /*
     * ret_arr initially stores PREFIX products.
     *
     * ret_arr[i] = nums[0] * nums[1] * ... * nums[i]
     *
     * Example:
     *
     *     nums     = [1, 2, 3, 4]
     *     ret_arr  = [1, 2, 6, 24]
     *
     * Later, these values will be overwritten with the final answers.
     */
    int *ret_arr = calloc(numsSize, sizeof(*ret_arr));

    /*
     * First pass: calculate prefix products.
     *
     * For index i, the previous prefix product is stored at
     * ret_arr[i - 1].
     *
     * There is no prefix before index 0, so its prefix multiplier
     * is treated as 1.
     */
    for (i = 0; i < numsSize; i++) {
        prev_val = i == 0 ? 1 : ret_arr[i - 1];
        ret_arr[i] = prev_val * nums[i];
    }

    /*
     * Second pass: calculate suffix products.
     *
     * For index i, the suffix product after it will eventually be
     * available at suff_arr[i + 1].
     *
     * The last element has no suffix, so its multiplier is 1.
     */
    for (i = numsSize - 1; i >= 0; i--) {
        next_val = i == numsSize - 1 ? 1 : suff_arr[i + 1];
        suff_arr[i] = next_val * nums[i];
    }

    /*
     * Third pass: construct the final answer.
     *
     * At this point:
     *
     *     ret_arr[i - 1]
     *
     * contains the product of everything before i.
     *
     * And:
     *
     *     suff_arr[i + 1]
     *
     * contains the product of everything after i.
     *
     * Therefore:
     *
     *     result[i] = prefix_before_i * suffix_after_i
     *
     * We iterate backwards so that ret_arr[i - 1] still contains
     * its prefix product before it is overwritten.
     */
    for (i = numsSize - 1; i >= 0; i--) {

        /*
         * Last element:
         *
         * There is nothing to its right, so the result is simply
         * the product of everything before it.
         */
        if (i == numsSize - 1) {
            ret_arr[i] = ret_arr[i - 1];
            continue;
        }

        /*
         * First element:
         *
         * There is nothing to its left, so the result is simply
         * the product of everything after it.
         */
        if (i == 0) {
            ret_arr[i] = suff_arr[i + 1];
            continue;
        }

        /*
         * General case:
         *
         *     everything before i
         *     *
         *     everything after i
         */
        ret_arr[i] = ret_arr[i - 1] * suff_arr[i + 1];
    }

    return ret_arr;
}
