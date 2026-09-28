from typing import List

class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        res = []
        nums.sort()

        for (i, x) in enumerate(nums):

            if x > 0: break
            if i > 0 and x == nums[i - 1]: continue

            lP, rP = i + 1, len(nums) - 1


            while lP < rP:
                threeSums = x + nums[lP] + nums[rP]
                if threeSums > 0: rP -= 1
                if threeSums < 0: lP += 1


                if threeSums == 0:
                    res.append([x, nums[lP], nums[rP]])
                    lP += 1
                    rP -= 1

                    while nums[lP] == nums [lP - 1] and lP < rP:
                        lP += 1
        return res

print(Solution().threeSum([-1,0,1,2,-1,-4]))