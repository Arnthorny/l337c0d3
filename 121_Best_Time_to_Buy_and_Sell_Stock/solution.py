class Solution:
    def maxProfit(self, prices: list[int]) -> int:

        mini = prices[0]
        max_p = 0

        for p in prices:
            if mini < p:
                max_p = max(max_p, p - mini)
            else:
                mini = p
        return max_p

print(Solution().maxProfit([7,1,5,3,6,4]))