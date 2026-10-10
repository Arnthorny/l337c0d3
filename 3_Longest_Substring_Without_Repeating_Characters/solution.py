class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        lPtr, rPtr = 0, 0
        max_len, tmp_len = 0, 0
        uniq_window = set()

        while rPtr < len(s) and lPtr <= rPtr:
            while s[rPtr] in uniq_window:
                uniq_window.remove(s[lPtr])
                lPtr += 1

            tmp_len = rPtr - lPtr + 1

            uniq_window.add(s[rPtr])
            rPtr += 1

            max_len = max(max_len, tmp_len)
        return max_len


print(Solution().lengthOfLongestSubstring("zxyzxyz"))
