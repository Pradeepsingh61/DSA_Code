# C Language Implementations 🔧

Welcome to the **C section** of our DSA repository! This directory contains fundamental implementations of algorithms and data structures in C, focusing on system-level programming and efficient memory management.

## 📂 Directory Structure

```
C/
├── algorithms/                 # Algorithm Implementations
│   ├── searching/             # Search algorithms
│   └── sorting/               # Sorting algorithms
├── data_structures/           # Data Structure Implementations
│   ├── queues/               # Queue implementations
│   ├── stacks/               # Stack implementations
│   └── trees/                # Tree structures
├── dynamic_programming/       # DP Solutions
└── projects/                 # Complete C projects
```

## 🚀 Quick Start

### C Development Setup

1. **Compiler**: GCC, Clang, or any C compiler
2. **Standards**: C99 or C11 recommended
3. **Build Commands**:
   ```bash
   gcc -o program program.c -std=c99 -Wall -Wextra
   ./program
   ```

### Adding New Algorithms

```c
/*
 * Algorithm: [Algorithm Name]
 * Description: [Brief description of what the algorithm does]
 * Time Complexity: [Big O notation]
 * Space Complexity: [Big O notation]
 * Author: [Your Name]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Brief description of the function
 *
 * @param arr: Array to process
 * @param size: Size of the array
 * @return: Description of return value
 */
int algorithm_function(int arr[], int size) {
    // Input validation
    if (arr == NULL || size <= 0) {
        fprintf(stderr, "Error: Invalid input parameters\n");
        return -1;
    }

    // Algorithm implementation here

    return result;
}

/**
 * Test function to demonstrate the algorithm
 */
void test_algorithm() {
    printf("Testing Algorithm...\n");

    // Test Case 1: Normal case
    int test_arr1[] = {1, 2, 3, 4, 5};
    int size1 = sizeof(test_arr1) / sizeof(test_arr1[0]);
    int result1 = algorithm_function(test_arr1, size1);
    printf("Test 1 - Input: {1,2,3,4,5}, Result: %d\n", result1);

    // Test Case 2: Edge case
    int *test_arr2 = NULL;
    int result2 = algorithm_function(test_arr2, 0);
    printf("Test 2 - Edge case handled: %d\n", result2);
}

int main() {
    test_algorithm();
    return 0;
}
```

## 📊 Current Implementations

### Algorithms
- **Sorting**: Selection Sort (relocated from root)
- **Searching**: Binary Search, Linear Search implementations
- **Basic Algorithms**: Fundamental algorithmic concepts

### Data Structures
- **Trees**: Binary Search Tree traversal
- **Queues**: Priority Queue implementation
- **Linear Structures**: Basic stack and queue operations

### Dynamic Programming
- **Classic Problems**: Knapsack problem implementation
- **Optimization**: Memory-efficient DP solutions

### Projects
- **Lexical Analyzer**: Compiler design components
- **System Programming**: Low-level implementations

## 🔧 C-Specific Features & Best Practices

### Memory Management
```c
#include <stdlib.h>

// Dynamic memory allocation
int* create_array(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    return arr;
}

// Always free allocated memory
void cleanup_array(int* arr) {
    if (arr != NULL) {
        free(arr);
        arr = NULL;  // Avoid dangling pointers
    }
}

// Example usage
int main() {
    int* dynamic_arr = create_array(10);

    // Use the array...

    cleanup_array(dynamic_arr);
    return 0;
}
```

### Pointer Manipulation
```c
// Swapping using pointers
void swap(int* a, int* b) {
    if (a != NULL && b != NULL) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}

// Array processing with pointers
int find_max(int* arr, int size) {
    if (arr == NULL || size <= 0) return -1;

    int max = *arr;
    for (int* ptr = arr + 1; ptr < arr + size; ptr++) {
        if (*ptr > max) {
            max = *ptr;
        }
    }
    return max;
}
```

### Struct-Based Data Structures
```c
// Node structure for linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Tree node structure
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Create a new node
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}
```

### Error Handling
```c
#include <errno.h>

// Robust file handling
FILE* safe_fopen(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode);
    if (file == NULL) {
        fprintf(stderr, "Error opening file '%s': %s\n",
                filename, strerror(errno));
        return NULL;
    }
    return file;
}

// Safe string operations
char* safe_strdup(const char* src) {
    if (src == NULL) return NULL;

    size_t len = strlen(src) + 1;
    char* dst = malloc(len);
    if (dst == NULL) {
        fprintf(stderr, "Memory allocation failed in strdup\n");
        return NULL;
    }

    strcpy(dst, src);
    return dst;
}
```

