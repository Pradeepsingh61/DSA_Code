# linked_list_demo.py
from __future__ import annotations
from dataclasses import dataclass
from typing import Any, Iterable, Iterator, Optional


@dataclass
class Node:
    value: Any
    next: Optional["Node"] = None

    def __repr__(self) -> str:
        return f"Node({self.value})"


class LinkedList:
    """A minimal singly linked list with O(1) append via tail pointer."""

    def __init__(self) -> None:
        self.head: Optional[Node] = None
        self.tail: Optional[Node] = None
        self._size: int = 0

    # ---------- Core helpers ----------
    def __len__(self) -> int:
        return self._size

    def __iter__(self) -> Iterator[Any]:
        curr = self.head
        while curr:
            yield curr.value
            curr = curr.next

    def __repr__(self) -> str:
        return f"LinkedList([{', '.join(map(str, self))}])"

    @classmethod
    def from_iterable(cls, items: Iterable[Any]) -> "LinkedList":
        ll = cls()
        for x in items:
            ll.append(x)
        return ll

    # ---------- Operations ----------
    def append(self, value: Any) -> None:
        """Add to the end. O(1)."""
        node = Node(value)
        if not self.head:
            self.head = self.tail = node
        else:
            assert self.tail is not None  # for type checkers
            self.tail.next = node
            self.tail = node
        self._size += 1

    def prepend(self, value: Any) -> None:
        """Add to the front. O(1)."""
        node = Node(value, self.head)
        self.head = node
        if self.tail is None:
            self.tail = node
        self._size += 1

    def insert_at(self, index: int, value: Any) -> None:
        """Insert at index in [0, len]. O(n) worst-case."""
        if index < 0 or index > self._size:
            raise IndexError("index out of range")
        if index == 0:
            self.prepend(value)
            return
        if index == self._size:
            self.append(value)
            return

        prev = self._node_at(index - 1)
        node = Node(value, prev.next)
        prev.next = node
        self._size += 1

    def remove(self, value: Any) -> bool:
        """Remove first occurrence. Returns True if removed. O(n)."""
        prev: Optional[Node] = None
        curr = self.head
        while curr:
            if curr.value == value:
                if prev is None:
                    # removing head
                    self.head = curr.next
                else:
                    prev.next = curr.next
                if curr is self.tail:
                    self.tail = prev
                self._size -= 1
                return True
            prev, curr = curr, curr.next
        return False

    def pop_first(self) -> Any:
        """Remove and return the first element. O(1)."""
        if not self.head:
            raise IndexError("pop from empty list")
        node = self.head
        self.head = node.next
        if node is self.tail:
            self.tail = None
        self._size -= 1
        return node.value

    def pop_last(self) -> Any:
        """Remove and return the last element. O(n) to find penultimate."""
        if not self.head:
            raise IndexError("pop from empty list")
        if self.head is self.tail:
            val = self.head.value
            self.head = self.tail = None
            self._size = 0
            return val
        # find penultimate
        prev = self.head
        curr = self.head.next
        while curr and curr is not self.tail:
            prev, curr = curr, curr.next
        assert self.tail is curr
        val = self.tail.value
        self.tail = prev
        self.tail.next = None
        self._size -= 1
        return val

    def find(self, value: Any) -> Optional[Node]:
        """Return the first node with the given value, else None. O(n)."""
        curr = self.head
        while curr:
            if curr.value == value:
                return curr
            curr = curr.next
        return None

    def reverse(self) -> None:
        """In-place reverse. O(n), O(1) extra space."""
        prev = None
        curr = self.head
        self.tail = self.head
        while curr:
            nxt = curr.next
            curr.next = prev
            prev = curr
            curr = nxt
        self.head = prev

    # ---------- Internal ----------
    def _node_at(self, index: int) -> Node:
        """Return node at index in [0, len-1]."""
        if index < 0 or index >= self._size:
            raise IndexError("index out of range")
        curr = self.head
        for _ in range(index):
            assert curr is not None
            curr = curr.next
        assert curr is not None
        return curr


# ----------------- Demo -----------------
if __name__ == "__main__":
    print("Linked list demo:")
    ll = LinkedList.from_iterable([10, 20, 30])
    print("Start:         ", ll)  # [10, 20, 30]

    ll.append(40)
    print("After append:  ", ll)  # [10, 20, 30, 40]

    ll.prepend(5)
    print("After prepend: ", ll)  # [5, 10, 20, 30, 40]

    ll.insert_at(2, 15)
    print("Insert @2=15:  ", ll)  # [5, 10, 15, 20, 30, 40]

    removed = ll.remove(20)
    print(f"Remove 20? {removed} ->", ll)

    first = ll.pop_first()
    last = ll.pop_last()
    print(f"Popped first={first}, last={last} ->", ll)

    print("Find 30 ->", ll.find(30))
    print("Find 999 ->", ll.find(999))

    ll.reverse()
    print("Reversed:      ", ll)

    print("Iterating values:", list(ll))
