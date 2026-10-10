from collections import deque


class Solution:
    def isValid(self, s: str) -> bool:
        stck = deque()
        valid_par = {"(": ")", "{": "}", "[": "]"}
        tmp_c = ""

        for c in s:
            # It is an Open bracket
            if c in valid_par:
                stck.append(c)
            else:
                tmp_c = stck.pop() if len(stck) > 0 else ""
                if valid_par.get(tmp_c, "") != c:
                    return False

        return len(stck) == 0


print(Solution().isValid("[(])"))
