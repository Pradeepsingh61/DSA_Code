# Python/data_structures/queue/array_queue.py

"""
Data Structure Description:
A Queue is a linear data structure that follows the First-In, First-Out (FIFO)
principle. Elements are added (enqueued) at the rear and removed (dequeued)
from the front. This implementation uses a standard Python list as the
underlying storage. While simple, dequeuing from the beginning of a Python
list can be inefficient (O(n)) as elements need to be shifted.
"""

# Time Complexity:
#   - Enqueue (append): O(1) on average
#   - Dequeue (pop(0)): O(n) because all subsequent elements must be shifted
#   - Peek: O(1)
#   - is_empty: O(1)
#   - size: O(1)
# Space Complexity: O(n)
#   - Where n is the number of elements stored in the queue.

class ArrayQueue:
    """Implements a queue using a Python list."""

    def __init__(self):
        """Initializes an empty queue."""
        self._items = []

    def enqueue(self, item):
        """Adds an item to the rear of the queue.
        >>> q = ArrayQueue()
        >>> q.enqueue(1)
        >>> q.enqueue(2)
        >>> print(q._items)
        [1, 2]
        """
        self._items.append(item)

    def dequeue(self):
        """Removes and returns the item from the front of the queue.
        Raises IndexError if the queue is empty.
        >>> q = ArrayQueue()
        >>> q.enqueue(1)
        >>> q.enqueue(2)
        >>> q.dequeue()
        1
        >>> q.dequeue()
        2
        >>> q.dequeue()
        Traceback (most recent call last):
        ...
        IndexError: dequeue from empty queue
        """
        if not self._items:
            raise IndexError("dequeue from empty queue")
        return self._items.pop(0) # Inefficient part

    def peek(self):
        """Returns the item at the front of the queue without removing it.
        Raises IndexError if the queue is empty.
        >>> q = ArrayQueue()
        >>> q.enqueue(1)
        >>> q.enqueue(2)
        >>> q.peek()
        1
        >>> q.dequeue()
        1
        >>> q.peek()
        2
        >>> q.dequeue()
        2
        >>> q.peek()
        Traceback (most recent call last):
        ...
        IndexError: peek from empty queue
        """
        if not self._items:
            raise IndexError("peek from empty queue")
        return self._items[0]

    def is_empty(self):
        """Returns True if the queue is empty, False otherwise.
        >>> q = ArrayQueue()
        >>> q.is_empty()
        True
        >>> q.enqueue(1)
        >>> q.is_empty()
        False
        """
        return len(self._items) == 0

    def size(self):
        """Returns the number of items in the queue.
        >>> q = ArrayQueue()
        >>> q.size()
        0
        >>> q.enqueue(1)
        >>> q.enqueue(2)
        >>> q.size()
        2
        """
        return len(self._items)

    def __len__(self):
        """Allows using len(q)."""
        return self.size()

    def __str__(self):
        """String representation of the queue."""
        return f"ArrayQueue({self._items})"

    def __repr__(self):
        """Representation of the queue."""
        return f"ArrayQueue({self._items})"

if __name__ == "__main__":
    import doctest
    doctest.testmod()

    q = ArrayQueue()
    print("Is queue empty?", q.is_empty())
    q.enqueue("A")
    q.enqueue("B")
    q.enqueue("C")
    print(q)
    print("Size:", len(q))
    print("Peek:", q.peek())
    print("Dequeue:", q.dequeue())
    print(q)
    print("Dequeue:", q.dequeue())
    print("Is queue empty?", q.is_empty())
    print("Dequeue:", q.dequeue())
    print("Is queue empty?", q.is_empty())
    # print("Dequeue:", q.dequeue()) # This will raise IndexError