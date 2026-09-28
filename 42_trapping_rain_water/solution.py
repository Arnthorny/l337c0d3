from collections import deque


class Solution:
    def trap(self, height: list[int]) -> int:
        """
        Calculates the total amount of rainwater that can be trapped
        between the bars represented by `height`.

        INTUITION:
        ----------
        The key observation is that water can be calculated whenever we
        discover a right boundary that is tall enough to close a container
        formed with a previously encountered left boundary.

        A monotonic decreasing stack is used to keep track of indices whose
        right boundary has not yet been found.

        The stack contains indices such that their corresponding heights
        are maintained in decreasing order.

        For example, while processing:

            [4, 2, 0, 3, 2, 5]

        the stack represents bars that are still "waiting" for a suitable
        right boundary.

        When the current height `h` is greater than or equal to the height
        at the top of the stack, the top bar can potentially be used as
        the bottom of a trapped-water region.

        We remove that bar:

            top = stack.pop()

        After removing it, the new top of the stack represents the left
        boundary, while the current index `i` represents the right
        boundary.

        For example, when processing the `3` in:

            [4, 2, 0, 3, 2, 5]
             0  1  2  3  4  5

        the stack contains indices corresponding to:

            [4, 2, 0]

        The `0` is popped because `3 >= 0`.

        After popping `0`, the new stack top is the `2` at index 1.
        Therefore, the immediate boundaries for the `0` are:

                left boundary       right boundary
                     ↓                    ↓
                    [2] ... [0] ... [3]
                            ↑
                           top

        NOT the `4` and `3`.

        The horizontal distance between the boundaries is:

            distance = i - stack[-1] - 1

        In this case:

            distance = 3 - 1 - 1
                     = 1

        The water level is determined by the shorter boundary:

            min(h, height[stack[-1]])

        The height of the popped bar must then be subtracted because that
        space is already occupied by the bar itself:

            boundHeight =
                min(h, height[stack[-1]]) - height[top]

        For this example:

            boundHeight = min(3, 2) - 0
                        = 2

        Therefore:

            water = distance * boundHeight
                  = 1 * 2
                  = 2

        So 2 units of water are trapped above the `0`, between the `2`
        and `3`.

        WHY DO WE POP THE STACK?
        -------------------------
        Suppose the current bar is taller than or equal to the bar at the
        top of the stack.

        The current bar becomes the right boundary for the popped bar.

        After popping, the next element in the stack becomes the potential
        left boundary.

        This allows us to calculate the complete horizontal region between
        the left and right boundaries.

        The process continues while the current bar is tall enough to
        resolve the bars waiting on the stack.

        WHY IS THE STACK MONOTONICALLY DECREASING?
        -------------------------------------------
        A decreasing stack allows us to efficiently discover a left
        boundary whenever a sufficiently tall right boundary appears.

        Every index is pushed onto the stack once and popped at most once.
        This is what allows the algorithm to run in linear time.

        EXAMPLE:
        --------
        For:

            height = [4, 2, 0, 3, 2, 5]

        When `3` is encountered, the `0` is popped and the `2` at index 1
        becomes its left boundary.

        Therefore, 2 units of water are trapped between:

            2 ... 0 ... 3

        Later, when `5` is encountered, additional elements are popped.
        The `4` at index 0 can then become the left boundary for another
        water region.

        The total trapped water is:

            9

        TIME COMPLEXITY:
        ----------------
        O(n)

        Every element is pushed onto the stack exactly once and can be
        popped at most once.

        Therefore, although there is a nested `while` loop, the total
        number of stack operations across the entire function is O(n).

        SPACE COMPLEXITY:
        -----------------
        O(n)

        In the worst case, the stack can contain every index in `height`,
        for example when the heights are strictly decreasing.
        """

        print(height)
        stack = deque()
        total_water, curr_water = 0, 0

        for i, h in enumerate(height):
            curr_water = 0
            while len(stack) > 0 and h >= height[stack[-1]]:
                top = stack.pop()
                if len(stack) == 0:
                    break

                distance = i - stack[-1] - 1
                boundHeight = min(h, height[stack[-1]]) - height[top]

                curr_water = distance * (max(0, boundHeight))
                total_water += curr_water

                print(
                    curr_water, height[stack[-1]], h, distance, boundHeight, height[top]
                )
                print([height[j] for j in stack])

            stack.append(i)
        return total_water


print(Solution().trap([4, 2, 0, 3, 2, 5]))
