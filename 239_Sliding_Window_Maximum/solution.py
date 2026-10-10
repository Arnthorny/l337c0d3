from collections import deque


class Solution:
    """
    * Finds the maximum value in every contiguous subarray of size k.
    *
    * Algorithm Kind:
    *     Sliding Window + Monotonic Deque
    *
    * Intuition:
    *
    * The goal is to find the maximum of every window without
    * scanning the entire window each time.
    *
    * A deque is maintained containing indices of elements that
    * could potentially become the maximum of the current or a
    * future window.
    *
    * The deque is kept monotonically decreasing according to the
    * values in nums:
    *
    *     nums[q[0]] >= nums[q[1]] >= nums[q[2]] ...
    *
    * Therefore, the index at the front of the deque (`q[0]`) always
    * represents the maximum value in the current window.
    *
    * ---------------------------------------------------------------
    * Maintaining the monotonic property:
    *
    * When nums[rP] enters the window, any indices at the back of
    * the deque whose values are smaller than nums[rP] can be removed.
    *
    * For example:
    *
    *     nums = [4, 2, 3]
    *
    * Before adding 3:
    *
    *     deque -> [4, 2]
    *
    * Since 3 is larger than 2, index 2 can never become the maximum
    * while 3 is still in the window, so 2 is removed:
    *
    *     deque -> [4, 3]
    *
    * The deque therefore contains only useful candidates.
    *
    * ---------------------------------------------------------------
    * Adding the current element:
    *
    * `rP` is the right boundary of the sliding window.
    *
    * Before adding its index to the deque, smaller elements at the
    * back are removed:
    *
    *     while nums[q[-1]] < nums[rP]:
    *         q.pop()
    *
    * Then the current index is added:
    *
    *     q.append(rP)
    *
    * ---------------------------------------------------------------
    * Getting the window maximum:
    *
    * Once the first window reaches size k, the maximum is simply:
    *
    *     nums[q[0]]
    *
    * because the deque is maintained in decreasing order.
    *
    * ---------------------------------------------------------------
    * Removing elements that leave the window:
    *
    * When the window moves forward, `lP` represents the index that
    * is leaving the window.
    *
    * If that index is currently at the front of the deque:
    *
    *     if lP == q[0]:
    *         q.popleft()
    *
    * it must be removed because it can no longer contribute to any
    * future window.
    *
    * If `lP` is not at the front, it does not need to be explicitly
    * removed here. It has either already been removed from the deque
    * or is not the maximum candidate at the front.
    *
    * ---------------------------------------------------------------
    * Why this is efficient:
    *
    * Each index enters the deque exactly once and leaves the deque
    * at most once.
    *
    * Although there are `while` loops, an element cannot be popped
    * repeatedly. Once an index is removed from the deque, it never
    * returns.
    *
    * Therefore, the total number of deque operations is O(n).
    *
    * ---------------------------------------------------------------
    * Time Complexity:
    *
    *     O(n)
    *
    * Each element is appended to the deque once and removed at most
    * once.
    *
    * ---------------------------------------------------------------
    * Space Complexity:
    *
    *     O(k)
    *
    * In the worst case, the deque can contain up to k indices.
    *
    * The result array itself contains n - k + 1 elements, so if
    * output space is included, the total space is O(n).
    *
    * ---------------------------------------------------------------
    * Key Pattern:
    *
    *     Sliding Window
    *           +
    *     Monotonic Deque
    *
    * The most important idea to remember is:
    *
    * "Remove elements from the back that can never beat the new
    *  element, and keep the largest candidate at the front."
    """

    def maxSlidingWindow(self, nums: list[int], k: int) -> list[int]:
        lP = 0
        rP = 0
        res = []

        # Monotonically decreasing queue
        q = deque()

        while rP < len(nums):
            # Ensure queue is monotonically decreasing
            while len(q) > 0 and nums[q[-1]] < nums[rP]:
                q.pop()

            q.append(rP)

            # Special case for first window
            if lP == 0 and (rP - lP) + 1 < k:
                rP += 1
                continue

            res.append(nums[q[0]])

            # If lP is at current max, pop it
            if lP == q[0]:
                q.popleft()

            lP += 1
            rP += 1
        return res


print(Solution().maxSlidingWindow([7, 2, 4], 2))
