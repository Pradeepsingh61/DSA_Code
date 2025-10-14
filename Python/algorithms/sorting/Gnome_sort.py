def gnome_sort(arr):
    """
    Gnome Sort Algorithm (also called Stupid Sort)
    Time Complexity: O(n^2) worst/average case, O(n) best case
    Space Complexity: O(1)
    
    Named after the garden gnome sorting flower pots. The gnome looks at
    the current and previous pot. If they are in order, he moves forward.
    If not, he swaps them and steps backward to check the previous pair.
    """
    n = len(arr)
    index = 0
    
    while index < n:
        if index == 0:
            index += 1
        elif arr[index] >= arr[index - 1]:
            index += 1
        else:
            # Swap and move back
            arr[index], arr[index - 1] = arr[index - 1], arr[index]
            index -= 1
    
    return arr


def gnome_sort_optimized(arr):
    """
    Optimized Gnome Sort
    Remembers the position before going back, so it doesn't
    start from beginning after each swap.
    """
    n = len(arr)
    index = 0
    
    while index < n:
        if index == 0:
            index += 1
        elif arr[index] >= arr[index - 1]:
            index += 1
        else:
            # Swap
            arr[index], arr[index - 1] = arr[index - 1], arr[index]
            
            # Move back but remember we can optimize here
            if index > 1:
                index -= 1
            else:
                index += 1
    
    return arr


def gnome_sort_with_steps(arr):
    """
    Gnome Sort with step-by-step visualization
    Useful for understanding the algorithm
    """
    n = len(arr)
    index = 0
    steps = 0
    
    print(f"Starting array: {arr}")
    
    while index < n:
        if index == 0:
            index += 1
        elif arr[index] >= arr[index - 1]:
            index += 1
        else:
            steps += 1
            arr[index], arr[index - 1] = arr[index - 1], arr[index]
            print(f"Step {steps}: Swapped positions {index-1} and {index}: {arr}")
            index -= 1
    
    print(f"\nTotal swaps: {steps}")
    return arr


# Example usage
if __name__ == "__main__":
    # Test case 1
    arr1 = [34, 2, 10, -9]
    print("Original array:", arr1)
    print("Sorted array:", gnome_sort(arr1.copy()))
    
    # Test case 2
    arr2 = [64, 34, 25, 12, 22, 11, 90]
    print("\nOriginal array:", arr2)
    print("Sorted array:", gnome_sort(arr2.copy()))
    
    # Test case 3 - Already sorted
    arr3 = [1, 2, 3, 4, 5]
    print("\nAlready sorted:", arr3)
    print("After sorting:", gnome_sort(arr3.copy()))
    
    # Test case 4 - With visualization
    arr4 = [5, 2, 8, 1, 9]
    print("\nWith step-by-step visualization:")
    gnome_sort_with_steps(arr4.copy())
    
    # Test case 5 - Single element
    arr5 = [42]
    print("\nSingle element:", arr5)
    print("After sorting:", gnome_sort(arr5.copy()))
