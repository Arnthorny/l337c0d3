#include <stdlib.h>
#include <stdio.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

 int bin_search(int val, int *numbers, int lPtr, int rPtr) {
    int midPtr = 0;

    while (lPtr <= rPtr)
    {
        midPtr = lPtr + (rPtr - lPtr) / 2;
        
        if (val > numbers[midPtr]) lPtr = midPtr + 1;
        if (val < numbers[midPtr]) rPtr = midPtr - 1;
        if (val == numbers[midPtr]) return midPtr;
    }
    return -1;
 }


int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int lPtr = 0, rPtr = 0, i = 0, midPtr = 0, other = 0, other_idx;

    int *ret_arr = calloc(2, sizeof(*ret_arr));

    for (i = 0; i < numbersSize; i++) {
        other = target - numbers[i];

        if (other >= numbers[i]) {
            lPtr = i + 1 < numbersSize ? i + 1 : numbersSize - 1;
            rPtr = numbersSize - 1;
        }
        if (other < numbers[i]) {
            lPtr = 0;
            rPtr = i - 1;
        }
        other_idx = bin_search(other, numbers, lPtr, rPtr);
        if (other_idx != -1){
            ret_arr[0] = i < other_idx ? i + 1 : other_idx + 1; // 1-based array
            ret_arr[1] = i < other_idx ? other_idx + 1 : i + 1;
            return ret_arr;
        }
    };
    
    *returnSize = 2;
    return ret_arr;
}

int main (void) {
    int ret = 0;
    int arr_ip[] = {-1,0};

    int *arr = twoSum(arr_ip, 2, -1, &ret);

    printf("[%d, %d]", arr[0], arr[1]);
}