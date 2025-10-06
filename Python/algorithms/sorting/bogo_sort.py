import random

def is_sorted(arr):
    """
    Check if array is sorted in ascending order
    """
    for i in range(len(arr) - 1):
        if arr[i] > arr[i + 1]:
            return False
    return True


def bogo_sort(arr, max_iterations=10000):
    """
    Bogo Sort Algorithm (also called Permutation Sort or Stupid Sort)
    Time Complexity: O((n+1)!) average, O(∞) worst case, O(n) best case
    Space Complexity: O(1)
    
    WARNING: This is extremely inefficient! Used only for educational purposes.
    The algorithm randomly shuffles the array until it happens to be sorted.
    
    For safety, this implementation has a max_iterations limit.
    """
    attempts = 0
    
    while not is_sorted(arr) and attempts < max_iterations:
        random.shuffle(arr)
        attempts += 1
    
    if attempts >= max_iterations:
        print(f"Warning: Reached maximum iterations ({max_iterations})")
        print("Array may not be fully sorted!")
    
    return arr, attempts


def bogo_sort_deterministic(arr):
    """
    Deterministic Bogo Sort - tries all permutations systematically
    Still extremely inefficient but guarantees to finish
    """
    from itertools import permutations
    
    n = len(arr)
    attempts = 0
    
    for perm in permutations(arr):
        attempts += 1
        if list(perm) == sorted(arr):
            return list(perm), attempts
    
    return arr, attempts


def bogo_sort_with_tracking(arr, max_iterations=10000):
    """
    Bogo Sort with attempt tracking for visualization
    """
    attempts = 0
    
    print(f"Starting array: {arr}")
    print(f"Target (sorted): {sorted(arr)}\n")
    
    while not is_sorted(arr) and attempts < max_iterations:
        random.shuffle(arr)
        attempts += 1
        
        # Show progress every 100 attempts
        if attempts % 100 == 0:
            print(f"Attempt {attempts}: {arr}")
    
    if is_sorted(arr):
        print(f"\nSuccess! Sorted in {attempts} attempts")
    else:
        print(f"\nFailed after {attempts} attempts")
    
    return arr, attempts


def bogo_bogo_sort(arr, max_iterations=1000):
    """
    Bogo Bogo Sort - Even more inefficient variant!
    Checks if sorted using another bogo sort
    
    WARNING: Extremely slow! Use only with very small arrays (2-3 elements)
    """
    attempts = 0
    
    def bogo_is_sorted(check_arr, max_check=100):
        """Check if sorted using bogo sort logic"""
        temp = check_arr.copy()
        for _ in range(max_check):
            if temp == sorted(check_arr):
                return True
            random.shuffle(temp)
        return temp == sorted(check_arr)
    
    while not bogo_is_sorted(arr) and attempts < max_iterations:
        random.shuffle(arr)
        attempts += 1
    
    return arr, attempts


def calculate_expected_attempts(n):
    """
    Calculate expected number of attempts for array of size n
    Expected attempts = n! (factorial of n)
    """
    import math
    return math.factorial(n)


# Example usage
if __name__ == "__main__":
    # WARNING: Only use small arrays with Bogo Sort!
    
    # Test case 1 - Very small array
    arr1 = [3, 2, 1]
    print("Original array:", arr1)
    expected = calculate_expected_attempts(len(arr1))
    print(f"Expected attempts: {expected}")
    sorted_arr, attempts = bogo_sort(arr1.copy())
    print("Sorted array:", sorted_arr)
    print(f"Actual attempts: {attempts}\n")
    
    # Test case 2
    arr2 = [4, 1, 3, 2]
    print("Original array:", arr2)
    expected = calculate_expected_attempts(len(arr2))
    print(f"Expected attempts: {expected}")
    sorted_arr, attempts = bogo_sort(arr2.copy())
    print("Sorted array:", sorted_arr)
    print(f"Actual attempts: {attempts}\n")
    
    # Test case 3 - Already sorted (best case)
    arr3 = [1, 2, 3]
    print("Already sorted:", arr3)
    sorted_arr, attempts = bogo_sort(arr3.copy())
    print("Sorted array:", sorted_arr)
    print(f"Attempts: {attempts}\n")
    
    # Test case 4 - Deterministic version
    arr4 = [3, 1, 2]
    print("Using deterministic bogo sort:")
    print("Original array:", arr4)
    sorted_arr, attempts = bogo_sort_deterministic(arr4.copy())
    print("Sorted array:", sorted_arr)
    print(f"Permutations checked: {attempts}\n")
    
    # Test case 5 - With tracking (small array only!)
    arr5 = [2, 1, 3]
    print("With tracking:")
    bogo_sort_with_tracking(arr5.copy(), max_iterations=500)
    
    # Complexity warning
    print("\n" + "="*50)
    print("COMPLEXITY WARNING:")
    print("Array size | Expected attempts")
    print("-"*50)
    for size in range(1, 8):
        print(f"    {size}      |  {calculate_expected_attempts(size):,}")
    print("="*50)
    print("\nNever use Bogo Sort with arrays larger than 5 elements!")
