from typing import List

def product_except_self(nums: List[int]) -> List[int]:
    """
    Returns an array `ans` where ans[i] is the product of all elements of
    `nums` except nums[i], without using division and in O(n) time.

    This implementation uses O(1) extra space (ignoring the output array)
    by:
      1. Building prefix products directly into the output array.
      2. Scanning from right to left and multiplying by a running suffix product.

    Time Complexity: O(n)
    Space Complexity: O(1) extra (output array not counted)

    Args:
        nums: List[int] - input list of integers (length >= 1)

    Returns:
        List[int] - product array as described above

    Example:
        >>> product_except_self([1,2,3,4])
        [24, 12, 8, 6]
    """
    n = len(nums)
    if n == 0:
        return []

    # ans[i] will hold product of nums[0..i-1] after first pass
    ans = [1] * n
    for i in range(1, n):
        ans[i] = ans[i - 1] * nums[i - 1]

    # suffix holds product of nums[i+1..n-1]
    suffix = 1
    for i in range(n - 1, -1, -1):
        ans[i] *= suffix
        suffix *= nums[i]

    return ans


# Optional: straightforward version using explicit prefix and suffix arrays
def product_except_self_extra_space(nums: List[int]) -> List[int]:
    """
    Alternate implementation that uses O(n) extra space for clarity.
    """
    n = len(nums)
    if n == 0:
        return []

    pre = [1] * n
    suf = [1] * n
    ans = [1] * n

    for i in range(1, n):
        pre[i] = pre[i - 1] * nums[i - 1]

    for i in range(n - 2, -1, -1):
        suf[i] = suf[i + 1] * nums[i + 1]

    for i in range(n):
        ans[i] = pre[i] * suf[i]

    return ans


if __name__ == "__main__":
    # quick manual checks
    examples = [
        ([1, 2, 3, 4], [24, 12, 8, 6]),
        ([0, 0], [0, 0]),
        ([0, 1, 2, 3], [6, 0, 0, 0]),
        ([5], [5]),
    ]
    for arr, expected in examples:
        out = product_except_self(arr)
        print(f"{arr} -> {out} (expected {expected})")
