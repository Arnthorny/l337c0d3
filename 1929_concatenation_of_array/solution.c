/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getConcatenation(int* nums, int numsSize, int* returnSize) {
    int *ret_arr, i = 0;
    
    ret_arr = malloc(sizeof(int) * numsSize * 2);
    *returnSize = numsSize * 2;

    for (i = 0; i < numsSize * 2; i++) ret_arr[i] = nums[i % numsSize];
    
    return ret_arr;
}