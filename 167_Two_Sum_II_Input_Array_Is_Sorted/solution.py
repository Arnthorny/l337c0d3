from typing import List

class Solution:
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        lPtr = 0
        rPtr = len(numbers) - 1
        sum_tot = 0

        while lPtr < rPtr:
            sum_tot = numbers[lPtr] + numbers [rPtr]

            if sum_tot > target: rPtr -= 1
            if sum_tot < target: lPtr += 1
            if sum_tot == target: return[lPtr + 1, rPtr + 1]

