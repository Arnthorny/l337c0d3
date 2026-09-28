
#include <stdbool.h>

/**
 * @brief Rotates an array one position to the right in place.
 *
 * Intuition:
 * The last element is saved because it will be moved to index 0.
 * Then, starting from the second-to-last element, every element is
 * shifted one position to the right. Finally, the saved last element
 * is placed at the beginning.
 *
 * Example:
 *     [1, 2, 3, 4] -> [4, 1, 2, 3]
 *
 * @param arr    Array to rotate.
 * @param arr_sz Number of elements in the array.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
void rotate_right_in_place(int *arr, int arr_sz) {
    int i = 0, tmp = arr[arr_sz - 1];

    for (i = arr_sz - 2; i >= 0; i--) arr[i + 1] = arr[i];
    arr[0] = tmp;
}


/**
 * @brief Checks whether an array is sorted in non-decreasing order.
 *
 * Intuition:
 * A non-decreasing array must satisfy arr[i] <= arr[i + 1] for every
 * adjacent pair. Therefore, we only need to look for one pair where
 * arr[i] > arr[i + 1]. If such a pair exists, the array is not sorted.
 *
 * @param arr    Array to check.
 * @param arr_sz Number of elements in the array.
 *
 * @return true if the array is sorted in non-decreasing order,
 *         false otherwise.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
bool is_sorted(int *arr, int arr_sz) {
    int i = 0;
    while (i < arr_sz - 1) {if (arr[i] > arr[i + 1]) return false; i++;}

    return true;
}


/**
 * @brief Determines whether an array is a sorted array rotated some number of times.
 *
 * Intuition:
 * A sorted-and-rotated array can be obtained by repeatedly moving the
 * last element to the front of an already sorted array.
 *
 * Instead of trying to determine the rotation point directly, this
 * function tries every possible right rotation:
 *
 *     1. Check whether the current array is sorted.
 *     2. If it is, return true.
 *     3. Otherwise, rotate the array one position to the right.
 *     4. Repeat for every possible rotation.
 *
 * There are numsSize possible states because rotating an array
 * numsSize times returns it to its original arrangement.
 *
 * Example:
 *     [3, 4, 5, 1, 2]
 *
 *     -> [2, 3, 4, 5, 1]
 *     -> [1, 2, 3, 4, 5]  <- sorted, so return true
 *
 * If none of the rotations is sorted, the array cannot be a sorted
 * array that has been rotated.
 *
 * @param nums     Array to check.
 * @param numsSize Number of elements in the array.
 *
 * @return true if nums is a rotation of a sorted array,
 *         false otherwise.
 *
 * Time complexity: O(n^2)
 * Space complexity: O(1)
 *
 * Why O(n^2):
 * In the worst case, we perform numsSize rotations.
 * Each rotation takes O(n), and each call to is_sorted() also takes O(n).
 * Therefore:
 *
 *     O(n) rotations * O(n) work per rotation = O(n^2)
 */
bool check(int* nums, int numsSize) {
    int i = 0;


    for (i = 0; i < numsSize; i++)
    {
        
    }

    for (i = 0; i < numsSize; i++)
    {
        if (is_sorted(nums, numsSize)) return true;
        rotate_right_in_place(nums, numsSize);
    }
    return false;
}
