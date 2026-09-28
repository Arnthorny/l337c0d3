class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        """
        Return the k most frequent elements in nums.

        Approach:
        1. Use a dictionary to count how many times each number occurs.
        2. Sort the unique numbers by their frequency, highest first.
        3. Return the first k numbers.

        Example:
            nums = [1, 1, 1, 2, 2, 3]

            freq = {
                1: 3,
                2: 2,
                3: 1
            }

            Sorted by frequency:
                [1, 2, 3]

            Return first k=2:
                [1, 2]

        Complexity:
            Let n = len(nums)
            and u = number of unique elements.

            Building the dictionary: O(n)
            Sorting u unique elements: O(u log u)

            Since u <= n:
                O(n + u log u)
                = O(n log n) worst case

            Space: O(u), which is O(n) in the worst case.
        """

        # number -> frequency
        freq = {}

        for num in nums:
            freq[num] = freq.get(num, 0) + 1

        # Sort the numbers by their frequency, highest first.
        sorted_nums = sorted(
            freq,
            key=lambda num: freq[num],
            reverse=True
        )

        return sorted_nums[:k]
