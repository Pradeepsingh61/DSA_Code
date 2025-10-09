// Author: HarshitKumarPandey
// Date: 2025-10-09
// Description: Rotate a singly linked list to the right by k positions.

class ListNode {
  constructor(val = 0, next = null) {
    this.val = val;
    this.next = next;
  }
}

function rotateRight(head, k) {
  if (!head || !head.next || k === 0) return head;

  // Step 1: Find the length of the list
  let length = 1;
  let tail = head;
  while (tail.next) {
    tail = tail.next;
    length++;
  }

  // Step 2: Make it circular
  tail.next = head;

  // Step 3: Find new tail: (length - k % length - 1)th node
  k = k % length;
  let stepsToNewHead = length - k;
  let newTail = tail;
  while (stepsToNewHead-- > 0) {
    newTail = newTail.next;
  }

  const newHead = newTail.next;
  newTail.next = null; // break the circle

  return newHead;
}

// Helper function to print linked list
function printList(head) {
  const values = [];
  let curr = head;
  while (curr) {
    values.push(curr.val);
    curr = curr.next;
  }
  console.log(values.join(" -> "));
}

// Example usage
const head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
const k = 2;

console.log("Original List:");
printList(head);

const rotated = rotateRight(head, k);
console.log("Rotated List:");
printList(rotated); // Output: 4 -> 5 -> 1 -> 2 -> 3
