#include <stdlib.h>


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int i;
    long long total_product = 1, tmp = 0;
    char hasZero = 0;
    
    int *ret_arr = calloc(numsSize, sizeof(*ret_arr));
    *returnSize = numsSize;

    for (i = 0; i < numsSize; i++) {
        if (hasZero && nums[i] == 0) {
            total_product = 0;
            break;
        }
        if (nums[i] == 0) {
            hasZero = 1;
            continue;
        }

        total_product *= nums[i];

    }

    for (i = 0; i < numsSize; i++)
    {
        if (nums[i] == 0) {
            ret_arr[i] = (int)(total_product);
            continue;
        }
        if (hasZero) {
            ret_arr[i] = 0;
        }
        else {
            tmp = total_product / nums[i];
            ret_arr[i] = (int)(total_product / nums[i]);
        }

    }
    
    return ret_arr;
}