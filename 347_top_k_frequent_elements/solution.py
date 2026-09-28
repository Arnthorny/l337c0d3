class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        """
        Return the k most frequent elements in `nums`.

        Approach
        --------
        Use a direct-address frequency array instead of a dictionary/hash table.

        The problem constrains each number to a small, known range:
            -1000 <= nums[i] <= 1000

        We therefore map each possible number to a unique array index by
        adding MAX_VAL:

            number -> index
            -1000  -> 0
            -999   -> 1
            ...
             0     -> 1000
             ...
             1000  -> 2000

        This gives us exactly 2001 possible indices.

        `freq_arr[i]` stores how many times the number
        `(i - MAX_VAL)` occurs.

        Example:
            nums = [1, 1, 1, 2, 2, 3]

            freq_arr[1001] = 3   # number 1
            freq_arr[1002] = 2   # number 2
            freq_arr[1003] = 1   # number 3

        We then sort the indices by their corresponding frequency, from
        highest to lowest. Finally, convert those indices back into the
        original numbers by subtracting MAX_VAL.

        Why the offset is necessary
        ----------------------------
        Array indices cannot be negative, but `nums` can contain negative
        numbers.

        Adding MAX_VAL shifts the entire range into non-negative indices:

            -MAX_VAL + MAX_VAL = 0
             0       + MAX_VAL = MAX_VAL
             MAX_VAL + MAX_VAL = 2 * MAX_VAL

        Therefore the frequency array needs:

            (2 * MAX_VAL) + 1

        slots, because both endpoints are inclusive.

        Complexity
        ----------
        Let:
            n = len(nums)
            R = size of the possible value range (2001 here)

        Building the frequency array:
            O(n)

        Sorting all possible values:
            O(R log R)

        Since R is fixed at 2001 by the problem constraints, this is
        effectively O(n) with respect to the input size.

        Space:
            O(R) for the frequency array and index list.

        Notes
        -----
        This deliberately exploits the constrained value range. A more
        general solution would use a hash table/dictionary, since a direct
        frequency array would become impractical if the possible integer
        range were very large.
        """

        MAX_VAL = 1000
        MAX_SIZE_FREQ_ARR = (MAX_VAL * 2) + 1

        freq_arr = [0] * MAX_SIZE_FREQ_ARR

        # Count the frequency of every number.
        # Adding MAX_VAL converts the number into a valid array index.
        for num in nums:
            freq_arr[num + MAX_VAL] += 1

        # Sort indices according to their frequency, highest first.
        # The indices are then converted back to their original values.
        return [
            i - MAX_VAL
            for i in sorted(
                range(MAX_SIZE_FREQ_ARR), key=lambda i: freq_arr[i], reverse=True
            )[:k]
        ]
