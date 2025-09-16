def binary_search(arr, left, right, target):
    if right >= left:
        mid = left + (right - left) // 2

        if arr[mid] == target:
            return mid
        elif arr[mid] > target:
            return binary_search(arr, left, mid - 1, target)
        else:
            return binary_search(arr, mid + 1, right, target)
    return -1

def exponential_search(arr, target):
    if arr[0] == target:
        return 0

    i = 1
    while i < len(arr) and arr[i] <= target:
        i *= 2

    return binary_search(arr, i // 2, min(i, len(arr) - 1), target)

arr = [2, 3, 4, 10, 40, 50, 80]
target = 10
result = exponential_search(arr, target)
print(f"Element found at index: {result}")
