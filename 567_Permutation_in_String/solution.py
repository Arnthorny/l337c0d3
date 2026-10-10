from collections import defaultdict
class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        if len(s1) > len(s2): return False

        s1_dict_counter = defaultdict(int)
        tmp_s2_dict_counter = defaultdict(int)
        for s in s1:
            s1_dict_counter[s] += 1

        lP, rP = 0, 0

        while rP < len(s2):
            if lP == 0 and rP < len(s1) - 1:
                 tmp_s2_dict_counter[s2[rP]] += 1
                 rP += 1
                 continue
                
            tmp_s2_dict_counter[s2[rP]] += 1

            if tmp_s2_dict_counter == s1_dict_counter: return True
            
            tmp_s2_dict_counter[s2[lP]] -= 1
            if (tmp_s2_dict_counter[s2[lP]] == 0): tmp_s2_dict_counter.pop(s2[lP])
            
            lP += 1
            rP += 1
        return False

print(Solution().checkInclusion("horse", "ros"))