#include <stdlib.h>
#include <stdio.h>

#define MAX_NUMS_LEN 100000

/**
 * Finds the maximum value in every contiguous subarray (sliding
 * window) of size `k`.
 *
 * Algorithm Kind:
 *     Sliding Window Maximum
 *     Block Decomposition / Prefix-Suffix Maximum
 *
 * Intuition:
 *
 * A window of size k can cross at most two blocks when the array
 * is divided into blocks of size k.
 *
 * For any window:
 *
 *     [ lP ---------------- rP ]
 *
 * the left part of the window lies in one block, while the right
 * part lies in another block.
 *
 * The maximum of the left part can be obtained from `rightMaxArr`
 * and the maximum of the right part can be obtained from
 * `leftMaxArr`.
 *
 * Therefore:
 *
 *     window_max = max(rightMaxArr[lP], leftMaxArr[rP])
 *
 * ---------------------------------------------------------------
 * leftMaxArr:
 *
 * `leftMaxArr[i]` stores the maximum value encountered while
 * scanning from the beginning of the current block up to index i.
 *
 * For example, with k = 3:
 *
 *     nums = [1, 3, 2,  5, 4, 6,  7, 2]
 *
 *     Blocks:
 *              [1, 3, 2] [5, 4, 6] [7, 2]
 *
 * Within each block, `leftMaxArr` gives the maximum from the
 * beginning of that block up to the current position.
 *
 * ---------------------------------------------------------------
 * rightMaxArr:
 *
 * `rightMaxArr[i]` stores the maximum value encountered while
 * scanning from the end of the current block backwards to index i.
 *
 * Thus, for a window:
 *
 *     left part  -> use rightMaxArr[lP]
 *     right part -> use leftMaxArr[rP]
 *
 * Taking the larger of these two values gives the maximum of the
 * entire window.
 *
 * ---------------------------------------------------------------
 * Why two arrays are enough:
 *
 * Consider a window that crosses a block boundary:
 *
 *          block 1       block 2
 *        |---------|----------------|
 *              [ lP -------- rP ]
 *
 * The portion from `lP` to the end of block 1 is represented by
 * `rightMaxArr[lP]`.
 *
 * The portion from the beginning of block 2 to `rP` is represented
 * by `leftMaxArr[rP]`.
 *
 * Therefore:
 *
 *     max(window) =
 *         max(rightMaxArr[lP], leftMaxArr[rP])
 *
 * This allows each window maximum to be obtained in O(1) time
 * after the preprocessing.
 *
 * ---------------------------------------------------------------
 * Time Complexity:
 *
 * Building `leftMaxArr`:
 *     O(n)
 *
 * Building `rightMaxArr`:
 *     O(n)
 *
 * Computing all window maximums:
 *     O(n)
 *
 * Total:
 *     O(n)
 *
 * where n is `numsSize`.
 *
 * ---------------------------------------------------------------
 * Space Complexity:
 *
 * `leftMaxArr`:
 *     O(n)
 *
 * `rightMaxArr`:
 *     O(n)
 *
 * `res_arr`:
 *     O(n - k + 1)
 *
 * Therefore the overall auxiliary/output space is:
 *
 *     O(n)
 *
 * ---------------------------------------------------------------
 * Note:
 *
 * The two precomputed arrays are used instead of a monotonic deque.
 * Another common O(n) solution to this problem is the monotonic
 * deque approach, which maintains candidate maximum elements while
 * the window moves.
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    int leftMaxArr[MAX_NUMS_LEN] = {0};
    int rightMaxArr[MAX_NUMS_LEN] = {0};

    int i = 0, cur_max, lP = 0, rP = k - 1;
    
    *returnSize = (numsSize - k )+ 1;
    int *res_arr = calloc(*returnSize, sizeof(*res_arr));


    // Populate leftMax
    cur_max = nums[0];
    for (i = 0; i < numsSize; i++)
    {
        if(i!= 0 && i % k == 0) cur_max = nums[i];
        
        cur_max = cur_max > nums[i] ? cur_max : nums[i]; 
        leftMaxArr[i] = cur_max;

    }


    cur_max = nums[numsSize - 1];
    for (i = numsSize - 1; i >= 0; i--)
    {
        if(i % k == 0) cur_max = nums[i];
        
        cur_max = cur_max > nums[i] ? cur_max : nums[i]; 
        rightMaxArr[i] = cur_max;
    }
    
    i = 0;
    while (rP < numsSize)
    {
        res_arr[i++] = leftMaxArr[rP] > rightMaxArr[lP] ? leftMaxArr[rP] : rightMaxArr[lP];
        lP ++; rP++;
    }
    return res_arr;
}

int main (void) {
    int nums[] = {2,4,7};
    int numsSize = 3;
    int k = 2;
    int returnSize = 0;

    int *res_arr = maxSlidingWindow(nums, numsSize, k, &returnSize);

    printf("[");
    for (int i = 0; i < returnSize; i++)
        printf("%d,", res_arr[i]);
    printf("]\n");
}