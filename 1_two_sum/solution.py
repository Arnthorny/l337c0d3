from typing import List
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        hash_tbl = {}

        for i in range(len(nums)):
            other_val = target - nums[i]
            res = hash_tbl.get(other_val, None)
            
            if (res != None):
                return[res, i]
            else:
                hash_tbl[nums[i]] = i
        return []

    
print(Solution().twoSum([3,3], 6))