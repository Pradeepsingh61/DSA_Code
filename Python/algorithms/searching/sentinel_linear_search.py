# Sentinel Linear Search

def sentinel_linear_search(arr, target):
    """
    Sentinel Linear Search implementation.
    Uses a sentinel value to reduce comparisons in linear search.
    
    Args:
        arr: List of elements to search
        target: Element to find
    
    Returns:
        Index of target if found, -1 otherwise
    """
    n = len(arr)
    
    # If array is empty
    if n == 0:
        return -1
    
    # Store last element and replace it with target (sentinel)
    last = arr[-1]
    arr[-1] = target
    
    i = 0
    # No need to check i < n in each iteration
    while arr[i] != target:
        i += 1
    
    # Restore the last element
    arr[-1] = last
    
    # Check if element was found
    if i < n - 1 or arr[n - 1] == target:
        return i
    else:
        return -1

def main():
    """Demonstrate Sentinel Linear Search with examples"""
    print("=" * 50)
    print("      SENTINEL LINEAR SEARCH")
    print("=" * 50)
    
    # Test cases
    test_arrays = [
        [2, 5, 8, 12, 16, 23, 38, 45, 67],
        [1, 3, 5, 7, 9, 11],
        [10, 20, 30, 40, 50],
        [42],
        []
    ]
    
    test_targets = [23, 7, 60, 42, 5]
    
    for i, (arr, target) in enumerate(zip(test_arrays, test_targets)):
        print(f"\nTest Case {i + 1}:")
        print(f"Array: {arr}")
        print(f"Target: {target}")
        
        # Create a copy to preserve original array
        arr_copy = arr.copy()
        result = sentinel_linear_search(arr_copy, target)
        
        if result != -1:
            print(f"✓ Found at index: {result}")
        else:
            print("✗ Not found")
        
        # Verify array is unchanged
        print(f"Array after search: {arr_copy}")
        assert arr_copy == arr, "Array was modified!"

def benchmark_comparison():
    """Compare standard vs sentinel linear search"""
    import time
    import random
    
    # Create large array for benchmarking
    size = 10000
    test_arr = [random.randint(1, 100000) for _ in range(size)]
    target = test_arr[-1]  # Worst case - search for last element
    
    # Standard Linear Search
    start_time = time.time()
    found_standard = -1
    for i in range(len(test_arr)):
        if test_arr[i] == target:
            found_standard = i
            break
    standard_time = time.time() - start_time
    
    # Sentinel Linear Search
    start_time = time.time()
    found_sentinel = sentinel_linear_search(test_arr.copy(), target)
    sentinel_time = time.time() - start_time
    
    print(f"\n{'='*40}")
    print("PERFORMANCE COMPARISON")
    print(f"{'='*40}")
    print(f"Array size: {size}")
    print(f"Standard Linear Search: {standard_time:.6f} seconds")
    print(f"Sentinel Linear Search: {sentinel_time:.6f} seconds")
    print(f"Both found at index: {found_standard}")
    assert found_standard == found_sentinel

if __name__ == "__main__":
    main()
    benchmark_comparison()
