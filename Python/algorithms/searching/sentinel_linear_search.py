"""
Sentinel Linear Search Algorithm

Description: An optimized version of linear search that uses a sentinel value 
to eliminate the boundary check in each iteration. The last element is replaced 
with the target value, ensuring the search always terminates without checking 
the array index bounds repeatedly.

Time Complexity: O(n) - In worst case, scans entire array once
Space Complexity: O(1) - Uses constant extra space (only a few variables)

Advantages:
- Reduces comparisons by eliminating index boundary checks
- More efficient in low-level languages
- Simple optimization over standard linear search

Use Cases:
- Unsorted arrays where binary search cannot be used
- Educational purposes to demonstrate optimization techniques
- Scenarios where reducing comparisons is critical
"""

def sentinel_linear_search(arr, target):
    """
    Search for target in array using sentinel technique.
    
    Args:
        arr: List of elements to search through
        target: Element to find in the array
    
    Returns:
        int: Index of target if found, -1 if not found
    """
    n = len(arr)
    
    # Handle empty array case
    if n == 0:
        return -1
    
    # Store last element and set sentinel
    last_element = arr[-1]
    arr[-1] = target  # Set sentinel
    
    i = 0
    # Search without boundary checks - sentinel guarantees termination
    while arr[i] != target:
        i += 1
    
    # Restore original last element
    arr[-1] = last_element
    
    # Check if element was found (before sentinel position)
    if i < n - 1 or last_element == target:
        return i
    else:
        return -1

def main():
    """Test and demonstrate Sentinel Linear Search with various cases"""
    print("=" * 50)
    print("      SENTINEL LINEAR SEARCH")
    print("=" * 50)
    
    # Comprehensive test cases
    test_cases = [
        # (array, target, expected_index, description)
        ([2, 5, 8, 12, 16, 23, 38, 45, 67], 23, 5, "Normal case - element in middle"),
        ([1, 3, 5, 7, 9, 11], 7, 3, "Normal case - element found"),
        ([10, 20, 30, 40, 50], 60, -1, "Element not in array"),
        ([42], 42, 0, "Single element array - element found"),
        ([42], 100, -1, "Single element array - element not found"),
        ([], 5, -1, "Empty array"),
        ([5, 3, 8, 1, 9], 1, 3, "Unsorted array"),
        ([1, 2, 3, 4, 5], 5, 4, "Element at last position"),
        ([1, 2, 3, 4, 5], 1, 0, "Element at first position"),
    ]
    
    passed = 0
    for arr, target, expected, description in test_cases:
        arr_copy = arr.copy()  # Preserve original
        result = sentinel_linear_search(arr_copy, target)
        
        status = "✓ PASS" if result == expected else "✗ FAIL"
        print(f"\n{status}: {description}")
        print(f"   Array: {arr}, Target: {target}")
        print(f"   Expected: {expected}, Got: {result}")
        
        # Verify array integrity
        assert arr_copy == arr, "Array was modified!"
        
        if result == expected:
            passed += 1
    
    print(f"\n{'='*40}")
    print(f"RESULTS: {passed}/{len(test_cases)} tests passed")
    print(f"{'='*40}")

def performance_comparison():
    """
    Compare performance between standard and sentinel linear search.
    Note: In Python, the performance difference may be minimal due to
    interpreter overhead, but the algorithm concept remains valuable.
    """
    import time
    import random
    
    # Create test data
    size = 10000
    test_arr = [random.randint(1, 100000) for _ in range(size)]
    target = test_arr[-1]  # Worst case scenario
    
    # Standard Linear Search
    start = time.time()
    result_standard = -1
    for i in range(len(test_arr)):
        if test_arr[i] == target:
            result_standard = i
            break
    time_standard = time.time() - start
    
    # Sentinel Linear Search
    start = time.time()
    result_sentinel = sentinel_linear_search(test_arr.copy(), target)
    time_sentinel = time.time() - start
    
    print(f"\n{'='*40}")
    print("PERFORMANCE COMPARISON (Worst Case)")
    print(f"{'='*40}")
    print(f"Array size: {size}")
    print(f"Standard Search: {time_standard:.6f}s")
    print(f"Sentinel Search: {time_sentinel:.6f}s")
    print(f"Results match: {result_standard == result_sentinel}")

if __name__ == "__main__":
    main()
    performance_comparison()
