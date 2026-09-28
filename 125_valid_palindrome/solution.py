class Solution:
    def isPalindrome(self, s: str) -> bool:
        lP = 0
        len_s = len(s)
        rP = len_s - 1

        while lP < rP:
            if not s[rP].isalnum():
                rP -= 1
                continue
            if not s[lP].isalnum():
                lP += 1
                continue

            # print(s[lP], s[rP], sep=",")
            if s[lP].lower() != s[rP].lower():
                return False

            lP += 1
            rP -= 1

        return True


print(Solution().isPalindrome("tab a cat"))
