from collections import deque


class MinStack:
    def __init__(self):
        self._min = float("inf")
        self._stack = []
        self._min_st = deque()

    def push(self, val: int) -> None:
        self._stack.append(val)

        if len(self._min_st) == 0:
            self._min_st.append(val)

        else:
            self._min_st.append(min(self._min_st[-1], val))

    def pop(self) -> None:
        self._stack.pop()
        self._min_st.pop()

    def top(self) -> int:
        return self._stack[-1]

    def getMin(self) -> int:
        return self._min_st[-1]
