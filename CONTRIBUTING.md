# 🤝 Contributing to DSA Code Repository

Welcome to the **DSA Code Repository**! We're excited to have you contribute to this comprehensive collection of algorithms and data structures. This guide will help you make meaningful contributions for **Hacktoberfest 2025** and beyond.

## 🌟 Table of Contents

- [Getting Started](#-getting-started)
- [Repository Structure](#-repository-structure)
- [Contribution Guidelines](#-contribution-guidelines)
- [Code Standards](#-code-standards)
- [Pull Request Process](#-pull-request-process)
- [Community Guidelines](#-community-guidelines)

## 🚀 Getting Started

### Prerequisites
- Git installed on your machine
- Basic knowledge of at least one programming language (C, C++, Java, Python)
- GitHub account
- Text editor or IDE of your choice

### First-Time Setup

1. **Fork the Repository**
   ```bash
   # Click the "Fork" button on GitHub
   # This creates your personal copy of the repository
   ```

2. **Clone Your Fork**
   ```bash
   git clone https://github.com/YOUR_USERNAME/DSA_Code.git
   cd DSA_Code
   ```

3. **Set Up Remote**
   ```bash
   git remote add upstream https://github.com/ORIGINAL_OWNER/DSA_Code.git
   git remote -v  # Verify remotes
   ```

4. **Stay Updated**
   ```bash
   git fetch upstream
   git checkout main
   git merge upstream/main
   ```

## 📁 Repository Structure

Our repository follows a **Language → Topic → Implementation** structure:

```
DSA_Code/
├── C/                          # C Language Implementations
│   ├── algorithms/
│   │   ├── searching/          # Search algorithms
│   │   ├── sorting/            # Sort algorithms
│   │   └── mathematical/       # Math algorithms
│   ├── data_structures/        # Core data structures
│   └── dynamic_programming/    # DP solutions
├── CPP/                        # C++ Language Implementations
│   ├── algorithms/             # Algorithm categories
│   ├── data_structures/        # Data structure implementations
│   ├── dynamic_programming/    # DP solutions
│   └── object_oriented_programming/ # OOP concepts
├── Java/                       # Java Language Implementations
│   ├── algorithms/             # Enterprise algorithm patterns
│   ├── data_structures/        # Collection framework usage
│   ├── dynamic_programming/    # DP with Java features
│   └── projects/              # Complete Java applications
└── Python/                     # Python Language Implementations
    ├── algorithms/             # Clean, readable algorithms
    ├── data_structures/        # Pythonic implementations
    ├── dynamic_programming/    # DP with Python features
    └── projects/              # Complete Python projects
```

## 🎯 Contribution Guidelines

### What You Can Contribute

#### 🔥 **High Priority Contributions**
- **Missing Algorithms**: Implement algorithms not yet in the repository
- **New Data Structures**: Add data structure implementations
- **New Programming Languages**: Add support for JavaScript, Go, Rust, Kotlin, Swift, etc.
- **Complete Projects**: Full applications demonstrating algorithms
- **Optimization**: Improve existing code performance
- **Documentation**: Add comprehensive comments and examples

#### 🌟 **Medium Priority Contributions**
- **Test Cases**: Add unit tests for existing implementations
- **Bug Fixes**: Fix issues in current code
- **Code Refactoring**: Improve code quality and readability
- **Cross-Language Ports**: Port algorithms between languages
- **Language-Specific READMEs**: Setup guides for new languages
- **README Improvements**: Enhance documentation

#### 💡 **Beginner-Friendly Contributions**
- **Comments**: Add explanatory comments to existing code
- **Examples**: Provide usage examples for algorithms
- **Documentation**: Fix typos and improve clarity
- **Simple Algorithms**: Implement basic algorithms

### Choosing the Right Directory

#### For **C** Contributions:
```
C/
├── algorithms/searching/       → binary_search.c
├── algorithms/sorting/         → quick_sort.c
├── algorithms/mathematical/    → prime_check.c
├── data_structures/stacks/     → stack_array.c
└── dynamic_programming/        → fibonacci_dp.c
```

#### For **C++** Contributions:
```
CPP/
├── algorithms/sorting/              → merge_sort.cpp
├── data_structures/trees/           → binary_search_tree.cpp
├── object_oriented_programming/     → polymorphism_example.cpp
├── dynamic_programming/             → longest_common_subsequence.cpp
└── projects/                       → complete_application.cpp
```

#### For **Java** Contributions:
```
Java/
├── algorithms/graph_algorithms/     → DijkstraAlgorithm.java
├── data_structures/trees/           → AVLTree.java
├── dynamic_programming/             → CoinChange.java
└── projects/games/                 → TicTacToe.java
```

#### For **Python** Contributions:
```
Python/
├── algorithms/machine_learning/     → linear_regression.py
├── data_structures/graphs/          → graph_adjacency_list.py
├── projects/games/                 → snake_game.py
└── dynamic_programming/             → edit_distance.py
```

#### 🌍 **Adding a New Programming Language**

**We welcome contributions in ANY programming language!** Here's how to add a new language:

##### **Step 1: Create Language Directory Structure**
```
YourLanguage/                       # e.g., JavaScript/, Go/, Rust/, Kotlin/
├── README.md                      # Language-specific guide
├── algorithms/
│   ├── searching/                 → binary_search.ext
│   ├── sorting/                   → merge_sort.ext
│   ├── graph_algorithms/          → dijkstra.ext
│   ├── arrays/                    → array_operations.ext
│   ├── strings/                   → string_algorithms.ext
│   └── mathematical/              → math_algorithms.ext
├── data_structures/
│   ├── trees/                     → binary_tree.ext
│   ├── stacks/                    → stack.ext
│   ├── queues/                    → queue.ext
│   ├── graphs/                    → graph.ext
│   ├── heaps/                     → heap.ext
│   └── linked_lists/              → linked_list.ext
├── dynamic_programming/           → dp_solutions.ext
└── projects/                      # Optional: Complete applications
    ├── games/
    ├── data_analysis/
    └── web_development/
```

##### **Step 2: Create Language-Specific README**
Your `YourLanguage/README.md` should include:

```markdown
# YourLanguage Implementations

## 🚀 Getting Started

### Prerequisites
- YourLanguage version X.X or higher
- Package manager (if applicable)
- Any specific dependencies

### Running the Code
```bash
# Instructions to run/compile code
your-language filename.ext
```

## 📋 Naming Conventions
- Use language-specific naming: `camelCase`, `snake_case`, etc.
- File extensions: `.js`, `.go`, `.rs`, `.kt`, etc.

## 🧪 Testing
- How to run tests
- Testing framework used
- Example test commands

## 📚 Language-Specific Notes
- Any special considerations
- Performance notes
- Best practices for this language
```

##### **Step 3: Follow Code Standards**
- **Naming**: Use language-specific conventions
- **Documentation**: Include comprehensive comments
- **Testing**: Add test cases where applicable
- **Dependencies**: Keep external dependencies minimal
- **Performance**: Write efficient, idiomatic code

##### **Step 4: Popular Languages to Add**
Here are some highly requested languages:

| Language | Extension | Use Cases | Difficulty |
|----------|-----------|-----------|------------|
| **JavaScript** | `.js` | Web algorithms, Node.js | ⭐⭐ |
| **TypeScript** | `.ts` | Type-safe web development | ⭐⭐⭐ |
| **Go** | `.go` | Concurrent algorithms, systems | ⭐⭐⭐ |
| **Rust** | `.rs` | Memory-safe, high-performance | ⭐⭐⭐⭐ |
| **Kotlin** | `.kt` | Android, JVM algorithms | ⭐⭐⭐ |
| **Swift** | `.swift` | iOS, macOS development | ⭐⭐⭐ |
| **PHP** | `.php` | Web backend algorithms | ⭐⭐ |
| **Ruby** | `.rb` | Dynamic, expressive code | ⭐⭐ |
| **C#** | `.cs` | .NET framework algorithms | ⭐⭐⭐ |
| **Dart** | `.dart` | Flutter development | ⭐⭐ |
| **Scala** | `.scala` | Functional programming | ⭐⭐⭐⭐ |
| **R** | `.r` | Statistical algorithms | ⭐⭐⭐ |

##### **Step 5: Example Implementation Template**

```language
/*
 * Algorithm: [Algorithm Name]
 * Language: [Your Language]
 * Description: [Brief description]
 * Time Complexity: O(?)
 * Space Complexity: O(?)
 * Author: [Your Name]
 * Date: [Date]
 */

// Your implementation here
function/method algorithmName(parameters) {
    // Input validation

    // Algorithm implementation

    // Return result
}

// Test cases
function/method testAlgorithm() {
    // Test case 1
    // Test case 2
    // Edge cases
}

// Main function (if applicable)
```

## 📝 Code Standards

### General Standards

#### 1. **File Naming Conventions**
- **C**: `snake_case.c` → `binary_search.c`
- **C++**: `snake_case.cpp` → `quick_sort.cpp`
- **Java**: `PascalCase.java` → `BinarySearchTree.java`
- **Python**: `snake_case.py` → `bubble_sort.py`

#### 2. **Code Documentation**
Every file must include:
```python
"""
Algorithm: [Algorithm Name]
Description: [Brief description of what the algorithm does]
Time Complexity: O(?)
Space Complexity: O(?)
Author: [Your Name]
Date: [Date]
"""
```

#### 3. **Function Documentation**
```python
def algorithm_name(parameters):
    """
    Brief description of the function.

    Args:
        param1 (type): Description of parameter 1
        param2 (type): Description of parameter 2

    Returns:
        return_type: Description of return value

    Examples:
        >>> algorithm_name(example_input)
        expected_output

    Raises:
        ErrorType: Description of when this error occurs
    """
```

### Language-Specific Standards

#### **C Code Standards**
```c
/*
 * Algorithm: Binary Search
 * Description: Search for target in sorted array
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Performs binary search on sorted array
 * @param arr: Sorted array to search in
 * @param size: Size of the array
 * @param target: Value to search for
 * @return: Index if found, -1 otherwise
 */
int binary_search(int arr[], int size, int target) {
    // Input validation
    if (arr == NULL || size <= 0) {
        return -1;
    }

    // Implementation here
    // ...
}

// Test function
void test_binary_search() {
    int arr[] = {1, 3, 5, 7, 9};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Testing binary search...\n");
    // Test cases
}

int main() {
    test_binary_search();
    return 0;
}
```

#### **C++ Code Standards**
```cpp
/*
 * Algorithm: Quick Sort
 * Description: Efficient divide-and-conquer sorting algorithm
 * Time Complexity: O(n log n) average, O(n²) worst
 * Space Complexity: O(log n)
 */

#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Quick sort implementation using modern C++
 * @param arr Vector to be sorted
 * @param low Starting index
 * @param high Ending index
 */
template<typename T>
void quickSort(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

// Test function with modern C++ features
void testQuickSort() {
    std::vector<int> test_data = {64, 34, 25, 12, 22, 11, 90};

    std::cout << "Original array: ";
    for (const auto& elem : test_data) {
        std::cout << elem << " ";
    }

    quickSort(test_data, 0, test_data.size() - 1);

    std::cout << "\nSorted array: ";
    for (const auto& elem : test_data) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
```

#### **Java Code Standards**
```java
/**
 * Algorithm: Merge Sort
 * Description: Stable divide-and-conquer sorting algorithm
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 *
 * @author Your Name
 * @version 1.0
 * @since 2025-01-01
 */

import java.util.*;

public class MergeSort {

    /**
     * Sorts an array using merge sort algorithm.
     *
     * @param arr the array to be sorted
     * @throws IllegalArgumentException if array is null
     */
    public static void mergeSort(int[] arr) {
        if (arr == null) {
            throw new IllegalArgumentException("Array cannot be null");
        }

        if (arr.length <= 1) {
            return; // Already sorted
        }

        mergeSort(arr, 0, arr.length - 1);
    }

    private static void mergeSort(int[] arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    /**
     * Test the merge sort implementation.
     */
    public static void main(String[] args) {
        int[] testArray = {64, 34, 25, 12, 22, 11, 90};

        System.out.println("Original array: " + Arrays.toString(testArray));
        mergeSort(testArray);
        System.out.println("Sorted array: " + Arrays.toString(testArray));

        // Additional test cases
        testEdgeCases();
    }

    private static void testEdgeCases() {
        // Test empty array
        int[] emptyArray = {};
        mergeSort(emptyArray);
        assert emptyArray.length == 0;

        // Test single element
        int[] singleElement = {42};
        mergeSort(singleElement);
        assert singleElement[0] == 42;

        System.out.println("All tests passed!");
    }
}
```

#### **Python Code Standards**
```python
"""
Algorithm: Heap Sort
Description: Efficient in-place comparison-based sorting algorithm
Time Complexity: O(n log n)
Space Complexity: O(1)
Author: Your Name
Date: 2025-01-01
"""

from typing import List

def heap_sort(arr: List[int]) -> List[int]:
    """
    Sort an array using heap sort algorithm.

    Args:
        arr: List of integers to be sorted

    Returns:
        List[int]: Sorted array in ascending order

    Raises:
        TypeError: If input is not a list
        ValueError: If array contains non-integer values

    Examples:
        >>> heap_sort([64, 34, 25, 12, 22, 11, 90])
        [11, 12, 22, 25, 34, 64, 90]

        >>> heap_sort([])
        []

        >>> heap_sort([42])
        [42]
    """
    # Input validation
    if not isinstance(arr, list):
        raise TypeError("Input must be a list")

    if not arr:
        return []

    if not all(isinstance(x, int) for x in arr):
        raise ValueError("Array must contain only integers")

    # Create a copy to avoid modifying original
    result = arr.copy()

    # Implementation here
    # ...

    return result

def _heapify(arr: List[int], n: int, i: int) -> None:
    """Helper function to maintain heap property."""
    # Implementation
    pass

def main():
    """Test the heap sort implementation."""
    # Test cases
    test_cases = [
        [64, 34, 25, 12, 22, 11, 90],
        [1],
        [],
        [5, 5, 5, 5],
        [9, 8, 7, 6, 5, 4, 3, 2, 1]
    ]

    for i, test_case in enumerate(test_cases, 1):
        print(f"Test case {i}:")
        print(f"  Input: {test_case}")
        sorted_array = heap_sort(test_case)
        print(f"  Output: {sorted_array}")
        print(f"  Correct: {sorted_array == sorted(test_case)}")
        print()

if __name__ == "__main__":
    main()
```

## 🤖 Automated Quality Checks

We have automated workflows that will check your PR for quality and help you improve your contributions!

### 🔍 Duplicate Detection

Our **Duplicate Detection** workflow automatically checks if similar implementations already exist:

- **What it checks**: Compares your file names with existing files to find potential duplicates
- **When it runs**: Automatically on every PR
- **What happens**: If a potential duplicate is found, you'll receive a friendly comment explaining:
  - Which files appear similar
  - How to verify if it's truly a duplicate
  - Options to either improve existing code or explain why yours is different

**💡 Pro Tip**: Always search the repository before adding a new algorithm to avoid duplicates!

### 💎 Quality Checks

Our **Quality Checks** workflow ensures all contributions meet our standards:

#### What Gets Checked:

1. **✅ Algorithm Description** (Required)
   - Your code must explain what the algorithm does
   - Include the purpose and approach

2. **✅ Complexity Analysis** (Required)
   - Time complexity (e.g., `O(n log n)`)
   - Space complexity (e.g., `O(n)`)
   - Brief explanation of why

3. **✅ Comments** (Recommended)
   - Single file PRs: Minimum 3 comments
   - Multiple file PRs: Minimum 5 comments per file
   - Explain complex logic and key steps

4. **✅ Test Cases/Examples** (Recommended)
   - Demonstrate your code works
   - Show different input scenarios
   - Include edge cases

#### Single File vs Multiple Files:

**Single File Contributions** (More Lenient):
- Only 3 comments required (vs 5)
- Minimum 15 lines (vs 20)
- Won't receive warnings for minor issues
- Focus on critical requirements (description + complexity)

**Multiple File Contributions** (Stricter):
- All quality checks apply
- Higher standards for documentation
- Ensures consistency across files

#### What You'll Receive:

If your PR needs improvements, you'll get a **helpful comment** with:
- ✅ What's missing or needs improvement
- 📚 Why each requirement is important
- 💡 Example template showing best practices
- 🔧 Exactly how to fix the issues

**Note**: Quality checks are **educational, not blocking** - they help you improve, but won't fail your PR!

### 🚨 Error Explanations

If any workflow fails, you'll receive a **friendly explanation** with:

- 🔍 **What went wrong**: Clear explanation of the error
- 🔧 **How to fix it**: Step-by-step instructions
- 💡 **Common causes**: Why this error typically happens
- 📚 **Resources**: Links to documentation and examples

### 📊 How Comments Work:

All automated workflows **update existing comments** instead of spamming:
- ✅ One comment per workflow type
- ✅ Updates when you push new commits
- ✅ Always shows current status
- ✅ Clean, non-spammy PR discussions

## 🔄 Pull Request Process

### Before Creating a Pull Request

1. **Search for Duplicates**
   ```bash
   # Search the repository for similar implementations
   # Check the language folder to see what already exists
   ls CPP/algorithms/sorting/  # Example for C++ sorting algorithms
   ```

2. **Test Your Code**
   ```bash
   # For Python
   python your_algorithm.py

   # For Java
   javac YourAlgorithm.java && java YourAlgorithm

   # For C++
   g++ -o algorithm your_algorithm.cpp && ./algorithm

   # For C
   gcc -o algorithm your_algorithm.c && ./algorithm
   ```

3. **Check Code Quality**
   - ✅ No compilation errors
   - ✅ No runtime errors on test cases
   - ✅ Algorithm description included
   - ✅ Time & space complexity documented
   - ✅ Meaningful comments (3+ for single file, 5+ for multiple)
   - ✅ Test cases or examples included
   - ✅ Proper input validation
   - ✅ Clear variable names

4. **Update Documentation**
   - Add algorithm to appropriate README
   - Include complexity analysis
   - Provide usage examples

### Creating the Pull Request

1. **Create Feature Branch**
   ```bash
   git checkout -b feature/algorithm-name
   git add .
   git commit -m "Add [algorithm name] implementation in [language]"
   git push origin feature/algorithm-name
   ```

2. **Pull Request Template**
   ```markdown
   ## 📋 Pull Request Description

   ### What does this PR add?
   - [ ] New algorithm implementation
   - [ ] Data structure implementation
   - [ ] New programming language support
   - [ ] Language-specific README
   - [ ] Bug fix
   - [ ] Documentation improvement
   - [ ] Test cases

   ### Algorithm/Feature Details
   - **Name**: [Algorithm Name]
   - **Language**: [Programming Language]
   - **Category**: [e.g., Sorting, Searching, Graph, etc.]
   - **Time Complexity**: O(?)
   - **Space Complexity**: O(?)

   ### Testing
   - [ ] Code compiles without errors
   - [ ] All test cases pass
   - [ ] Edge cases handled
   - [ ] Documentation updated

   ### Screenshots (if applicable)
   [Add screenshots of output]

   ### Additional Notes
   [Any additional information about the implementation]
   ```

3. **PR Checklist**
   - [ ] Code follows language-specific style guidelines
   - [ ] File is in the correct directory
   - [ ] File name follows naming conventions
   - [ ] Algorithm is well-documented
   - [ ] Test cases are included
   - [ ] No duplicate implementations
   - [ ] Code is original work (if adapted, cite source)

## 👥 Community Guidelines

### Be Respectful
- Use welcoming and inclusive language
- Respect different viewpoints and experiences
- Accept constructive criticism gracefully
- Focus on what's best for the community

### Quality Over Quantity
- Aim for meaningful contributions
- Test your code thoroughly
- Write clear, readable code
- Include comprehensive documentation

### Collaborate Effectively
- Ask questions if you're unsure
- Help review others' pull requests
- Share knowledge and learn from others
- Be patient with newcomers

### Hacktoberfest Guidelines
- Make sure your PRs are meaningful, not spam
- Quality contributions are valued over quantity
- Help maintain the repository's standards
- Engage positively with the community

## 🆘 Getting Help

### 📞 Contact Information

**🛠️ Co-Admin & Maintainer**:
- **Twitter/X**: [@Karanjotdulay](https://x.com/Karanjotdulay)
- **GitHub**: [@Karanjot786](https://github.com/Karanjot786/)

### Where to Ask Questions
1. **Direct Contact**: Reach out to [@Karanjotdulay](https://x.com/Karanjotdulay) on Twitter/X for quick questions
2. **GitHub Issues**: For bugs, feature requests, or general questions
3. **Pull Request Comments**: For specific code review questions
4. **Discussions**: For broader community discussions

### Common Issues and Solutions

#### **Issue**: "I don't know where to put my algorithm"
**Solution**: Check the [Repository Structure](#-repository-structure) section and choose the appropriate language and category.

#### **Issue**: "My code doesn't compile"
**Solution**: Check the [Code Standards](#-code-standards) section for language-specific requirements.

#### **Issue**: "I want to contribute but don't know what to implement"
**Solution**: Check open issues labeled "good first issue" or "help wanted".

#### **Issue**: "My PR was rejected"
**Solution**: Read the feedback, make necessary changes, and resubmit. Don't take it personally!

## 🎉 Recognition

Contributors will be recognized through:
- **README Hall of Fame**: Top contributors featured in README
- **Monthly Highlights**: Featured contributors each month
- **Hacktoberfest Completion**: Special recognition for Hacktoberfest participants

## 📜 Code of Conduct

By participating in this project, you agree to abide by our Code of Conduct:
- Be respectful and inclusive
- No harassment, discrimination, or offensive behavior
- Focus on constructive feedback
- Help create a welcoming environment for all

---

**Thank you for contributing to the DSA Code Repository! Your contributions help make this a valuable resource for developers worldwide.** 🚀

**Happy Coding and Happy Hacktoberfest 2025!** ✨