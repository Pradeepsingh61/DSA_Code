"""
Algorithm: Subset Sum Problem
Description: Find if there exists a subset with given sum using backtracking
Time Complexity: O(2^n) in worst case where n is array length
Space Complexity: O(n) for recursion stack
Author: DSA Code Repository
Date: 2025-10-02
"""

def subset_sum_exists(arr, target_sum):
    """
    Check if there exists a subset with the given sum.
    
    Args:
        arr: List of positive integers
        target_sum: Target sum to achieve
        
    Returns:
        bool: True if subset exists, False otherwise
        
    Examples:
        >>> subset_sum_exists([3, 34, 4, 12, 5, 2], 9)
        True
        >>> subset_sum_exists([3, 34, 4, 12, 5, 2], 30)
        False
    """
    def backtrack(index, current_sum):
        """
        Backtracking helper function.
        
        Args:
            index: Current index in the array
            current_sum: Current sum achieved
            
        Returns:
            bool: True if target sum can be achieved
        """
        # Base case: target sum achieved
        if current_sum == target_sum:
            return True
        
        # Base case: exceeded target or reached end
        if current_sum > target_sum or index >= len(arr):
            return False
        
        # Include current element
        if backtrack(index + 1, current_sum + arr[index]):
            return True
        
        # Exclude current element
        if backtrack(index + 1, current_sum):
            return True
        
        return False
    
    return backtrack(0, 0)

def find_subset_with_sum(arr, target_sum):
    """
    Find one subset that achieves the target sum.
    
    Args:
        arr: List of positive integers
        target_sum: Target sum to achieve
        
    Returns:
        list: Subset that sums to target, or None if no such subset exists
    """
    def backtrack(index, current_sum, current_subset):
        """Find subset with backtracking."""
        if current_sum == target_sum:
            return current_subset[:]
        
        if current_sum > target_sum or index >= len(arr):
            return None
        
        # Include current element
        current_subset.append(arr[index])
        result = backtrack(index + 1, current_sum + arr[index], current_subset)
        if result is not None:
            return result
        current_subset.pop()  # Backtrack
        
        # Exclude current element
        result = backtrack(index + 1, current_sum, current_subset)
        return result
    
    return backtrack(0, 0, [])

def find_all_subsets_with_sum(arr, target_sum):
    """
    Find all subsets that achieve the target sum.
    
    Args:
        arr: List of positive integers
        target_sum: Target sum to achieve
        
    Returns:
        list: List of all subsets that sum to target
    """
    all_subsets = []
    
    def backtrack(index, current_sum, current_subset):
        """Find all subsets with backtracking."""
        if current_sum == target_sum:
            all_subsets.append(current_subset[:])
            return
        
        if current_sum > target_sum or index >= len(arr):
            return
        
        # Include current element
        current_subset.append(arr[index])
        backtrack(index + 1, current_sum + arr[index], current_subset)
        current_subset.pop()  # Backtrack
        
        # Exclude current element
        backtrack(index + 1, current_sum, current_subset)
    
    backtrack(0, 0, [])
    return all_subsets

def count_subsets_with_sum(arr, target_sum):
    """
    Count the number of subsets with the given sum.
    
    Args:
        arr: List of positive integers
        target_sum: Target sum to achieve
        
    Returns:
        int: Number of subsets that sum to target
    """
    def backtrack(index, current_sum):
        """Count subsets with backtracking."""
        if current_sum == target_sum:
            return 1
        
        if current_sum > target_sum or index >= len(arr):
            return 0
        
        # Include current element + Exclude current element
        return (backtrack(index + 1, current_sum + arr[index]) + 
                backtrack(index + 1, current_sum))
    
    return backtrack(0, 0)

def subset_sum_closest(arr, target_sum):
    """
    Find the subset sum closest to the target sum.
    
    Args:
        arr: List of positive integers
        target_sum: Target sum
        
    Returns:
        tuple: (closest_sum, subset_achieving_closest_sum)
    """
    best_sum = 0
    best_subset = []
    
    def backtrack(index, current_sum, current_subset):
        """Find closest sum with backtracking."""
        nonlocal best_sum, best_subset
        
        # Update best if current sum is closer to target
        if abs(current_sum - target_sum) < abs(best_sum - target_sum):
            best_sum = current_sum
            best_subset = current_subset[:]
        
        if index >= len(arr) or current_sum >= target_sum:
            return
        
        # Include current element
        current_subset.append(arr[index])
        backtrack(index + 1, current_sum + arr[index], current_subset)
        current_subset.pop()  # Backtrack
        
        # Exclude current element
        backtrack(index + 1, current_sum, current_subset)
    
    backtrack(0, 0, [])
    return best_sum, best_subset

