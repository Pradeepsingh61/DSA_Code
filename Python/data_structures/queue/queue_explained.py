"""
Queue — Full Explanation and Multiple Implementations
----------------------------------------------------

Description
-----------
This file is written to teach the Queue data structure clearly and practically.
A reader who opens this file should understand:
    1. What a queue is and when to use it.
    2. Basic operations (enqueue, dequeue, peek, is_empty, size).
    3. Trade-offs between simple list-based queue, circular array queue,
       and linked-list queue.
    4. Complexity analysis for each approach.
    5. Example usages and edge cases.

    
High-level Queue Definition
---------------------------
A Queue is a linear data structure that follows **FIFO** (First-In-First-Out).
Operations:
- enqueue(x): insert x at the rear
- dequeue(): remove and return item from the front
- peek()/front(): return front item without removing
- is_empty(): check if queue is empty
- size(): number of elements

Implementations included below:
1) Simple List-backed Queue (teaches concept; not optimal)
2) Circular Array Queue (fixed-size, efficient)
3) Linked-List Queue (dynamic size, efficient)
4) Short notes about Deque and Python collections (concept only)

Complexity Summary
------------------
- List-backed (append/pop(0)): enqueue O(1), dequeue O(n) — bad for many dequeues
- Circular array: enqueue O(1), dequeue O(1) — best when capacity known
- Linked-list queue: enqueue O(1), dequeue O(1) — best when dynamic size needed

"""

# ---------------------------------------------------------------------
# 1) Simple list-backed Queue (for conceptual understanding only)
# ---------------------------------------------------------------------
class SimpleQueue:
    """
    Simple queue using Python list.
    - enqueue: append at end (O(1))
    - dequeue: pop from front (pop(0)) (O(n)) because elements shift left
    Use this for learning only, not for heavy use.
    """
    def __init__(self):
        self._data = []

    def enqueue(self, value):
        """Add value to the rear of the queue"""
        self._data.append(value)

    def dequeue(self):
        """Remove and return front value. Raises IndexError if empty."""
        if self.is_empty():
            raise IndexError("dequeue from empty queue")
        return self._data.pop(0)

    def peek(self):
        """Return front value without removing. None if empty."""
        return None if self.is_empty() else self._data[0]

    def is_empty(self):
        return len(self._data) == 0

    def size(self):
        return len(self._data)


# ---------------------------------------------------------------------
# 2) Circular Array Queue (fixed capacity) — efficient O(1) ops
# ---------------------------------------------------------------------
class CircularQueue:
    """
    Circular (ring) buffer implementation with fixed capacity.

    Internal layout:
        - array of size capacity
        - front index points to the front element
        - rear index points to next insertion position
        - count stores current number of elements
    This implementation supports enqueue and dequeue in O(1) time.
    """
    def __init__(self, capacity):
        if capacity <= 0:
            raise ValueError("capacity must be positive")
        self._cap = capacity
        self._arr = [None] * capacity
        self._front = 0    # index of current front element
        self._rear = 0     # index where next element will be inserted
        self._count = 0    # number of elements present

    def enqueue(self, value):
        """Insert value at rear. Raises OverflowError if full."""
        if self._count == self._cap:
            raise OverflowError("enqueue to full queue")
        self._arr[self._rear] = value
        # move rear to next position in circular manner
        self._rear = (self._rear + 1) % self._cap
        self._count += 1

    def dequeue(self):
        """Remove and return front value. Raises IndexError if empty."""
        if self.is_empty():
            raise IndexError("dequeue from empty queue")
        val = self._arr[self._front]
        self._arr[self._front] = None  # optional: help GC / clarity
        self._front = (self._front + 1) % self._cap
        self._count -= 1
        return val

    def peek(self):
        return None if self.is_empty() else self._arr[self._front]

    def is_empty(self):
        return self._count == 0

    def is_full(self):
        return self._count == self._cap

    def size(self):
        return self._count

    def capacity(self):
        return self._cap

    def __repr__(self):
        """Simple representation showing current items in logical order."""
        items = []
        idx = self._front
        for _ in range(self._count):
            items.append(self._arr[idx])
            idx = (idx + 1) % self._cap
        return f"CircularQueue({items})"


# ---------------------------------------------------------------------
# 3) Linked-List Queue — dynamic size, O(1) enqueue & dequeue
# ---------------------------------------------------------------------
class _Node:
    """Internal node used by LinkedListQueue"""
    def __init__(self, val):
        self.val = val
        self.next = None


