# Java Data Structures ☕🏗️

This directory contains comprehensive data structure implementations in Java, emphasizing object-oriented design principles, generic programming, and the effective use of Java Collections Framework.

## 📂 Directory Structure

```
data_structures/
├── arrays/              # Array-based data structures
├── linked_lists/        # Linked list implementations
├── priority_queues/     # Priority queue implementations
├── queues/              # Queue variations
├── stacks/              # Stack implementations and applications
├── trees/               # Tree data structures
└── tries/               # Trie (prefix tree) implementations
```

## 📚 Stacks

Located in `stacks/`

### Current Implementations
- **Stack Implementation** (`Stack.java`) - Custom stack data structure
- **Delete Middle Element** (`DeleteMiddleElementOfStack.java`) - Remove middle element from stack

### Java Stack Implementation
```java
import java.util.*;

public class Stack<T> {
    private ArrayList<T> stack;
    private int top;

    public Stack() {
        stack = new ArrayList<>();
        top = -1;
    }

    // Basic operations
    public void push(T item) {
        stack.add(item);
        top++;
    }

    public T pop() {
        if (isEmpty()) {
            throw new EmptyStackException();
        }
        T item = stack.get(top);
        stack.remove(top);
        top--;
        return item;
    }

    public T peek() {
        if (isEmpty()) {
            throw new EmptyStackException();
        }
        return stack.get(top);
    }

    public boolean isEmpty() {
        return top == -1;
    }

    public int size() {
        return top + 1;
    }
}
```

### Built-in Stack Usage
```java
// Using java.util.Stack (legacy)
Stack<Integer> stack = new Stack<>();

// Using ArrayDeque (recommended)
Deque<Integer> stack = new ArrayDeque<>();
stack.push(1);
stack.push(2);
int top = stack.pop();

// Using ArrayList as stack
List<Integer> stack = new ArrayList<>();
stack.add(item);                    // push
stack.remove(stack.size() - 1);     // pop
stack.get(stack.size() - 1);        // peek
```

### Stack Applications
- **Expression Evaluation**: Infix, postfix, prefix notation
- **Parentheses Matching**: Balanced brackets checking
- **Function Call Management**: Call stack implementation
- **Undo Operations**: History management
- **Browser History**: Back button functionality

## 🔗 Linked Lists

Located in `linked_lists/`

### Current Implementations
- **Find Sum of Last N Nodes** (`FindSumOfLastNNodes.java`) - Calculate sum of last N nodes

### Linked List Implementation
```java
public class LinkedList<T> {
    private Node<T> head;
    private int size;

    private static class Node<T> {
        T data;
        Node<T> next;

        Node(T data) {
            this.data = data;
            this.next = null;
        }
    }

    // Basic operations
    public void addFirst(T data) {
        Node<T> newNode = new Node<>(data);
        newNode.next = head;
        head = newNode;
        size++;
    }

    public void addLast(T data) {
        Node<T> newNode = new Node<>(data);
        if (head == null) {
            head = newNode;
        } else {
            Node<T> current = head;
            while (current.next != null) {
                current = current.next;
            }
            current.next = newNode;
        }
        size++;
    }

    public boolean remove(T data) {
        if (head == null) return false;

        if (head.data.equals(data)) {
            head = head.next;
            size--;
            return true;
        }

        Node<T> current = head;
        while (current.next != null && !current.next.data.equals(data)) {
            current = current.next;
        }

        if (current.next != null) {
            current.next = current.next.next;
            size--;
            return true;
        }
        return false;
    }

    public void display() {
        Node<T> current = head;
        while (current != null) {
            System.out.print(current.data + " -> ");
            current = current.next;
        }
        System.out.println("null");
    }
}
```

### Java Collections Framework Lists
```java
// ArrayList - Resizable array implementation
List<Integer> arrayList = new ArrayList<>();

// LinkedList - Doubly-linked list implementation
List<Integer> linkedList = new LinkedList<>();

// Performance comparison
// ArrayList: O(1) access, O(n) insertion/deletion at arbitrary position
// LinkedList: O(n) access, O(1) insertion/deletion at known position
```

## 🏆 Priority Queues

Located in `priority_queues/`

### Current Implementations
- **Max Priority Queue** (`MaxPriorityQueue.java`) - Maximum priority queue implementation

### Priority Queue Implementation
```java
import java.util.*;

public class MaxPriorityQueue<T extends Comparable<T>> {
    private List<T> heap;

    public MaxPriorityQueue() {
        heap = new ArrayList<>();
    }

    public void insert(T item) {
        heap.add(item);
        heapifyUp(heap.size() - 1);
    }

    public T extractMax() {
        if (heap.isEmpty()) {
            throw new NoSuchElementException("Priority queue is empty");
        }

        T max = heap.get(0);
        T lastItem = heap.remove(heap.size() - 1);

        if (!heap.isEmpty()) {
            heap.set(0, lastItem);
            heapifyDown(0);
        }

        return max;
    }

    private void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap.get(index).compareTo(heap.get(parentIndex)) <= 0) {
                break;
            }
            Collections.swap(heap, index, parentIndex);
            index = parentIndex;
        }
    }

    private void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < heap.size() &&
            heap.get(leftChild).compareTo(heap.get(largest)) > 0) {
            largest = leftChild;
        }

        if (rightChild < heap.size() &&
            heap.get(rightChild).compareTo(heap.get(largest)) > 0) {
            largest = rightChild;
        }

        if (largest != index) {
            Collections.swap(heap, index, largest);
            heapifyDown(largest);
        }
    }
}
```

