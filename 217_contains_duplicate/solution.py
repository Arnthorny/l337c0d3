class Solution:
    def containsDuplicate(self, nums: List[int]) -> bool:
        hash = {}

        for num in nums:
            if(hash.get(num, None)): return True
            hash[num] = True
        return False
