from collections import deque


class Solution:
    def nextGreaterElements(self, nums: list[int]) -> list[int]:
        """
        Finds the next greater element for every element in a circular array.

        INTUITION:
        -----------
        For each element, we want to find the first element to its right
        that is strictly greater than it.

        Because the array is circular, elements at the beginning of the
        array can also be considered as elements to the right of elements
        near the end.

        For example:

            nums = [1, 2, 3, 4, 3]

        When looking for the next greater element of the last 3, we continue
        from the beginning of the array and find 4.

        To simulate this circular behavior, we iterate through the array
        twice:

            range(len(nums) * 2)

        The actual index is obtained using:

            i = i % len(nums)

        This means that after reaching the end of the array, we start again
        from index 0.

        MONOTONIC STACK:
        ----------------
        The stack stores indices whose next greater element has not yet
        been found.

        More specifically, the values corresponding to the indices in the
        stack are maintained in decreasing order.

        When nums[i] is greater than nums[stack[-1]], nums[i] has just been
        discovered as the next greater element for stack[-1].

        Therefore:

            res[stack.pop()] = nums[i]

        We continue popping while the current value is greater than the
        values represented by indices in the stack.

        Any indices remaining in the stack after the complete two passes
        have no greater element anywhere in the circular array, so their
        result remains -1.

        WHY TWO PASSES ARE ENOUGH:
        --------------------------
        Every element only needs to look at most one complete additional
        traversal of the array to find its next greater element.

        Iterating 2 * n times therefore gives every element an opportunity
        to find a greater element that may occur before it in the original
        array.

        EXAMPLE:
        --------
            nums = [1, 2, 3, 4, 3]

        The result is:

            [2, 3, 4, -1, 4]

        The last 3 has no greater element after it in the original array,
        but because the array is circular, we continue from the beginning
        and encounter 4.

        TIME COMPLEXITY:
        ----------------
        O(n)

        Although the loop executes 2n times, each index is pushed onto the
        stack at most twice and popped at most once. Therefore, the total
        amount of stack work is linear.

        SPACE COMPLEXITY:
        -----------------
        O(n)

        The result array contains n elements, and the stack can contain up
        to n indices.
        """

        stack = deque()
        res = [-1] * len(nums)

        for i in range(len(nums) * 2):
            i = i % len(nums)

            if len(stack) == 0:
                stack.append(i)
                continue

            while len(stack) > 0 and nums[i] > nums[stack[-1]]:
                res[stack.pop()] = nums[i]
            stack.append(i)
        return res


print(Solution().nextGreaterElements([1, 2, 3, 4, 3]))
