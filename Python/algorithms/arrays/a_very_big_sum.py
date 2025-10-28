def a_very_big_sum(arr: list[int]) -> int:
    """
    Description:
    This function calculates the sum of all integers in a given list.
    It iterates through each element in the array and accumulates the total.
    This approach ensures accurate summation even for large numbers
    (common in problems like "A Very Big Sum" from HackerRank).

    Approach:
    - Initialize a variable to store the cumulative sum.
    - Traverse the list and add each number to the sum.
    - Return the final result.

    Time Complexity:
        O(n) - The function iterates through all n elements once.
    Space Complexity:
        O(1) - Uses a constant amount of extra memory.

    >>> a_very_big_sum([2, 4, 6])
    12
    >>> a_very_big_sum([])
    0
    >>> a_very_big_sum([1000000001, 1000000002, 1000000003])
    3000000006
    """
    total = 0
    for i in arr:
        total += i
    return total


if __name__ == "__main__":
    arr = [2, 4, 6, 2, 4, 6, 3]
    result = a_very_big_sum(arr)
    print(f"Sum of {arr} is {result}")
