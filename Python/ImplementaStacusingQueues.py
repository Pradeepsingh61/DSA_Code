from collections import deque

class Stack:
    def __init__(self):
        self.queue1 = deque()
        self.queue2 = deque()

    def push(self, x: int):
        self.queue1.append(x)

    def pop(self) -> int:
        while len(self.queue1) > 1:
            self.queue2.append(self.queue1.popleft())
        popped = self.queue1.popleft()
        self.queue1, self.queue2 = self.queue2, self.queue1
        return popped

    def top(self) -> int:
        return self.queue1[-1]

    def empty(self) -> bool:
        return not self.queue1
