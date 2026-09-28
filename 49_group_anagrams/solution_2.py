from typing import List


class Solution:
    def letter_counter(self, val: str) -> List[int]:
        d_arr = {}
        for s in val:
            d_arr[s] = d_arr.get(s, 0) + 1

        return tuple(sorted(d_arr.items()))

    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        anag_dict = {}

        for str in strs:
            cnt_ltrs_arr = self.letter_counter(str)

            anag_dict[cnt_ltrs_arr] = anag_dict.get(cnt_ltrs_arr, [])
            anag_dict[cnt_ltrs_arr].append(str)

        return list(anag_dict.values())

    def run(self, strs: List[str]):
        print(self.groupAnagrams(strs))


sol = Solution().run(["eat", "tea", "tan", "ate", "nat", "bat"])
