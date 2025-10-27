# Python/data_structures/stack/stack_with_min.py

"""
Data Structure Description:
This implements a Stack (LIFO - Last-In, First-Out) with an additional
operation `get_min()` that returns the minimum element currently in the stack
in O(1) time complexity.

This is achieved by using an auxiliary stack (`_min_stack`) that stores
the minimum value seen *so far* at each level of the main stack (`_main_stack`).
When pushing an element, if it's less than or equal to the current minimum
(the top of `_min_stack`), it's pushed onto `_min_stack` as well.
When popping, if the element being popped is the current minimum (top of
`_min_stack`), it's also popped from `_min_stack`.
"""

# Time Complexity:
#   - Push (append): O(1)
#   - Pop: O(1)
#   - Top (peek): O(1)
#   - GetMin: O(1)
#   - is_empty: O(1)
#   - size: O(1)
# Space Complexity: O(n)
#   - In the worst case (e.g., pushing decreasing numbers), the _min_stack
#     can store as many elements as the _main_stack.

class StackWithMin:
    """Implements a stack supporting O(1) get_min operation."""

    def __init__(self):
        """Initializes the main stack and the auxiliary min stack."""
        self._main_stack = []
        self._min_stack = []

    def push(self, item):
        """Pushes an item onto the stack.
        >>> s = StackWithMin()
        >>> s.push(5)
        >>> s.push(2)
        >>> s.push(3)
        >>> s.push(1)
        >>> print(s._main_stack)
        [5, 2, 3, 1]
        >>> print(s._min_stack) # Stores min seen at each stage
        [5, 2, 1]
        """
        self._main_stack.append(item)
        # Push to min_stack if it's empty or item is <= current min
        if not self._min_stack or item <= self._min_stack[-1]:
            self._min_stack.append(item)

    def pop(self):
        """Removes and returns the top item from the stack.
        Raises IndexError if the stack is empty.
        >>> s = StackWithMin()
        >>> s.push(5)
        >>> s.push(2)
        >>> s.push(1)
        >>> s.pop() # Removes 1 from both
        1
        >>> print(s._main_stack)
        [5, 2]
        >>> print(s._min_stack)
        [5, 2]
        >>> s.pop() # Removes 2 from both
        2
        >>> s.push(3)
        >>> s.pop() # Removes 3 from main, not min
        3
        >>> print(s._min_stack)
        [5]
        >>> s.pop() # Removes 5 from both
        5
        >>> s.pop()
        Traceback (most recent call last):
        ...
        IndexError: pop from empty stack
        """
        if not self._main_stack:
            raise IndexError("pop from empty stack")

        item_to_pop = self._main_stack.pop()
        # If the popped item is the current minimum, pop from min_stack too
        if item_to_pop == self._min_stack[-1]:
            self._min_stack.pop()
        return item_to_pop

    def top(self):
        """Returns the top item of the stack without removing it.
        Raises IndexError if the stack is empty.
        >>> s = StackWithMin()
        >>> s.push(5)
        >>> s.push(2)
        >>> s.top()
        2
        >>> s.pop()
        2
        >>> s.top()
        5
        >>> s.pop()
        5
        >>> s.top()
        Traceback (most recent call last):
        ...
        IndexError: top from empty stack
        """
        if not self._main_stack:
            raise IndexError("top from empty stack")
        return self._main_stack[-1]

    def get_min(self):
        """Returns the minimum item currently in the stack in O(1).
        Raises IndexError if the stack is empty.
        >>> s = StackWithMin()
        >>> s.push(5)
        >>> s.get_min()
        5
        >>> s.push(2)
        >>> s.get_min()
        2
        >>> s.push(3)
        >>> s.get_min()
        2
        >>> s.push(1)
        >>> s.get_min()
        1
        >>> s.pop()
        1
        >>> s.get_min()
        2
        >>> s.pop()
        3
        >>> s.get_min()
        2
        >>> s.pop()
        2
        >>> s.get_min()
        5
        >>> s.pop()
        5
        >>> s.get_min()
        Traceback (most recent call last):
        ...
        IndexError: get_min from empty stack
        """
        if not self._min_stack:
            raise IndexError("get_min from empty stack")
        return self._min_stack[-1]

    def is_empty(self):
        """Returns True if the stack is empty, False otherwise.
        >>> s = StackWithMin()
        >>> s.is_empty()
        True
        >>> s.push(1)
        >>> s.is_empty()
        False
        """
        return len(self._main_stack) == 0

    def size(self):
        """Returns the number of items in the stack.
        >>> s = StackWithMin()
        >>> s.size()
        0
        >>> s.push(1)
        >>> s.push(2)
        >>> s.size()
        2
        """
        return len(self._main_stack)

    def __len__(self):
        """Allows using len(s)."""
        return self.size()

    def __str__(self):
        """String representation of the main stack."""
        return f"StackWithMin({self._main_stack})"

    def __repr__(self):
        """Representation showing internal state."""
        return f"StackWithMin(main={self._main_stack}, min={self._min_stack})"


if __name__ == "__main__":
    import doctest
    doctest.testmod()

    s = StackWithMin()
    print("Is empty?", s.is_empty())
    s.push(10)
    s.push(5)
    s.push(15)
    s.push(3) # New min
    print(s)
    print("Size:", len(s))
    print("Top:", s.top())
    print("Current Min:", s.get_min())
    print("Pop:", s.pop()) # Removes 3
    print(s)
    print("Current Min:", s.get_min()) # Should be 5
    print("Pop:", s.pop()) # Removes 15
    print("Current Min:", s.get_min()) # Still 5
    print("Pop:", s.pop()) # Removes 5
    print("Current Min:", s.get_min()) # Should be 10
    print("Is empty?", s.is_empty())
    print("Pop:", s.pop()) # Removes 10
    print("Is empty?", s.is_empty())
    # print("Pop:", s.pop()) # Raises IndexError
    # print("Get Min:", s.get_min()) # Raises IndexError