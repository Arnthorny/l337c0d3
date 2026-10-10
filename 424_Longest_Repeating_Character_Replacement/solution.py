class Solution:
    def characterReplacement(self, s: str, k: int) -> int:
        uniq_ltrs = set(s)
        all_max = 0

        for ltr in uniq_ltrs:
            lP = 0
            rP = 0
            cur_max = 0
            tmp_k = k
            tmp_len = 0

            while rP < len(s):

                while (tmp_k < 0):
                    if s[lP] != ltr:
                        tmp_k += 1
                        lP += 1
                        break
                    lP += 1

                tmp_len = rP - lP + 1

                if (s[rP] != ltr): tmp_k -= 1
                if (tmp_k >= 0): cur_max = max(cur_max, tmp_len) 
                rP +=1
            
            all_max = max(all_max, cur_max)
        return all_max

print(Solution().characterReplacement("AABABBA", 1))