### Built-in Priority Queue
```java
// Min heap by default
PriorityQueue<Integer> minHeap = new PriorityQueue<>();

// Max heap using custom comparator
PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());

// Custom objects with priority
PriorityQueue<Task> taskQueue = new PriorityQueue<>(
    Comparator.comparing(Task::getPriority).reversed()
);
```

## 🌳 Trees

Located in `trees/`

### Tree Types to Implement
- [ ] **Binary Tree** - Basic binary tree operations
- [ ] **Binary Search Tree** - Self-organizing binary tree
- [ ] **AVL Tree** - Self-balancing binary search tree
- [ ] **Red-Black Tree** - Balanced binary search tree
- [ ] **B-Tree** - Multi-way tree for databases
- [ ] **Segment Tree** - Range query data structure
- [ ] **Fenwick Tree** - Binary indexed tree

### Binary Tree Implementation
```java
public class BinaryTree<T> {
    private TreeNode<T> root;

    private static class TreeNode<T> {
        T data;
        TreeNode<T> left, right;

        TreeNode(T data) {
            this.data = data;
            this.left = null;
            this.right = null;
        }
    }

    // Tree traversals
    public void inorderTraversal(TreeNode<T> node) {
        if (node != null) {
            inorderTraversal(node.left);
            System.out.print(node.data + " ");
            inorderTraversal(node.right);
        }
    }

    public void preorderTraversal(TreeNode<T> node) {
        if (node != null) {
            System.out.print(node.data + " ");
            preorderTraversal(node.left);
            preorderTraversal(node.right);
        }
    }

    public void postorderTraversal(TreeNode<T> node) {
        if (node != null) {
            postorderTraversal(node.left);
            postorderTraversal(node.right);
            System.out.print(node.data + " ");
        }
    }

    // Level order traversal using queue
    public void levelOrderTraversal() {
        if (root == null) return;

        Queue<TreeNode<T>> queue = new LinkedList<>();
        queue.add(root);

        while (!queue.isEmpty()) {
            TreeNode<T> current = queue.poll();
            System.out.print(current.data + " ");

            if (current.left != null) {
                queue.add(current.left);
            }
            if (current.right != null) {
                queue.add(current.right);
            }
        }
    }
}
```

### Binary Search Tree
```java
public class BinarySearchTree<T extends Comparable<T>> {
    private TreeNode<T> root;

    public void insert(T data) {
        root = insertRec(root, data);
    }

    private TreeNode<T> insertRec(TreeNode<T> root, T data) {
        if (root == null) {
            root = new TreeNode<>(data);
            return root;
        }

        if (data.compareTo(root.data) < 0) {
            root.left = insertRec(root.left, data);
        } else if (data.compareTo(root.data) > 0) {
            root.right = insertRec(root.right, data);
        }

        return root;
    }

    public boolean search(T data) {
        return searchRec(root, data);
    }

    private boolean searchRec(TreeNode<T> root, T data) {
        if (root == null) return false;
        if (root.data.equals(data)) return true;

        return data.compareTo(root.data) < 0 ?
            searchRec(root.left, data) : searchRec(root.right, data);
    }
}
```

## 🅰️ Tries (Prefix Trees)

Located in `tries/`

### Trie Implementation
```java
public class Trie {
    private TrieNode root;

    private static class TrieNode {
        Map<Character, TrieNode> children;
        boolean isEndOfWord;

        TrieNode() {
            children = new HashMap<>();
            isEndOfWord = false;
        }
    }

    public Trie() {
        root = new TrieNode();
    }

    public void insert(String word) {
        TrieNode current = root;
        for (char ch : word.toCharArray()) {
            current.children.putIfAbsent(ch, new TrieNode());
            current = current.children.get(ch);
        }
        current.isEndOfWord = true;
    }

    public boolean search(String word) {
        TrieNode current = root;
        for (char ch : word.toCharArray()) {
            if (!current.children.containsKey(ch)) {
                return false;
            }
            current = current.children.get(ch);
        }
        return current.isEndOfWord;
    }

    public boolean startsWith(String prefix) {
        TrieNode current = root;
        for (char ch : prefix.toCharArray()) {
            if (!current.children.containsKey(ch)) {
                return false;
            }
            current = current.children.get(ch);
        }
        return true;
    }

    // Auto-complete functionality
    public List<String> findWordsWithPrefix(String prefix) {
        List<String> result = new ArrayList<>();
        TrieNode current = root;

        // Navigate to the prefix
        for (char ch : prefix.toCharArray()) {
            if (!current.children.containsKey(ch)) {
                return result; // No words with this prefix
            }
            current = current.children.get(ch);
        }

        // DFS to find all words with this prefix
        dfs(current, prefix, result);
        return result;
    }

    private void dfs(TrieNode node, String currentWord, List<String> result) {
        if (node.isEndOfWord) {
            result.add(currentWord);
        }

        for (Map.Entry<Character, TrieNode> entry : node.children.entrySet()) {
            dfs(entry.getValue(), currentWord + entry.getKey(), result);
        }
    }
}
```

