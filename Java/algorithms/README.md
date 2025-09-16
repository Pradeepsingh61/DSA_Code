# Java Algorithms ☕⚡

This directory contains comprehensive algorithm implementations in Java, showcasing object-oriented programming principles, clean code practices, and efficient problem-solving techniques.

## 📂 Directory Structure

```
algorithms/
├── arrays/              # Array manipulation algorithms
├── backtracking/        # Backtracking algorithms
├── compression/         # Data compression algorithms
├── graph_algorithms/    # Graph traversal and algorithms
├── mathematical/        # Mathematical and numerical algorithms
├── matrix/              # Matrix operations
├── searching/           # Search algorithms
├── sorting/             # Sorting algorithms
└── string_algorithms/   # String processing algorithms
```

## 🎯 Array Algorithms

Located in `arrays/`

### Current Implementations
- **Container With Most Water** (`ContainerWithMostWater.java`) - Two-pointer technique for maximum area
- **Compare Arrays** (`CompArray.java`) - Array comparison utilities
- **Remove Element** (`RemoveElement.java`) - In-place array element removal
- **Majority Vote** (`MajorityVote.java`) - Boyer-Moore majority vote algorithm
- **Kadane's Algorithm** (`KadaneAlgorithm.java`) - Maximum subarray sum

### Java-Specific Array Features
```java
// Static imports for utility methods
import static java.util.Arrays.*;

// Enhanced for loops
for (int element : array) {
    System.out.println(element);
}

// Collections framework integration
List<Integer> list = Arrays.asList(1, 2, 3, 4, 5);
int[] array = list.stream().mapToInt(i -> i).toArray();

// Array utilities
Arrays.sort(arr);
Arrays.binarySearch(arr, target);
Arrays.equals(arr1, arr2);
System.arraycopy(src, 0, dest, 0, length);
```

## 🔍 Searching Algorithms

Located in `searching/`

### Current Implementations
- **Linear Search** (`LinearSearch.java`) - Sequential search implementation
- **Binary Search** (`Binary_Search.java`) - Logarithmic search for sorted arrays

### Java Collections Search
```java
// Using Collections framework
List<Integer> list = Arrays.asList(1, 3, 5, 7, 9);
int index = Collections.binarySearch(list, 5);

// Custom binary search implementation
public static int binarySearch(int[] arr, int target) {
    int left = 0, right = arr.length - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; // Avoid overflow

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1; // Element not found
}
```

## 📊 Sorting Algorithms

Located in `sorting/`

### Current Implementations
- **Selection Sort** (`SelectionSort.java`) - O(n²) selection-based sorting
- **Insertion Sort** (`InsertionSort.java`) - O(n²) insertion-based sorting
- **Counting Sort** (`CountingSort.java`) - O(n+k) non-comparison sorting
- **Bubble Sort** (`Bubble_Sort.java`) - O(n²) bubble-based sorting
- **Merge Sort** (`Merge_Sort.java`) - O(n log n) divide-and-conquer sorting

### Java Sorting Best Practices
```java
// Using built-in sort (TimSort - hybrid of merge sort and insertion sort)
Arrays.sort(array);

// Custom comparator for objects
Arrays.sort(students, (s1, s2) -> s1.getName().compareTo(s2.getName()));

// Using Comparator interface
Arrays.sort(students, Comparator.comparing(Student::getGrade).reversed());

// Generic sorting method
public static <T extends Comparable<T>> void bubbleSort(T[] arr) {
    int n = arr.length;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].compareTo(arr[j + 1]) > 0) {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
```

## 🌐 Graph Algorithms

Located in `graph_algorithms/`

### Current Implementations
- **Dijkstra's Algorithm** (`DijkstraAlgorithm.java`) - Shortest path algorithm
- **Floyd-Warshall** (`FloydWarshall.java`) - All-pairs shortest path

### Graph Representation in Java
```java
// Adjacency List using HashMap and ArrayList
Map<Integer, List<Integer>> adjList = new HashMap<>();

// Adjacency Matrix
int[][] adjMatrix = new int[vertices][vertices];

// Weighted graph using custom Edge class
class Edge {
    int src, dest, weight;

    public Edge(int src, int dest, int weight) {
        this.src = src;
        this.dest = dest;
        this.weight = weight;
    }
}

// Priority Queue for algorithms like Dijkstra
PriorityQueue<Node> pq = new PriorityQueue<>(
    Comparator.comparing(node -> node.distance)
);
```

## 🔢 Mathematical Algorithms

Located in `mathematical/`

### Current Implementations
- **Armstrong Number** (`ArmstrongNumber.java`) - Check if number equals sum of digits raised to power
- **Brute Force Algorithm** (`BruteForceAlgorithm.java`) - Exhaustive search approach

### Mathematical Utilities in Java
```java
// Math class utilities
Math.pow(base, exponent);
Math.sqrt(number);
Math.abs(number);
Math.max(a, b);
Math.min(a, b);

// BigInteger for large numbers
BigInteger factorial = BigInteger.ONE;
for (int i = 1; i <= n; i++) {
    factorial = factorial.multiply(BigInteger.valueOf(i));
}

// Number theory operations
public static int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

public static boolean isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}
```