## 🔥 Popular Algorithms to Implement

### High Priority
- [ ] Quick Sort implementation
- [ ] Merge Sort implementation
- [ ] Hash Table with collision handling
- [ ] Binary Search Tree operations (insert, delete, search)
- [ ] Linked List operations (single, double, circular)
- [ ] Stack and Queue implementations

### Medium Priority
- [ ] Heap implementation (min/max heap)
- [ ] Graph representations (adjacency list/matrix)
- [ ] DFS and BFS for graphs
- [ ] Basic string algorithms (KMP, Boyer-Moore)
- [ ] Bit manipulation algorithms

### Advanced
- [ ] Memory pool allocator
- [ ] Lock-free data structures
- [ ] System-level implementations
- [ ] Performance-critical algorithms

## 💡 C Programming Guidelines

### Code Style
```c
// Function naming: snake_case
int binary_search(int arr[], int size, int target);

// Variable naming: snake_case
int array_size = 10;
int* student_grades;

// Constants: UPPER_SNAKE_CASE
#define MAX_ARRAY_SIZE 1000
#define PI 3.14159

// Struct naming: PascalCase
typedef struct BinaryTree {
    int data;
    struct BinaryTree* left;
    struct BinaryTree* right;
} BinaryTree;
```

### Header Files
```c
// algorithm_name.h
#ifndef ALGORITHM_NAME_H
#define ALGORITHM_NAME_H

#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int algorithm_function(int arr[], int size);
void print_array(int arr[], int size);

// Constants
#define MAX_SIZE 100

#endif // ALGORITHM_NAME_H
```

### Makefile Example
```makefile
# Makefile for C programs
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = program
SOURCES = main.c algorithm.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: all clean
```

## 🌟 Performance Considerations

### Memory Efficiency
```c
// Use appropriate data types
uint8_t small_number;    // 0-255
uint16_t medium_number;  // 0-65535
uint32_t large_number;   // 0-4294967295

// Struct padding awareness
typedef struct {
    char a;     // 1 byte
    int b;      // 4 bytes (with 3 bytes padding after 'a')
    char c;     // 1 byte (with 3 bytes padding after)
} BadStruct;   // Total: 12 bytes

typedef struct {
    int b;      // 4 bytes
    char a;     // 1 byte
    char c;     // 1 byte (with 2 bytes padding after)
} GoodStruct;  // Total: 8 bytes
```

### Optimization Tips
```c
// Loop optimization
// Bad: Division in loop
for (int i = 0; i < size/2; i++) {
    // Process...
}

// Good: Calculate once
int half_size = size >> 1;  // Bit shift for division by 2
for (int i = 0; i < half_size; i++) {
    // Process...
}

// Register hint for frequently used variables
register int counter;
```

## 🎯 Contribution Guidelines

### Code Quality Checklist
- [ ] Includes proper header comments
- [ ] Uses meaningful variable and function names
- [ ] Has proper error handling and input validation
- [ ] Manages memory correctly (malloc/free pairs)
- [ ] Includes test cases in main function
- [ ] Follows consistent indentation (4 spaces)
- [ ] Avoids memory leaks and buffer overflows

### Safety Guidelines
```c
// Buffer overflow prevention
char buffer[256];
strncpy(buffer, source, sizeof(buffer) - 1);
buffer[sizeof(buffer) - 1] = '\0';  // Ensure null termination

// Safe scanf usage
char input[100];
if (scanf("%99s", input) == 1) {  // Limit input size
    // Process input
}

// Pointer validation
if (ptr != NULL) {
    // Safe to dereference
    int value = *ptr;
}
```

## 🚀 Advanced Topics

### Function Pointers
```c
// Function pointer for sorting algorithms
typedef int (*compare_func_t)(const void* a, const void* b);

void generic_sort(void* arr, size_t count, size_t size, compare_func_t cmp) {
    // Implementation using qsort or custom algorithm
    qsort(arr, count, size, cmp);
}

// Comparison functions
int int_compare(const void* a, const void* b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}
```

### Preprocessor Macros
```c
// Debug macros
#ifdef DEBUG
#define DBG_PRINT(fmt, ...) \
    fprintf(stderr, "[DEBUG] %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define DBG_PRINT(fmt, ...)
#endif

// Generic macros
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
```

Happy C Programming! 🔧🚀

---
**Note**: Focus on writing efficient, safe, and portable C code. Always validate inputs, manage memory properly, and include comprehensive test cases.