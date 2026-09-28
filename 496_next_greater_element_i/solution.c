#include <stdio.h>
#include <stdlib.h>

#define HASH_ARR_SZ 10001


/**
 * @brief Finds the next greater element for each element in nums1.
 *
 * The function solves the "Next Greater Element I" problem.
 *
 * INTUITION:
 * ----------
 * nums1 is a subset of nums2. Instead of searching through nums2
 * separately for every element in nums1, we first solve the next-greater
 * problem for every element in nums2.
 *
 * A monotonically decreasing stack is used to efficiently find the next
 * greater element.
 *
 * The stack stores INDICES into nums2 rather than the values themselves.
 *
 * As we iterate through nums2:
 *
 *     nums2[i]
 *
 * is the current candidate for being the next greater element of the
 * elements currently waiting in the stack.
 *
 * If:
 *
 *     nums2[i] > nums2[stack[curr_stack_top]]
 *
 * then nums2[i] is the first greater element encountered for the element
 * at the top of the stack.
 *
 * Therefore, we remove that element from the stack and record:
 *
 *     hsh_arr[value] = nums2[i]
 *
 * We continue popping while the current value is greater than the values
 * represented by the stack.
 *
 * This maintains the stack as a monotonically decreasing sequence of
 * values.
 *
 * For example, given:
 *
 *     nums2 = [1, 3, 4, 2]
 *
 * When 3 is encountered:
 *
 *     3 > 1
 *
 * so 3 becomes the next greater element of 1.
 *
 * When 4 is encountered:
 *
 *     4 > 3
 *
 * so 4 becomes the next greater element of 3.
 *
 * 4 also resolves any smaller elements still waiting in the stack.
 *
 *
 * HANDLING ELEMENTS WITH NO GREATER ELEMENT:
 * -------------------------------------------
 * After nums2 has been completely processed, any elements remaining in
 * the stack never encountered a greater element.
 *
 * Their next greater element is therefore -1:
 *
 *     hsh_arr[nums2[stack[curr_stack_top--]]] = -1;
 *
 *
 * WHY THE HASH ARRAY?
 * -------------------
 * Once the next-greater element for every value in nums2 has been found,
 * we need to quickly retrieve the answer for each value in nums1.
 *
 * hsh_arr[value] stores the next greater element associated with that
 * value.
 *
 * Therefore, instead of searching nums2 again, we can directly perform:
 *
 *     hsh_arr[nums1[i]]
 *
 * for every element in nums1.
 *
 * This gives constant-time lookup, assuming the values in nums1/nums2
 * fall within the range supported by HASH_ARR_SZ.
 *
 *
 * EXAMPLE:
 * --------
 *
 *     nums1 = [4, 1, 2]
 *     nums2 = [1, 3, 4, 2]
 *
 * The next greater mappings produced from nums2 are:
 *
 *     1 -> 3
 *     3 -> 4
 *     4 -> -1
 *     2 -> -1
 *
 * Therefore:
 *
 *     nums1 = [4, 1, 2]
 *     result = [-1, 3, -1]
 *
 *
 * @param nums1 Array containing the values for which we need answers.
 * @param nums1Size Number of elements in nums1.
 * @param nums2 Array containing the complete set of values to search.
 * @param nums2Size Number of elements in nums2.
 * @param returnSize Pointer used to return the size of the allocated
 *                    result array.
 *
 * @return A dynamically allocated array containing the next greater
 *         element for every value in nums1. The caller is responsible
 *         for freeing the returned array.
 *
 * TIME COMPLEXITY:
 * ----------------
 * O(nums1Size + nums2Size)
 *
 * Every element in nums2 is pushed onto the stack once and popped at most
 * once. Therefore, processing nums2 takes O(nums2Size).
 *
 * After that, nums1 is traversed once to construct the result, taking
 * O(nums1Size).
 *
 * Overall:
 *
 *     O(nums1Size + nums2Size)
 *
 *
 * SPACE COMPLEXITY:
 * -----------------
 * O(HASH_ARR_SZ + nums2Size + nums1Size)
 *
 * The function uses:
 *
 *     - stack[HASH_ARR_SZ] for the monotonic stack
 *     - hsh_arr[HASH_ARR_SZ] for the value -> next-greater mapping
 *     - ret_arr[nums1Size] for the returned result
 *
 * Since HASH_ARR_SZ is a fixed constant (10001), the two fixed-size
 * arrays are technically O(1) with respect to the input size.
 *
 * Therefore, if HASH_ARR_SZ is treated as a fixed constant, the
 * asymptotic auxiliary space is O(nums1Size + nums2Size) due to the
 * result array and the stack usage.
 *
 *
 * NOTE:
 * -----
 * This implementation assumes that the values in nums1 and nums2 are
 * valid indices into hsh_arr, i.e. they fall within the range supported
 * by HASH_ARR_SZ.
 *
 * It also relies on the standard problem constraint that values are
 * unique in nums2. If arbitrary negative values or values >=
 * HASH_ARR_SZ were supplied, hsh_arr indexing would not be safe.
 */
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int stack[HASH_ARR_SZ] = {0}; // monotonically decreasing stack
    int hsh_arr[HASH_ARR_SZ] = {0};

    int curr_stack_top = -1, i = 0;
    int *ret_arr = NULL;

    for (i = 0; i < nums2Size; i++)
    {
        while (curr_stack_top >= 0 && nums2[i] > nums2[stack[curr_stack_top]])
        {
            hsh_arr[nums2[stack[curr_stack_top--]]] = nums2[i];
        }   

        stack[++curr_stack_top] = i;
    }
    
    while (curr_stack_top >= 0) hsh_arr[nums2[stack[curr_stack_top--]]] = -1;

    *returnSize = nums1Size;
    ret_arr = calloc(nums1Size, sizeof(*ret_arr));

    for (i = 0; i < nums1Size; i++) ret_arr[i] = hsh_arr[nums1[i]];

    return ret_arr;
}


int main(void) {
    int nums1[] = {1,3,5,2,4};
    int nums2[] = {5,4,3,2,1};

    int nums1Size = 5;
    int nums2Size = 5;
    
    int returnSize = 0;

    int *v_t = nextGreaterElement(nums1, nums1Size, nums2, nums2Size, &returnSize);

    printf("[");
    for (int i = 0; i < returnSize; i++) printf("%d,", v_t[i]);
    printf("]\n");
}