## 🎯 Java Collections Framework Integration

### Choosing the Right Collection
```java
// List implementations
List<String> arrayList = new ArrayList<>();    // Fast random access
List<String> linkedList = new LinkedList<>();  // Fast insertion/deletion
List<String> vector = new Vector<>();          // Synchronized ArrayList

// Set implementations
Set<String> hashSet = new HashSet<>();         // O(1) operations, no order
Set<String> linkedHashSet = new LinkedHashSet<>(); // Maintains insertion order
Set<String> treeSet = new TreeSet<>();         // Sorted order, O(log n)

// Map implementations
Map<String, Integer> hashMap = new HashMap<>(); // O(1) operations
Map<String, Integer> linkedHashMap = new LinkedHashMap<>(); // Insertion order
Map<String, Integer> treeMap = new TreeMap<>(); // Sorted by keys

// Queue implementations
Queue<Integer> queue = new LinkedList<>();      // FIFO queue
Queue<Integer> priorityQueue = new PriorityQueue<>(); // Priority-based
Deque<Integer> deque = new ArrayDeque<>();      // Double-ended queue
```

### Generic Programming
```java
// Generic data structure interface
public interface DataStructure<T> {
    void insert(T item);
    boolean remove(T item);
    boolean contains(T item);
    int size();
    boolean isEmpty();
}

// Generic implementation
public class GenericStack<T> implements DataStructure<T> {
    private ArrayList<T> stack;

    public GenericStack() {
        stack = new ArrayList<>();
    }

    @Override
    public void insert(T item) {
        stack.add(item);
    }

    @Override
    public boolean remove(T item) {
        return stack.remove(item);
    }

    // Additional stack-specific methods
    public T pop() {
        if (isEmpty()) {
            throw new EmptyStackException();
        }
        return stack.remove(stack.size() - 1);
    }

    public T peek() {
        if (isEmpty()) {
            throw new EmptyStackException();
        }
        return stack.get(stack.size() - 1);
    }
}
```

## 🏆 Performance Characteristics

### Time Complexities
| Data Structure | Access | Search | Insertion | Deletion |
|----------------|--------|--------|-----------|----------|
| Array          | O(1)   | O(n)   | O(n)      | O(n)     |
| ArrayList      | O(1)   | O(n)   | O(1)*     | O(n)     |
| LinkedList     | O(n)   | O(n)   | O(1)      | O(1)     |
| HashMap        | O(1)*  | O(1)*  | O(1)*     | O(1)*    |
| TreeMap        | O(log n)| O(log n)| O(log n) | O(log n) |
| Priority Queue | -      | O(n)   | O(log n)  | O(log n) |

*Amortized time complexity

### Space Complexities
- **Arrays**: O(n)
- **Linked Lists**: O(n) + pointer overhead
- **Trees**: O(n) + tree structure overhead
- **Hash Tables**: O(n) + hash table overhead

## 🚀 Best Practices

### Design Principles
1. **Encapsulation**: Hide internal implementation details
2. **Generic Programming**: Use type parameters for flexibility
3. **Fail-Fast Iterators**: Detect concurrent modifications
4. **Immutable Objects**: When possible, create immutable data structures
5. **Builder Pattern**: For complex data structure construction

### Error Handling
```java
public class SafeStack<T> {
    private List<T> stack = new ArrayList<>();

    public T pop() throws EmptyStackException {
        if (stack.isEmpty()) {
            throw new EmptyStackException("Cannot pop from empty stack");
        }
        return stack.remove(stack.size() - 1);
    }

    public Optional<T> safePop() {
        return stack.isEmpty() ?
            Optional.empty() :
            Optional.of(stack.remove(stack.size() - 1));
    }
}

// Usage with Optional
SafeStack<Integer> stack = new SafeStack<>();
Optional<Integer> value = stack.safePop();
if (value.isPresent()) {
    System.out.println("Popped: " + value.get());
} else {
    System.out.println("Stack is empty");
}
```

### Memory Management
```java
// Avoid memory leaks in custom implementations
public class MemoryEfficientStack<T> {
    private T[] array;
    private int size;
    private int capacity;

    @SuppressWarnings("unchecked")
    public MemoryEfficientStack(int initialCapacity) {
        array = (T[]) new Object[initialCapacity];
        capacity = initialCapacity;
        size = 0;
    }

    public T pop() {
        if (size == 0) {
            throw new EmptyStackException();
        }
        T item = array[--size];
        array[size] = null; // Prevent memory leak
        return item;
    }

    // Resize array when necessary
    private void resize() {
        if (size == capacity) {
            capacity *= 2;
            array = Arrays.copyOf(array, capacity);
        }
    }
}
```

Happy Java Data Structure Implementation! ☕🏗️🚀