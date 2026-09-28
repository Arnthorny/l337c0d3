int findMaxConsecutiveOnes(int* nums, int numsSize) {
    int i = 0, curr_max_ones = 0;
    int curr_ones = 0;
    
    for (i = 0; i < numsSize; i++)
    {
        if (nums[i] == 1) curr_ones++;
        else {
            if(curr_ones > curr_max_ones) curr_max_ones = curr_ones;
            curr_ones = 0;
        }
    }
    return curr_max_ones > curr_ones ? curr_max_ones : curr_ones;
}