from typing import List


class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        num_len = len(nums)

        ret_arr = [1] * num_len
        suf_arr = [1] * num_len

        # populate prefix array:
        for i in range(num_len):
            ret_arr[i] = 1 * nums[i] if i == 0 else ret_arr[i - 1] * nums[i]

        # populate suffix array:
        for i in range(num_len - 1, -1, -1):
            suf_arr[i] = 1 * nums[i] if i == num_len - 1 else suf_arr[i + 1] * nums[i]

        
        for i in range(num_len - 1, -1, -1):
            if i == 0:
                ret_arr[i] = suf_arr[i + 1]
            elif i == num_len - 1:
                ret_arr[i] = ret_arr[i - 1]
            else:
                ret_arr[i] = ret_arr[i - 1] * suf_arr[i + 1]

        return ret_arr


sol = print(Solution().productExceptSelf([1, 2, 3, 4]))
