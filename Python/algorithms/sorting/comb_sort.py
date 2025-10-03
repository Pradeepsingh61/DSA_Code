def comb_sort(arr):
    """
    Comb Sort Algorithm
    Time Complexity: O(n^2) worst case, O(n log n) average case
    Space Complexity: O(1)
    
    An improvement over Bubble Sort. It eliminates small values at the end
    (turtles) by using a gap larger than 1. The gap starts with a large value
    and shrinks by a factor of 1.3 in every iteration until it reaches 1.
    """
    n = len(arr)
    gap = n
    shrink = 1.3
    swapped = True
    
    while gap > 1 or swapped:
        # Update the gap value for next comb
        gap = int(gap / shrink)
        if gap < 1:
            gap = 1
        
        swapped = False
        
        # Compare all elements with current gap
        for i in range(n - gap):
            if arr[i] > arr[i + gap]:
                # Swap elements
                arr[i], arr[i + gap] = arr[i + gap], arr[i]
                swapped = True
    
    return arr


def comb_sort_optimized(arr):
    """
    Optimized version with gap of 11 check
    (gap of 9 and 10 are suboptimal)
    """
    n = len(arr)
    gap = n
    shrink = 1.3
    swapped = True
    
    while gap > 1 or swapped:
        # Calculate gap
        gap = int(gap / shrink)
        
        # Minimum gap is 1
        if gap < 1:
            gap = 1
        
        # Optimize: if gap becomes 9 or 10, set it to 11
        if gap == 9 or gap == 10:
            gap = 11
        
        swapped = False
        
        # Compare elements with current gap
        for i in range(n - gap):
            if arr[i] > arr[i + gap]:
                arr[i], arr[i + gap] = arr[i + gap], arr[i]
                swapped = True
    
    return arr


# Example usage
if __name__ == "__main__":
    # Test case 1
    arr1 = [8, 4, 1, 56, 3, -44, 23, -6, 28, 0]
    print("Original array:", arr1)
    print("Sorted array:", comb_sort(arr1.copy()))
    
    # Test case 2
    arr2 = [64, 34, 25, 12, 22, 11, 90]
    print("\nOriginal array:", arr2)
    print("Sorted array:", comb_sort(arr2.copy()))
    
    # Test case 3 - Already sorted
    arr3 = [1, 2, 3, 4, 5]
    print("\nAlready sorted:", arr3)
    print("After sorting:", comb_sort(arr3.copy()))
    
    # Test case 4 - Reverse sorted
    arr4 = [9, 7, 5, 3, 1]
    print("\nReverse sorted:", arr4)
    print("After sorting:", comb_sort(arr4.copy()))
    
    # Test case 5 - With duplicates
    arr5 = [5, 2, 8, 2, 9, 5, 7]
    print("\nWith duplicates:", arr5)
    print("After sorting:", comb_sort_optimized(arr5.copy()))
