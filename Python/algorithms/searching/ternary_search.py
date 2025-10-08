def ternary_search(arr, target):
    """
    Performs ternary search on a sorted array to find the index of the target element.

    Ternary search is a divide and conquer algorithm that can find the position
    of a target value within a sorted array. It works by repeatedly dividing
    the search interval into three parts.

    Args:
        arr (list): A sorted list of elements.
        target: The element to search for.

    Returns:
        int: The index of the target element if found, otherwise -1.
    """
    left, right = 0, len(arr) - 1

    while left <= right:
        # Calculate mid1 and mid2
        mid1 = left + (right - left) // 3
        mid2 = right - (right - left) // 3

        # If target is at mid1
        if arr[mid1] == target:
            return mid1
        # If target is at mid2
        if arr[mid2] == target:
            return mid2

        # If target is in the left third
        if target < arr[mid1]:
            right = mid1 - 1
        # If target is in the right third
        elif target > arr[mid2]:
            left = mid2 + 1
        # If target is in the middle third
        else:
            left = mid1 + 1
            right = mid2 - 1
    return -1

def ternary_search_recursive(arr, target, left, right):
    """
    Performs recursive ternary search on a sorted array to find the index of the target element.

    Args:
        arr (list): A sorted list of elements.
        target: The element to search for.
        left (int): The left boundary of the current search space.
        right (int): The right boundary of the current search space.

    Returns:
        int: The index of the target element if found, otherwise -1.
    """
    if left > right:
        return -1

    mid1 = left + (right - left) // 3
    mid2 = right - (right - left) // 3

    if arr[mid1] == target:
        return mid1
    if arr[mid2] == target:
        return mid2

    if target < arr[mid1]:
        return ternary_search_recursive(arr, target, left, mid1 - 1)
    elif target > arr[mid2]:
        return ternary_search_recursive(arr, target, mid2 + 1, right)
    else:
        return ternary_search_recursive(arr, target, mid1 + 1, mid2 - 1)

if __name__ == "__main__":
    # Test cases for iterative ternary search
    print("Iterative Ternary Search Tests:")
    test_array = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    print(f"Array: {test_array}")

    # Test case 1: Target found in the left third
    target1 = 2
    result1 = ternary_search(test_array, target1)
    print(f"Target {target1}: Index {result1} (Expected: 1)")
    assert result1 == 1

    # Test case 2: Target found in the middle third
    target2 = 5
    result2 = ternary_search(test_array, target2)
    print(f"Target {target2}: Index {result2} (Expected: 4)")
    assert result2 == 4

    # Test case 3: Target found in the right third
    target3 = 9
    result3 = ternary_search(test_array, target3)
    print(f"Target {target3}: Index {result3} (Expected: 8)")
    assert result3 == 8

    # Test case 4: Target not found
    target4 = 11
    result4 = ternary_search(test_array, target4)
    print(f"Target {target4}: Index {result4} (Expected: -1)")
    assert result4 == -1

    # Test case 5: Target at the beginning
    target5 = 1
    result5 = ternary_search(test_array, target5)
    print(f"Target {target5}: Index {result5} (Expected: 0)")
    assert result5 == 0

    # Test case 6: Target at the end
    target6 = 10
    result6 = ternary_search(test_array, target6)
    print(f"Target {target6}: Index {result6} (Expected: 9)")
    assert result6 == 9

    # Test case 7: Empty array
    empty_array = []
    target7 = 5
    result7 = ternary_search(empty_array, target7)
    print(f"Target {target7} in empty array: Index {result7} (Expected: -1)")
    assert result7 == -1

    # Test case 8: Single element array - target found
    single_element_array = [7]
    target8 = 7
    result8 = ternary_search(single_element_array, target8)
    print(f"Target {target8} in single element array: Index {result8} (Expected: 0)")
    assert result8 == 0

    # Test case 9: Single element array - target not found
    target9 = 8
    result9 = ternary_search(single_element_array, target9)
    print(f"Target {target9} in single element array: Index {result9} (Expected: -1)")
    assert result9 == -1

    print("\nRecursive Ternary Search Tests:")
    # Test cases for recursive ternary search
    test_array_rec = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    print(f"Array: {test_array_rec}")

    # Test case 1: Target found in the left third
    target_rec1 = 2
    result_rec1 = ternary_search_recursive(test_array_rec, target_rec1, 0, len(test_array_rec) - 1)
    print(f"Target {target_rec1}: Index {result_rec1} (Expected: 1)")
    assert result_rec1 == 1

    # Test case 2: Target found in the middle third
    target_rec2 = 5
    result_rec2 = ternary_search_recursive(test_array_rec, target_rec2, 0, len(test_array_rec) - 1)
    print(f"Target {target_rec2}: Index {result_rec2} (Expected: 4)")
    assert result_rec2 == 4

    # Test case 3: Target found in the right third
    target_rec3 = 9
    result_rec3 = ternary_search_recursive(test_array_rec, target_rec3, 0, len(test_array_rec) - 1)
    print(f"Target {target_rec3}: Index {result_rec3} (Expected: 8)")
    assert result_rec3 == 8

    # Test case 4: Target not found
    target_rec4 = 11
    result_rec4 = ternary_search_recursive(test_array_rec, target_rec4, 0, len(test_array_rec) - 1)
    print(f"Target {target_rec4}: Index {result_rec4} (Expected: -1)")
    assert result_rec4 == -1

    # Test case 5: Target at the beginning
    target_rec5 = 1
    result_rec5 = ternary_search_recursive(test_array_rec, target_rec5, 0, len(test_array_rec) - 1)
    print(f"Target {target_rec5}: Index {result_rec5} (Expected: 0)")
    assert result_rec5 == 0

    # Test case 6: Target at the end
    target_rec6 = 10
    result_rec6 = ternary_search_recursive(test_array_rec, target_rec6, 0, len(test_array_rec) - 1)
    print(f"Target {target_rec6}: Index {result_rec6} (Expected: 9)")
    assert result_rec6 == 9

    # Test case 7: Empty array
    empty_array_rec = []
    target_rec7 = 5
    result_rec7 = ternary_search_recursive(empty_array_rec, target_rec7, 0, len(empty_array_rec) - 1)
    print(f"Target {target_rec7} in empty array: Index {result_rec7} (Expected: -1)")
    assert result_rec7 == -1

    # Test case 8: Single element array - target found
    single_element_array_rec = [7]
    target_rec8 = 7
    result_rec8 = ternary_search_recursive(single_element_array_rec, target_rec8, 0, len(single_element_array_rec) - 1)
    print(f"Target {target_rec8} in single element array: Index {result_rec8} (Expected: 0)")
    assert result_rec8 == 0

    # Test case 9: Single element array - target not found
    target_rec9 = 8
    result_rec9 = ternary_search_recursive(single_element_array_rec, target_rec9, 0, len(single_element_array_rec) - 1)
    print(f"Target {target_rec9} in single element array: Index {result_rec9} (Expected: -1)")
    assert result_rec9 == -1