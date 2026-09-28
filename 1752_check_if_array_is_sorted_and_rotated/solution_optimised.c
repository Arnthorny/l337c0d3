
#include <stdbool.h>

/**
 * @brief Determines whether an array is a sorted array rotated some number of times.
 *
 * Intuition:
 * A sorted-and-rotated array can be obtained by repeatedly moving the
 * last element to the front of an already sorted array.
 *
 * In this variant, we inspect the original array by checking for
 * rotation points. If there's at most one point where the ascending order breaks,
 * then the array is sorted-rotated. We also perform circular comparison 
 * (last element checked against first)
 * 
 * @param nums     Array to check.
 * @param numsSize Number of elements in the array.
 *
 * @return true if nums is a rotation of a sorted array,
 *         false otherwise.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * Why O(n):
 * This approach only needs a single pass at the array
 */
bool check(int* nums, int numsSize) {
    int i = 0, count = 0;


    for (i = 0; i < numsSize; i++)
    {
        if (nums[i] > nums[(i + 1) % numsSize]) count++;
        if (count >= 2) return false;
    }

    return count <= 1 ? true : false;
}
