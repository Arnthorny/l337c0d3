from collections import defaultdict


class Solution:
    def minWindow(self, s: str, t: str) -> str:
        t_dict = defaultdict(int)
        temp_dict = defaultdict(int)
        cur_min_arr = [0, 0, float("inf")]

        lP, rP = 0, 0

        found_idxs = []
        found_match = False

        if len(t) > len(s):
            return ""

        for c in t:
            t_dict[c] += 1

        # find all instances
        for idx in range(len(s)):
            if t_dict.get(s[idx], 0) > 0:
                found_idxs.append(idx)

        if len(found_idxs) == 0:
            return ""


        for idx in found_idxs:
            lP, rP = idx, idx
            temp_dict.clear()

            while rP < len(s):

                # If we find an extra letter, start from next idx
                if t_dict.get(s[rP], 0) != 0 and temp_dict[s[rP]] == t_dict[s[rP]]:
                    rP += 1
                    continue

                if t_dict.get(s[rP], 0) != 0:
                    temp_dict[s[rP]] += 1

                if temp_dict == t_dict:
                    found_match = True
                    if cur_min_arr[2] != min(cur_min_arr[2], rP - lP + 1):
                        cur_min_arr[0], cur_min_arr[1], cur_min_arr[2] = (
                            lP,
                            rP,
                            (rP - lP + 1),
                        )

                    if cur_min_arr[2] == len(t):
                        break

                rP += 1

        return s[cur_min_arr[0] : cur_min_arr[1] + 1] if found_match else ""


print(Solution().minWindow("OUZODYXAZV", "XYZ"))
