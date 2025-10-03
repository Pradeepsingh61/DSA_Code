def flip(arr, k):
    """
    Reverses elements from index 0 to k
    This simulates flipping a stack of pancakes
    """
    left = 0
    while left < k:
        arr[left], arr[k] = arr[k], arr[left]
        left += 1
        k -= 1


def find_max_index(arr, n):
    """
    Finds the index of the maximum element in arr[0:n]
    """
    max_idx = 0
    for i in range(1, n):
        if arr[i] > arr[max_idx]:
            max_idx = i
    return max_idx


def pancake_sort(arr):
    """
    Pancake Sort Algorithm
    Time Complexity: O(n^2)
    Space Complexity: O(1)
    
    Unlike traditional sorting, pancake sort can only perform one operation:
    flip the array from position 0 to position i. The goal is to sort by
    repeatedly finding the maximum element and flipping it to the end.
    
    Algorithm:
    1. Find the maximum element in current unsorted portion
    2. Flip it to the beginning (if not already there)
    3. Flip it to its correct position at the end
    4. Reduce the size of unsorted portion by 1
    5. Repeat until sorted
    """
    n = len(arr)
    
    # Reduce the problem size by 1 in each iteration
    for curr_size in range(n, 1, -1):
        # Find index of maximum element in arr[0:curr_size]
        max_idx = find_max_index(arr, curr_size)
        
        # If maximum is not already at the end
        if max_idx != curr_size - 1:
            # Move maximum to beginning if not already there
            if max_idx != 0:
                flip(arr, max_idx)
            
            # Move maximum to its correct position
            flip(arr, curr_size - 1)
    
    return arr


def pancake_sort_with_steps(arr):
    """
    Pancake Sort with visualization of each flip
    """
    n = len(arr)
    flip_count = 0
    
    print(f"Starting array: {arr}\n")
    
    for curr_size in range(n, 1, -1):
        max_idx = find_max_index(arr, curr_size)
        
        if max_idx != curr_size - 1:
            if max_idx != 0:
                flip_count += 1
                flip(arr, max_idx)
                print(f"Flip {flip_count}: Flip first {max_idx + 1} elements")
                print(f"Result: {arr}")
            
            flip_count += 1
            flip(arr, curr_size - 1)
            print(f"Flip {flip_count}: Flip first {curr_size} elements")
            print(f"Result: {arr}\n")
    
    print(f"Total flips: {flip_count}")
    return arr


def count_flips(arr):
    """
    Returns the minimum number of flips needed to sort the array
    """
    temp = arr.copy()
    n = len(temp)
    flip_count = 0
    
    for curr_size in range(n, 1, -1):
        max_idx = find_max_index(temp, curr_size)
        
        if max_idx != curr_size - 1:
            if max_idx != 0:
                flip(temp, max_idx)
                flip_count += 1
            
            flip(temp, curr_size - 1)
            flip_count += 1
    
    return flip_count


# Example usage
if __name__ == "__main__":
    # Test case 1
    arr1 = [23, 10, 20, 11, 12, 6, 7]
    print("Original array:", arr1)
    print("Sorted array:", pancake_sort(arr1.copy()))
    print()
    
    # Test case 2 - With visualization
    arr2 = [3, 2, 4, 1]
    print("Sorting with visualization:")
    pancake_sort_with_steps(arr2.copy())
    print()
    
    # Test case 3
    arr3 = [64, 34, 25, 12, 22, 11, 90]
    print("Original array:", arr3)
    flips = count_flips(arr3)
    print(f"Minimum flips needed: {flips}")
    print("Sorted array:", pancake_sort(arr3.copy()))
    print()
    
    # Test case 4 - Already sorted
    arr4 = [1, 2, 3, 4, 5]
    print("Already sorted:", arr4)
    print("Flips needed:", count_flips(arr4))
    print()
    
    # Test case 5 - Reverse sorted
    arr5 = [5, 4, 3, 2, 1]
    print("Reverse sorted:", arr5)
    print("Sorted array:", pancake_sort(arr5.copy()))
