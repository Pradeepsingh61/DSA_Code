def cocktail_shaker_sort(arr):
    """
    Cocktail Shaker Sort (also called Bidirectional Bubble Sort, Ripple Sort)
    Time Complexity: O(n^2) worst/average case, O(n) best case
    Space Complexity: O(1)
    
    An improvement over Bubble Sort that traverses the list in both directions
    alternately. It's slightly better than Bubble Sort in practice because it
    moves both small and large elements to their positions more quickly.
    
    Like shaking a cocktail shaker - elements move up and down!
    """
    n = len(arr)
    swapped = True
    start = 0
    end = n - 1
    
    while swapped:
        swapped = False
        
        # Move from left to right (like bubble sort)
        # Move the largest element to the end
        for i in range(start, end):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True
        
        if not swapped:
            break
        
        # Reduce end since largest element is now at the end
        end -= 1
        swapped = False
        
        # Move from right to left
        # Move the smallest element to the beginning
        for i in range(end - 1, start - 1, -1):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True
        
        # Increase start since smallest element is now at the beginning
        start += 1
    
    return arr


def cocktail_sort_optimized(arr):
    """
    Optimized version that remembers last swap position
    to avoid unnecessary comparisons
    """
    n = len(arr)
    start = 0
    end = n - 1
    
    while start < end:
        new_start = start
        new_end = end
        
        # Forward pass
        for i in range(start, end):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                new_end = i
        
        end = new_end
        
        # If no swaps in forward pass, array is sorted
        if start >= end:
            break
        
        # Backward pass
        for i in range(end - 1, start - 1, -1):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                new_start = i
        
        start = new_start
    
    return arr


def cocktail_sort_with_visualization(arr):
    """
    Cocktail Sort with step-by-step visualization
    """
    n = len(arr)
    swapped = True
    start = 0
    end = n - 1
    pass_num = 0
    
    print(f"Starting array: {arr}\n")
    
    while swapped:
        swapped = False
        pass_num += 1
        
        # Forward pass
        print(f"Pass {pass_num} - Forward (→):")
        for i in range(start, end):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True
                print(f"  Swapped positions {i} and {i+1}: {arr}")
        
        if not swapped:
            break
        
        end -= 1
        swapped = False
        
        # Backward pass
        print(f"Pass {pass_num} - Backward (←):")
        for i in range(end - 1, start - 1, -1):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True
                print(f"  Swapped positions {i} and {i+1}: {arr}")
        
        start += 1
        print(f"After pass {pass_num}: {arr}\n")
    
    print(f"Sorted in {pass_num} passes!")
    return arr


def compare_with_bubble_sort(arr):
    """
    Compare Cocktail Sort with Bubble Sort
    """
    def bubble_sort_count(arr):
        n = len(arr)
        swaps = 0
        for i in range(n):
            for j in range(0, n - i - 1):
                if arr[j] > arr[j + 1]:
                    arr[j], arr[j + 1] = arr[j + 1], arr[j]
                    swaps += 1
        return arr, swaps
    
    def cocktail_sort_count(arr):
        n = len(arr)
        swapped = True
        start = 0
        end = n - 1
        swaps = 0
        
        while swapped:
            swapped = False
            
            for i in range(start, end):
                if arr[i] > arr[i + 1]:
                    arr[i], arr[i + 1] = arr[i + 1], arr[i]
                    swapped = True
                    swaps += 1
            
            if not swapped:
                break
            
            end -= 1
            swapped = False
            
            for i in range(end - 1, start - 1, -1):
                if arr[i] > arr[i + 1]:
                    arr[i], arr[i + 1] = arr[i + 1], arr[i]
                    swapped = True
                    swaps += 1
            
            start += 1
        
        return arr, swaps
    
    arr_bubble = arr.copy()
    arr_cocktail = arr.copy()
    
    _, bubble_swaps = bubble_sort_count(arr_bubble)
    _, cocktail_swaps = cocktail_sort_count(arr_cocktail)
    
    print(f"Original array: {arr}")
    print(f"Bubble Sort swaps: {bubble_swaps}")
    print(f"Cocktail Sort swaps: {cocktail_swaps}")
    print(f"Improvement: {bubble_swaps - cocktail_swaps} fewer swaps")
    print(f"Percentage: {((bubble_swaps - cocktail_swaps) / bubble_swaps * 100):.1f}% reduction")


# Example usage
if __name__ == "__main__":
    # Test case 1
    arr1 = [5, 1, 4, 2, 8, 0, 2]
    print("Original array:", arr1)
    print("Sorted array:", cocktail_shaker_sort(arr1.copy()))
    print()
    
    # Test case 2
    arr2 = [64, 34, 25, 12, 22, 11, 90]
    print("Original array:", arr2)
    print("Sorted array:", cocktail_shaker_sort(arr2.copy()))
    print()
    
    # Test case 3 - With visualization (small array)
    arr3 = [5, 2, 8, 1, 9]
    print("Sorting with visualization:")
    cocktail_sort_with_visualization(arr3.copy())
    print()
    
    # Test case 4 - Already sorted
    arr4 = [1, 2, 3, 4, 5]
    print("Already sorted:", arr4)
    print("After sorting:", cocktail_shaker_sort(arr4.copy()))
    print()
    
    # Test case 5 - Worst case for bubble sort (small at end)
    arr5 = [2, 3, 4, 5, 1]
    print("Worst case for bubble sort (turtle at end):")
    compare_with_bubble_sort(arr5)
    print()
    
    # Test case 6 - Reverse sorted
    arr6 = [9, 8, 7, 6, 5, 4, 3, 2, 1]
    print("Reverse sorted:", arr6)
    print("After sorting:", cocktail_shaker_sort(arr6.copy()))
    print()
    
    # Test case 7 - Optimized version
    arr7 = [5, 1, 4, 2, 8, 0, 2]
    print("Using optimized version:")
    print("Original:", arr7)
    print("Sorted:", cocktail_sort_optimized(arr7.copy()))
    print()
    
    print("="*60)
    print("COCKTAIL SORT vs BUBBLE SORT:")
    print("-"*60)
    print("Cocktail Sort eliminates 'turtles' (small values at the end)")
    print("by traversing in both directions, making it faster in practice!")
    print("="*60)
