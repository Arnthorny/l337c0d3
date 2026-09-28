from typing import List


class Solution:
    def maxArea(self, heights: List[int]) -> int:
        lP, rP, max_area_val, tmp_area = 0, len(heights) - 1, 0, 0

        while lP < rP:
            tmp_area = min(heights[lP], heights[rP]) * (rP - lP)

            if heights[lP] <= heights[rP]:
                lP += 1
            else:
                rP -= 1

            max_area_val = max(max_area_val, tmp_area)

        return max_area_val