## 🔤 String Algorithms

Located in `string_algorithms/`

### Current Implementations
- **Anagram** (`Anagram.java`) - Check if two strings are anagrams
- **Palindrome** (`Palindrome.java`) - Check if string reads same forwards and backwards
- **Infix to Postfix** (`InfixToPostfix.java`) - Expression conversion using stacks

### Java String Processing
```java
// String methods
String str = "Hello World";
str.length();
str.charAt(index);
str.substring(start, end);
str.toLowerCase();
str.toCharArray();

// StringBuilder for efficient string building
StringBuilder sb = new StringBuilder();
sb.append("Hello");
sb.append(" World");
String result = sb.toString();

// Regular expressions
Pattern pattern = Pattern.compile("[a-zA-Z]+");
Matcher matcher = pattern.matcher(text);

// String algorithms
public static boolean isAnagram(String s1, String s2) {
    if (s1.length() != s2.length()) return false;

    char[] arr1 = s1.toLowerCase().toCharArray();
    char[] arr2 = s2.toLowerCase().toCharArray();

    Arrays.sort(arr1);
    Arrays.sort(arr2);

    return Arrays.equals(arr1, arr2);
}
```

## 📋 Matrix Operations

Located in `matrix/`

### Current Implementations
- **Matrix Addition** (`MatrixAddition.java`) - Add two matrices

### Matrix Operations in Java
```java
// 2D array representation
int[][] matrix = new int[rows][cols];

// Matrix operations
public static int[][] addMatrices(int[][] a, int[][] b) {
    int rows = a.length;
    int cols = a[0].length;
    int[][] result = new int[rows][cols];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }

    return result;
}

// Using streams for matrix operations
int sum = Arrays.stream(matrix)
    .flatMapToInt(Arrays::stream)
    .sum();
```

## 🎯 Java-Specific Algorithm Design

### Generic Programming
```java
// Generic algorithm interface
public interface Sorter<T extends Comparable<T>> {
    void sort(T[] array);
}

// Generic implementation
public class QuickSort<T extends Comparable<T>> implements Sorter<T> {
    @Override
    public void sort(T[] array) {
        quickSort(array, 0, array.length - 1);
    }

    private void quickSort(T[] arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
}
```

### Exception Handling
```java
public static int binarySearch(int[] arr, int target)
        throws IllegalArgumentException {
    if (arr == null) {
        throw new IllegalArgumentException("Array cannot be null");
    }

    // Check if array is sorted
    for (int i = 1; i < arr.length; i++) {
        if (arr[i] < arr[i-1]) {
            throw new IllegalArgumentException("Array must be sorted");
        }
    }

    // Perform binary search
    // ...
}
```

### Documentation Standards
```java
/**
 * Performs binary search on a sorted array.
 *
 * @param arr the sorted array to search in
 * @param target the value to search for
 * @return index of target if found, -1 otherwise
 * @throws IllegalArgumentException if array is null or not sorted
 * @since 1.0
 * @author Your Name
 */
public static int binarySearch(int[] arr, int target) {
    // Implementation
}
```

## 🚀 Performance and Optimization

### Time Complexity Guidelines
- **O(1)**: Constant time - array access, hash operations
- **O(log n)**: Logarithmic - binary search, balanced trees
- **O(n)**: Linear - array traversal, linear search
- **O(n log n)**: Linearithmic - efficient sorting algorithms
- **O(n²)**: Quadratic - nested loops, simple sorting

### Memory Optimization
```java
// Use appropriate data types
byte smallNumber;    // -128 to 127
short mediumNumber;  // -32,768 to 32,767
int standardNumber;  // -2^31 to 2^31-1
long largeNumber;    // -2^63 to 2^63-1

// Object vs primitive performance
int[] primitiveArray = new int[1000];      // Fast
Integer[] objectArray = new Integer[1000]; // Slower due to boxing/unboxing

// StringBuilder vs String concatenation
// Good for multiple concatenations
StringBuilder sb = new StringBuilder();
for (String word : words) {
    sb.append(word);
}
```

## 🏆 Best Practices

### Code Quality
1. **Meaningful names**: Use descriptive method and variable names
2. **Single responsibility**: Each method should do one thing well
3. **DRY principle**: Don't repeat yourself
4. **Error handling**: Handle edge cases appropriately
5. **Documentation**: Include Javadoc for public methods

### Testing
```java
// JUnit test example
@Test
public void testBinarySearch() {
    int[] arr = {1, 3, 5, 7, 9};
    assertEquals(2, AlgorithmUtils.binarySearch(arr, 5));
    assertEquals(-1, AlgorithmUtils.binarySearch(arr, 4));
}

// Edge case testing
@Test(expected = IllegalArgumentException.class)
public void testBinarySearchWithNullArray() {
    AlgorithmUtils.binarySearch(null, 5);
}
```

Happy Java Algorithm Implementation! ☕🚀💡