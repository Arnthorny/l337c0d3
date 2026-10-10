#include <stdlib.h>
#include <string.h>

#define NUMS_LEN 100000

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    int lP = 0, rP = 0;
    int res_tmp[NUMS_LEN] = {0};
    int res_tmp_idx = 0;
    int *res = NULL;

    int cur_win_max_idx = 0;

    while (rP < numsSize)
    {
        if (rP - lP < k - 1) {
            cur_win_max_idx = nums[cur_win_max_idx] > nums[rP] ? cur_win_max_idx : rP;
            rP++; continue;
        }
        cur_win_max_idx = nums[cur_win_max_idx] > nums[rP] ? cur_win_max_idx : rP;
        res_tmp[res_tmp_idx++] = nums[cur_win_max_idx];

        if (lP == cur_win_max_idx)
        {
            cur_win_max_idx = lP + 1;
            rP = lP;
        }
        rP++;
        lP++;
    }

    res = calloc(res_tmp_idx, sizeof(*res));
    
    printf("%d\n",res_tmp[2]);


    memcpy(res, res_tmp, res_tmp_idx * sizeof(*res));
    *returnSize = res_tmp_idx;
    
    return res;
}


int main (void) {
    int nums[] = {1,3,-1,-3,5,3,6,7};
    int numsSize = 8;
    int k = 3;
    int returnSize = 0;

    printf("%d\n", maxSlidingWindow(nums, numsSize, k, &returnSize)[2]);
}