class LinkedListQueue:
    """
    Queue implemented using singly-linked list with head & tail pointers.
    - enqueue: push to tail (O(1))
    - dequeue: pop from head (O(1))
    Good when you need a queue with unknown or large size.
    """
    def __init__(self):
        self._head = None  # front
        self._tail = None  # rear
        self._count = 0

    def enqueue(self, value):
        node = _Node(value)
        if self._tail is None:
            # empty queue
            self._head = self._tail = node
        else:
            self._tail.next = node
            self._tail = node
        self._count += 1

    def dequeue(self):
        if self.is_empty():
            raise IndexError("dequeue from empty queue")
        val = self._head.val
        self._head = self._head.next
        if self._head is None:
            # queue became empty
            self._tail = None
        self._count -= 1
        return val

    def peek(self):
        return None if self._head is None else self._head.val

    def is_empty(self):
        return self._count == 0

    def size(self):
        return self._count

    def __repr__(self):
        vals = []
        cur = self._head
        while cur:
            vals.append(cur.val)
            cur = cur.next
        return f"LinkedListQueue({vals})"


# ---------------------------------------------------------------------
# 4) Notes: Deque and Python built-ins (conceptual)
# ---------------------------------------------------------------------
"""
Note for reviewers/learners:
- Python's collections.deque is a highly optimized double-ended queue (O(1) append/pop both ends).
  We are not using it here because this file aims to teach low-level implementations.
- Use deque in production code for most queue needs in Python.
"""

# ---------------------------------------------------------------------
# 5) Small test suite (examples + edge cases)
# ---------------------------------------------------------------------
def run_tests():
    print("Running tests for Queue implementations...\n")

    # Test SimpleQueue (conceptual)
    sq = SimpleQueue()
    sq.enqueue(1)
    sq.enqueue(2)
    sq.enqueue(3)
    assert sq.size() == 3
    assert sq.peek() == 1
    assert sq.dequeue() == 1
    assert sq.dequeue() == 2
    assert sq.dequeue() == 3
    try:
        sq.dequeue()
        assert False, "Expected exception on empty dequeue"
    except IndexError:
        pass  # expected

    print("SimpleQueue tests passed.")

    # Test CircularQueue
    cq = CircularQueue(3)
    assert cq.is_empty()
    cq.enqueue(10)
    cq.enqueue(20)
    cq.enqueue(30)
    assert cq.is_full()
    assert repr(cq) in ("CircularQueue([10, 20, 30])", "CircularQueue([10, 20, 30])")
    assert cq.dequeue() == 10
    cq.enqueue(40)
    assert cq.size() == 3
    assert cq.dequeue() == 20
    assert cq.dequeue() == 30
    assert cq.dequeue() == 40
    try:
        cq.dequeue()
        assert False, "Expected exception on empty dequeue"
    except IndexError:
        pass

    print("CircularQueue tests passed.")

    # Test LinkedListQueue
    llq = LinkedListQueue()
    llq.enqueue("a")
    llq.enqueue("b")
    assert llq.size() == 2
    assert llq.peek() == "a"
    assert llq.dequeue() == "a"
    assert llq.dequeue() == "b"
    try:
        llq.peek()  # should return None, not error
    except Exception:
        assert False, "peek should not raise"
    print("LinkedListQueue tests passed.")

    print("\nAll tests passed successfully!")


# ---------------------------------------------------------------------
# 6) Demo printed examples for quick manual verification
# ---------------------------------------------------------------------
if __name__ == "__main__":
    print("Queue — educational examples\n")
    # Demo SimpleQueue
    print("SimpleQueue demo:")
    sq = SimpleQueue()
    for x in [5, 6, 7]:
        sq.enqueue(x)
    print(" After enqueues:", sq._data)
    print(" Dequeue ->", sq.dequeue())
    print(" Now front ->", sq.peek())
    print()

    # Demo CircularQueue
    print("CircularQueue demo:")
    cq = CircularQueue(4)
    for x in [1, 2, 3]:
        cq.enqueue(x)
    print(" After enqueues:", repr(cq))
    print(" Dequeue ->", cq.dequeue())
    cq.enqueue(99)
    print(" After enqueue 99:", repr(cq))
    print()

    # Demo LinkedListQueue
    print("LinkedListQueue demo:")
    llq = LinkedListQueue()
    for ch in ["x", "y", "z"]:
        llq.enqueue(ch)
    print(" After enqueues:", repr(llq))
    print(" Dequeue ->", llq.dequeue())
    print(" Now queue:", repr(llq))
    print()

    # Run assertions/tests
    run_tests()
