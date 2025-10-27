# Python/data_structures/queue/queue_using_stacks.py

"""
Data Structure Description:
This implements a Queue (FIFO - First-In, First-Out) using two Stacks
(LIFO - Last-In, First-Out). One stack (`_in_stack`) is used for enqueue
operations, and the other (`_out_stack`) is used for dequeue and peek
operations. Elements are moved from `_in_stack` to `_out_stack` only when
`_out_stack` is empty, ensuring the FIFO order is maintained efficiently
on average (amortized O(1) for dequeue).
"""

# Time Complexity:
#   - Enqueue: O(1) - Simply push onto the in_stack.
#   - Dequeue: O(1) amortized. In the worst case (when out_stack is empty
#     and in_stack has n elements), it takes O(n) to transfer elements.
#     However, each element is moved only once, so over n operations, the
#     average cost is O(1).
#   - Peek: O(1) amortized - Same reasoning as dequeue.
#   - is_empty: O(1)
#   - size: O(1)
# Space Complexity: O(n)
#   - Where n is the number of elements stored across both stacks.

class QueueUsingStacks:
    """Implements a FIFO queue using two LIFO stacks."""

    def __init__(self):
        """Initializes the two stacks."""
        self._in_stack = []  # Used for enqueue
        self._out_stack = [] # Used for dequeue/peek

    def enqueue(self, item):
        """Adds an item to the rear of the queue.
        >>> q = QueueUsingStacks()
        >>> q.enqueue(1)
        >>> q.enqueue(2)
        >>> print(q._in_stack)
        [1, 2]
        """
        self._in_stack.append(item)

    def _transfer_elements(self):
        """Transfers elements from in_stack to out_stack if out_stack is empty."""
        if not self._out_stack:
            while self._in_stack:
                self._out_stack.append(self._in_stack.pop())

    def dequeue(self):
        """Removes and returns the item from the front of the queue.
        Raises IndexError if the queue is empty.
        >>> q = QueueUsingStacks()
        >>> q.enqueue(1)
        >>> q.enqueue(2)
        >>> q.dequeue() # Transfers 1, 2 to out_stack [2, 1], pops 1
        1
        >>> q.enqueue(3)
        >>> q.dequeue() # Pops 2 from out_stack
        2
        >>> q.dequeue() # Transfers 3 to out_stack [3], pops 3
        3
        >>> q.dequeue()
        Traceback (most recent call last):
        ...
        IndexError: dequeue from empty queue
        """
        self._transfer_elements()
        if not self._out_stack:
            raise IndexError("dequeue from empty queue")
        return self._out_stack.pop()

    def peek(self):
        """Returns the item at the front of the queue without removing it.
        Raises IndexError if the queue is empty.
        >>> q = QueueUsingStacks()
        >>> q.enqueue(1)
        >>> q.enqueue(2)
        >>> q.peek() # Transfers 1, 2 to out_stack [2, 1], returns 1
        1
        >>> q.dequeue()
        1
        >>> q.peek() # Returns 2 from out_stack
        2
        >>> q.dequeue()
        2
        >>> q.peek()
        Traceback (most recent call last):
        ...
        IndexError: peek from empty queue
        """
        self._transfer_elements()
        if not self._out_stack:
            raise IndexError("peek from empty queue")
        return self._out_stack[-1] # Peek at the top of out_stack

    def is_empty(self):
        """Returns True if the queue is empty, False otherwise.
        >>> q = QueueUsingStacks()
        >>> q.is_empty()
        True
        >>> q.enqueue(1)
        >>> q.is_empty()
        False
        """
        return not self._in_stack and not self._out_stack

    def size(self):
        """Returns the total number of items in the queue.
        >>> q = QueueUsingStacks()
        >>> q.size()
        0
        >>> q.enqueue(1)
        >>> q.enqueue(2)
        >>> q.size()
        2
        >>> q.dequeue()
        1
        >>> q.size()
        1
        """
        return len(self._in_stack) + len(self._out_stack)

    def __len__(self):
        """Allows using len(q)."""
        return self.size()

    def __str__(self):
        """String representation showing logical FIFO order (may be slow)."""
        # Note: This is inefficient for visualization but shows the logical order
        elements = list(reversed(self._out_stack)) + list(self._in_stack)
        return f"QueueUsingStacks({elements})"

    def __repr__(self):
        """Representation showing internal stack states."""
        return f"QueueUsingStacks(in={self._in_stack}, out={self._out_stack})"

if __name__ == "__main__":
    import doctest
    doctest.testmod()

    q = QueueUsingStacks()
    print("Is empty?", q.is_empty())
    q.enqueue('A')
    q.enqueue('B')
    print(q)
    print("Peek:", q.peek())
    print("Dequeue:", q.dequeue())
    print(q)
    q.enqueue('C')
    print(q)
    print("Size:", len(q))
    print("Dequeue:", q.dequeue())
    print("Dequeue:", q.dequeue())
    print("Is empty?", q.is_empty())
    # print("Dequeue:", q.dequeue()) # Raises IndexError