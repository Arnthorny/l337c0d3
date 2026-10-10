from collections import deque


class Solution:
    def dailyTemperatures(self, temperatures: list[int]) -> list[int]:
        stck = deque()
        ans = [0] * len(temperatures)

        for i in range(len(temperatures) - 1, -1, -1):

            while(len(stck) > 0 and temperatures[i] >= temperatures[stck[-1]]): stck.pop()

            if (len(stck) == 0):
                ans[i] = 0
                stck.append(i)
                continue

            ans[i] = stck[-1] - i
            stck.append(i)

        return ans