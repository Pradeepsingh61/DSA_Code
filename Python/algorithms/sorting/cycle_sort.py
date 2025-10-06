def cycle_sort(arr):
    """
    Cycle Sort Algorithm
    Time Complexity: O(n^2)
    Space Complexity: O(1)
    
    Minimizes the number of memory writes, making it useful for situations
    where write operations are expensive (like flash memory or EEPROM).
    
    It works by placing each element at its correct position by rotating
    cycles. Each cycle consists of elements that need to be rotated to
    reach their correct positions.
    """
    writes = 0
    n = len(arr)
    
    # Traverse array elements
    for cycle_start in range(0, n - 1):
        item = arr[cycle_start]
        
        # Find position where we put the item
        pos = cycle_start
        for i in range(cycle_start + 1, n):
            if arr[i] < item:
                pos += 1
        
        # If item is already in correct position
        if pos == cycle_start:
            continue
        
        # Skip duplicates
        while item == arr[pos]:
            pos += 1
        
        # Put the item to its correct position
        arr[pos], item = item, arr[pos]
        writes += 1
        
        # Rotate rest of the cycle
        while pos != cycle_start:
            pos = cycle_start
            
            # Find position where we put the element
            for i in range(cycle_start + 1, n):
                if arr[i] < item:
                    pos += 1
            
            # Skip duplicates
            while item == arr[pos]:
                pos += 1
            
            # Put the item to its correct position
            arr[pos], item = item, arr[pos]
            writes += 1
    
    return arr, writes


def cycle_sort_simple(arr):
    """
    Simplified version without counting writes
    """
    n = len(arr)
    
    for cycle_start in range(0, n - 1):
        item = arr[cycle_start]
        pos = cycle_start
        
        for i in range(cycle_start + 1, n):
            if arr[i] < item:
                pos += 1
        
        if pos == cycle_start:
            continue
        
        while item == arr[pos]:
            pos += 1
        
        arr[pos], item = item, arr[pos]
        
        while pos != cycle_start:
            pos = cycle_start
            
            for i in range(cycle_start + 1, n):
                if arr[i] < item:
                    pos += 1
            
            while item == arr[pos]:
                pos += 1
            
            arr[pos], item = item, arr[pos]
    
    return arr


def cycle_sort_with_visualization(arr):
    """
    Cycle Sort with step-by-step visualization
    """
    writes = 0
    n = len(arr)
    
    print(f"Starting array: {arr}\n")
    
    for cycle_start in range(0, n - 1):
        item = arr[cycle_start]
        pos = cycle_start
        
        for i in range(cycle_start + 1, n):
            if arr[i] < item:
                pos += 1
        
        if pos == cycle_start:
            continue
        
        print(f"Cycle starting at index {cycle_start} with value {item}")
        
        while item == arr[pos]:
            pos += 1
        
        arr[pos], item = item, arr[pos]
        writes += 1
        print(f"Write {writes}: Placed at position {pos}, array: {arr}")
        
        while pos != cycle_start:
            pos = cycle_start
            
            for i in range(cycle_start + 1, n):
                if arr[i] < item:
                    pos += 1
            
            while item == arr[pos]:
                pos += 1
            
            arr[pos], item = item, arr[pos]
            writes += 1
            print(f"Write {writes}: Placed at position {pos}, array: {arr}")
        
        print()
    
    print(f"Total writes: {writes}")
    return arr, writes


# Example usage
if __name__ == "__main__":
    # Test case 1
    arr1 = [1, 8, 3, 9, 10, 10, 2, 4]
    print("Original array:", arr1)
    sorted_arr, writes = cycle_sort(arr1.copy())
    print("Sorted array:", sorted_arr)
    print(f"Number of writes: {writes}\n")
    
    # Test case 2
    arr2 = [64, 34, 25, 12, 22, 11, 90]
    print("Original array:", arr2)
    sorted_arr, writes = cycle_sort(arr2.copy())
    print("Sorted array:", sorted_arr)
    print(f"Number of writes: {writes}\n")
    
    # Test case 3 - With visualization
    arr3 = [5, 2, 8, 1, 9]
    print("Sorting with visualization:")
    cycle_sort_with_visualization(arr3.copy())
    print()
    
    # Test case 4 - Already sorted
    arr4 = [1, 2, 3, 4, 5]
    print("Already sorted:", arr4)
    sorted_arr, writes = cycle_sort(arr4.copy())
    print("After sorting:", sorted_arr)
    print(f"Number of writes: {writes}\n")
    
    # Test case 5 - With duplicates
    arr5 = [5, 2, 2, 8, 1, 5, 9]
    print("With duplicates:", arr5)
    sorted_arr, writes = cycle_sort(arr5.copy())
    print("Sorted array:", sorted_arr)
    print(f"Number of writes: {writes}")
