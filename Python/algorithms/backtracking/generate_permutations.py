"""
Algorithm: Generate All Permutations
Description: Generate all permutations of a given array/string using backtracking
Time Complexity: O(n! * n) where n is the length of input
Space Complexity: O(n) for recursion stack
Author: DSA Code Repository
Date: 2025-10-02
"""

def permute(nums):
    """
    Generate all permutations of a list of numbers.
    
    Args:
        nums: List of integers
        
    Returns:
        list: List of all permutations
        
    Examples:
        >>> permute([1, 2, 3])
        [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
    """
    result = []
    
    def backtrack(current_permutation):
        """Backtracking helper function."""
        # Base case: permutation is complete
        if len(current_permutation) == len(nums):
            result.append(current_permutation[:])
            return
        
        # Try each unused number
        for num in nums:
            if num not in current_permutation:
                # Make choice
                current_permutation.append(num)
                
                # Recursive call
                backtrack(current_permutation)
                
                # Backtrack
                current_permutation.pop()
    
    backtrack([])
    return result

def permute_unique(nums):
    """
    Generate all unique permutations of a list that may contain duplicates.
    
    Args:
        nums: List of integers (may contain duplicates)
        
    Returns:
        list: List of all unique permutations
    """
    result = []
    nums.sort()  # Sort to handle duplicates
    used = [False] * len(nums)
    
    def backtrack(current_permutation):
        """Backtracking for unique permutations."""
        if len(current_permutation) == len(nums):
            result.append(current_permutation[:])
            return
        
        for i in range(len(nums)):
            # Skip used elements
            if used[i]:
                continue
            
            # Skip duplicates: if current element is same as previous
            # and previous is not used, skip current
            if i > 0 and nums[i] == nums[i-1] and not used[i-1]:
                continue
            
            # Make choice
            used[i] = True
            current_permutation.append(nums[i])
            
            # Recursive call
            backtrack(current_permutation)
            
            # Backtrack
            used[i] = False
            current_permutation.pop()
    
    backtrack([])
    return result

def permute_string(s):
    """
    Generate all permutations of a string.
    
    Args:
        s: Input string
        
    Returns:
        list: List of all permutations as strings
    """
    chars = list(s)
    result = []
    
    def backtrack(current_chars, remaining_chars):
        """Backtracking for string permutations."""
        if not remaining_chars:
            result.append(''.join(current_chars))
            return
        
        for i, char in enumerate(remaining_chars):
            # Make choice
            new_current = current_chars + [char]
            new_remaining = remaining_chars[:i] + remaining_chars[i+1:]
            
            # Recursive call
            backtrack(new_current, new_remaining)
    
    backtrack([], chars)
    return result

def permute_with_repetition(elements, length):
    """
    Generate all permutations with repetition allowed.
    
    Args:
        elements: List of available elements
        length: Length of each permutation
        
    Returns:
        list: List of all permutations with repetition
    """
    result = []
    
    def backtrack(current_permutation):
        """Backtracking with repetition."""
        if len(current_permutation) == length:
            result.append(current_permutation[:])
            return
        
        for element in elements:
            # Make choice (repetition allowed)
            current_permutation.append(element)
            
            # Recursive call
            backtrack(current_permutation)
            
            # Backtrack
            current_permutation.pop()
    
    backtrack([])
    return result

def next_permutation(nums):
    """
    Find the next lexicographically greater permutation.
    
    Args:
        nums: List of integers
        
    Returns:
        list: Next permutation, or sorted array if no next permutation exists
    """
    # Find the largest index i such that nums[i] < nums[i + 1]
    i = len(nums) - 2
    while i >= 0 and nums[i] >= nums[i + 1]:
        i -= 1
    
    if i == -1:
        # No next permutation, return sorted array
        return sorted(nums)
    
    # Find the largest index j such that nums[i] < nums[j]
    j = len(nums) - 1
    while nums[j] <= nums[i]:
        j -= 1
    
    # Swap nums[i] and nums[j]
    nums[i], nums[j] = nums[j], nums[i]
    
    # Reverse the suffix starting at nums[i + 1]
    nums[i + 1:] = reversed(nums[i + 1:])
    
    return nums

def permutation_rank(permutation, elements):
    """
    Find the rank of a given permutation among all permutations.
    
    Args:
        permutation: The permutation to find rank for
        elements: List of all available elements
        
    Returns:
        int: Rank of the permutation (1-indexed)
    """
    import math
    
    elements = sorted(elements)
    n = len(elements)
    rank = 1
    
    for i in range(n):
        # Count elements smaller than current element
        smaller_count = 0
        for j in range(len(elements)):
            if elements[j] < permutation[i]:
                smaller_count += 1
        
        # Add to rank
        rank += smaller_count * math.factorial(n - i - 1)
        
        # Remove used element
        elements.remove(permutation[i])
    
    return rank

