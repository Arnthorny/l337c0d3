/**
 * Note: The returned array must be malloced, assume caller calls free().
 * 
 * Given an array arr, replace every element in that array with the greatest
 * element among the elements to its right, and replace the last element with -1.
 * After doing so, return the array.
 * 
 * Solution entails looping array from behind and keeping track of largest seen so far.
 * Array may be edited in-place.
 */
#define NULL (void *) 0

int* replaceElements(int* arr, int arrSize, int* returnSize) {
    int lst_idx = arrSize - 1, i = 0;
    int curr_lgst = arr[lst_idx], tmp = 0;
    
    *returnSize = arrSize;

    arr[lst_idx--] = -1;

    for (i = lst_idx; i >= 0; i--)
    {
        // Save current value before swapping for current largest value
        tmp = arr[i];
        arr[i] = curr_lgst;
        if (tmp > curr_lgst) curr_lgst = tmp;
    }
    

    return arr;
}