def equal_sum_partition(arr):
    """
    Check if array can be partitioned into two subsets with equal sum.
    
    Args:
        arr: List of positive integers
        
    Returns:
        tuple: (bool, subset1, subset2) - True if partition exists with the two subsets
    """
    total_sum = sum(arr)
    
    # If total sum is odd, partition is impossible
    if total_sum % 2 != 0:
        return False, [], []
    
    target = total_sum // 2
    subset1 = find_subset_with_sum(arr, target)
    
    if subset1:
        # Find subset2 by removing subset1 elements
        remaining = arr[:]
        for element in subset1:
            remaining.remove(element)
        return True, subset1, remaining
    
    return False, [], []

def print_subset_analysis(arr, target_sum):
    """Print comprehensive analysis of subset sum problem."""
    print(f"\nSubset Sum Analysis for array {arr}, target sum: {target_sum}")
    print("-" * 60)
    
    # Check existence
    exists = subset_sum_exists(arr, target_sum)
    print(f"Subset with sum {target_sum} exists: {exists}")
    
    if exists:
        # Find one subset
        subset = find_subset_with_sum(arr, target_sum)
        print(f"One such subset: {subset} (sum: {sum(subset)})")
        
        # Count all subsets
        count = count_subsets_with_sum(arr, target_sum)
        print(f"Total number of subsets with sum {target_sum}: {count}")
        
        # Find all subsets (if count is reasonable)
        if count <= 10:
            all_subsets = find_all_subsets_with_sum(arr, target_sum)
            print(f"All subsets: {all_subsets}")
    
    # Find closest sum
    closest_sum, closest_subset = subset_sum_closest(arr, target_sum)
    print(f"Closest achievable sum: {closest_sum}")
    print(f"Subset achieving closest sum: {closest_subset}")

def main():
    """Test the subset sum algorithms with various examples."""
    print("Subset Sum Problem using Backtracking")
    print("=" * 50)
    
    # Test case 1: Basic subset sum
    print("Test Case 1: Basic Subset Sum")
    arr1 = [3, 34, 4, 12, 5, 2]
    print_subset_analysis(arr1, 9)
    print_subset_analysis(arr1, 30)
    
    # Test case 2: Multiple solutions
    print("\n" + "=" * 50)
    print("Test Case 2: Multiple Solutions")
    arr2 = [1, 2, 3, 4, 5]
    print_subset_analysis(arr2, 6)
    
    # Test case 3: Equal sum partition
    print("\n" + "=" * 50)
    print("Test Case 3: Equal Sum Partition")
    
    test_arrays = [
        [1, 5, 11, 5],
        [1, 2, 3, 5],
        [3, 1, 1, 2, 2, 1]
    ]
    
    for arr in test_arrays:
        can_partition, subset1, subset2 = equal_sum_partition(arr)
        print(f"\nArray: {arr}")
        print(f"Can be partitioned into equal sum subsets: {can_partition}")
        if can_partition:
            print(f"Subset 1: {subset1} (sum: {sum(subset1)})")
            print(f"Subset 2: {subset2} (sum: {sum(subset2)})")
    
    # Test case 4: Large numbers
    print("\n" + "=" * 50)
    print("Test Case 4: Larger Numbers")
    arr3 = [10, 20, 15, 5, 25, 30]
    targets = [35, 50, 100]
    
    for target in targets:
        print(f"\nTarget sum: {target}")
        exists = subset_sum_exists(arr3, target)
        print(f"Exists: {exists}")
        if exists:
            subset = find_subset_with_sum(arr3, target)
            print(f"Subset: {subset}")
    
    # Test case 5: Edge cases
    print("\n" + "=" * 50)
    print("Test Case 5: Edge Cases")
    
    # Empty array
    print("Empty array, target 0:", subset_sum_exists([], 0))
    print("Empty array, target 5:", subset_sum_exists([], 5))
    
    # Single element
    print("Single element [5], target 5:", subset_sum_exists([5], 5))
    print("Single element [5], target 3:", subset_sum_exists([5], 3))
    
    # All elements needed
    arr4 = [1, 2, 3]
    target_all = sum(arr4)
    print(f"Array {arr4}, target {target_all}:", subset_sum_exists(arr4, target_all))
    subset_all = find_subset_with_sum(arr4, target_all)
    print(f"Subset using all elements: {subset_all}")

if __name__ == "__main__":
    main()