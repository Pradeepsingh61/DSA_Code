from typing import List

def rotate(nums: List[int], k: int) -> None:
    """
    Rotate `nums` to the right by `k` steps in-place.

    This uses the three-reverse trick:
      1. Reverse the whole array.
      2. Reverse the first k elements.
      3. Reverse the remaining n-k elements.

    Time Complexity: O(n)
    Space Complexity: O(1) (in-place)

    Args:
        nums: list of integers to rotate (modified in-place).
        k: non-negative number of steps to rotate to the right.

    Example:
        >>> arr = [1,2,3,4,5,6,7]
        >>> rotate(arr, 3)
        >>> arr
        [5,6,7,1,2,3,4]
    """
    n = len(nums)
    if n == 0:
        return

    k %= n
    if k == 0:
        return

    def _reverse(a: List[int], left: int, right: int) -> None:
        """Reverse subarray a[left:right+1] in-place."""
        while left < right:
            a[left], a[right] = a[right], a[left]
            left += 1
            right -= 1

    # reverse the entire array
    _reverse(nums, 0, n - 1)
    # reverse first k elements
    _reverse(nums, 0, k - 1)
    # reverse remaining elements
    _reverse(nums, k, n - 1)


# Optional: alternate simple solution that uses O(n) extra space (kept as reference)
def rotate_with_extra_array(nums: List[int], k: int) -> None:
    """
    Rotate using an extra array (not in-place).

    Time: O(n), Space: O(n)
    """
    n = len(nums)
    if n == 0:
        return

    k %= n
    if k == 0:
        return

    ans = [0] * n
    for i in range(n):
        ans[(i + k) % n] = nums[i]
    for i in range(n):
        nums[i] = ans[i]


if __name__ == "__main__":
    # quick manual demonstration
    examples = [
        ([1,2,3,4,5,6,7], 3, [5,6,7,1,2,3,4]),
        ([-1,-100,3,99], 2, [3,99,-1,-100]),
        ([1,2], 0, [1,2]),
        ([1,2], 2, [1,2]),
        ([], 5, []),
    ]
    for arr, k, expected in examples:
        a = arr.copy()
        rotate(a, k)
        print(f"rotate({arr}, {k}) -> {a} (expected {expected})")
