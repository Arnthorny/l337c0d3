from typing import List


class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        """
        Find the length of the longest consecutive sequence of integers.

        A consecutive sequence consists of numbers that increase by exactly 1.
        The numbers do not need to be adjacent in the original input.

        For example:
            nums = [100, 4, 200, 1, 3, 2]

        The longest consecutive sequence is:
            1 -> 2 -> 3 -> 4

        Therefore, the answer is 4.

        Approach:
        1. Put all numbers into a set for O(1) average-time lookups.
        2. Only start counting from a number if its predecessor
           (num - 1) does not exist in the set.
        3. From that starting number, keep incrementing while the next
           number exists in the set.
        4. Track the longest sequence found.

        Time Complexity:
            O(n) average

            Each number is visited at most a constant number of times.
            Although there is a while loop inside the for loop, the loop
            only starts for the beginning of a consecutive sequence.

        Space Complexity:
            O(n)

            The set stores all n input numbers.
        """

        # Store all numbers in a set so that membership checks are
        # O(1) on average.
        numsSet = set(nums)

        max_len = 0

        # Examine each unique number.
        for num in numsSet:

            # If num - 1 exists, then num is not the beginning
            # of a consecutive sequence. We skip it because the
            # sequence will be counted starting from its smallest number.
            if (num - 1) not in numsSet:

                curr_len = 0
                current = num

                # Count all consecutive numbers starting from num.
                while current in numsSet:
                    curr_len += 1
                    current += 1

                # Keep track of the longest sequence found so far.
                max_len = max(max_len, curr_len)

        return max_len
