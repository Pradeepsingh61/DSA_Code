import math

def jump_search(arr, target):
    length = len(arr)
    step = math.isqrt(length)
    prev = 0

    while arr[min(step, length) - 1] < target:
        prev = step
        step += math.isqrt(length)
        if prev >= length:
            return -1

    for i in range(prev, min(step, length)):
        if arr[i] == target:
            return i
    return -1

arr = [1, 3, 5, 7, 9, 11, 13, 15, 17]
target = 13
result = jump_search(arr, target)
print(f"Element found at index: {result}")