def kth_permutation(elements, k):
    """
    Find the kth permutation of given elements.
    
    Args:
        elements: List of elements
        k: Position of permutation (1-indexed)
        
    Returns:
        list: The kth permutation
    """
    import math
    
    elements = sorted(elements)
    n = len(elements)
    result = []
    k -= 1  # Convert to 0-indexed
    
    for i in range(n):
        factorial = math.factorial(n - i - 1)
        index = k // factorial
        result.append(elements.pop(index))
        k %= factorial
    
    return result

def count_permutations_with_condition(nums, condition_func):
    """
    Count permutations that satisfy a given condition.
    
    Args:
        nums: List of numbers
        condition_func: Function that takes a permutation and returns True/False
        
    Returns:
        int: Number of permutations satisfying the condition
    """
    count = 0
    
    def backtrack(current_permutation):
        """Backtracking to count valid permutations."""
        nonlocal count
        
        if len(current_permutation) == len(nums):
            if condition_func(current_permutation):
                count += 1
            return
        
        for num in nums:
            if num not in current_permutation:
                current_permutation.append(num)
                backtrack(current_permutation)
                current_permutation.pop()
    
    backtrack([])
    return count

def main():
    """Test the permutation algorithms with various examples."""
    print("Generate Permutations using Backtracking")
    print("=" * 45)
    
    # Test case 1: Basic permutations
    print("Test Case 1: Basic Permutations")
    nums1 = [1, 2, 3]
    perms1 = permute(nums1)
    print(f"Permutations of {nums1}:")
    for i, perm in enumerate(perms1, 1):
        print(f"  {i}: {perm}")
    print(f"Total: {len(perms1)} permutations")
    
    # Test case 2: Permutations with duplicates
    print("\n" + "="*45)
    print("Test Case 2: Unique Permutations (with duplicates)")
    nums2 = [1, 1, 2]
    perms2 = permute_unique(nums2)
    print(f"Unique permutations of {nums2}:")
    for i, perm in enumerate(perms2, 1):
        print(f"  {i}: {perm}")
    print(f"Total: {len(perms2)} unique permutations")
    
    # Test case 3: String permutations
    print("\n" + "="*45)
    print("Test Case 3: String Permutations")
    string = "ABC"
    str_perms = permute_string(string)
    print(f"Permutations of '{string}':")
    for i, perm in enumerate(str_perms, 1):
        print(f"  {i}: {perm}")
    
    # Test case 4: Permutations with repetition
    print("\n" + "="*45)
    print("Test Case 4: Permutations with Repetition")
    elements = ['A', 'B']
    length = 3
    rep_perms = permute_with_repetition(elements, length)
    print(f"Permutations of {elements} with repetition, length {length}:")
    for i, perm in enumerate(rep_perms, 1):
        print(f"  {i}: {perm}")
    print(f"Total: {len(rep_perms)} permutations")
    
    # Test case 5: Next permutation
    print("\n" + "="*45)
    print("Test Case 5: Next Permutation")
    test_arrays = [[1, 2, 3], [3, 2, 1], [1, 1, 5], [1, 3, 2]]
    
    for arr in test_arrays:
        original = arr[:]
        next_perm = next_permutation(arr)
        print(f"Next permutation of {original}: {next_perm}")
    
    # Test case 6: Permutation rank and kth permutation
    print("\n" + "="*45)
    print("Test Case 6: Permutation Rank and Kth Permutation")
    
    elements = [1, 2, 3, 4]
    test_perm = [2, 1, 4, 3]
    rank = permutation_rank(test_perm, elements)
    print(f"Rank of permutation {test_perm} among {elements}: {rank}")
    
    k = 10
    kth_perm = kth_permutation(elements[:], k)  # Pass copy since function modifies list
    print(f"The {k}th permutation of {elements}: {kth_perm}")
    
    # Test case 7: Conditional permutations
    print("\n" + "="*45)
    print("Test Case 7: Conditional Permutations")
    
    # Count permutations where first element is smaller than last
    def first_smaller_than_last(perm):
        return perm[0] < perm[-1]
    
    nums3 = [1, 2, 3, 4]
    count = count_permutations_with_condition(nums3, first_smaller_than_last)
    print(f"Permutations of {nums3} where first < last: {count}")
    
    # Count ascending permutations
    def is_ascending(perm):
        return all(perm[i] < perm[i+1] for i in range(len(perm)-1))
    
    count_asc = count_permutations_with_condition(nums3, is_ascending)
    print(f"Ascending permutations of {nums3}: {count_asc}")
    
    # Test case 8: Performance comparison
    print("\n" + "="*45)
    print("Test Case 8: Performance Analysis")
    
    import time
    import math
    
    sizes = [3, 4, 5, 6]
    for size in sizes:
        test_nums = list(range(1, size + 1))
        
        start_time = time.time()
        perms = permute(test_nums)
        end_time = time.time()
        
        expected = math.factorial(size)
        actual = len(perms)
        time_taken = end_time - start_time
        
        print(f"Size {size}: Expected {expected}, Got {actual}, Time: {time_taken:.4f}s")

if __name__ == "__main__":
    main()