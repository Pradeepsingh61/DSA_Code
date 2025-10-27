from typing import Dict
from collections import Counter

def are_occurrences_equal(s: str) -> bool:
    """
    Return True if every character in the string `s` appears the same number
    of times, otherwise False.

    Approach:
      - Use Counter to count occurrences of each character.
      - Convert counts to a set and check if its length is 1.

    Time Complexity: O(n)
    Space Complexity: O(k) where k is number of distinct characters

    Args:
        s: input string

    Returns:
        bool: True if all character frequencies are equal, else False.

    Examples:
        >>> are_occurrences_equal("abacbc")
        True  # a:2, b:2, c:2

        >>> are_occurrences_equal("aaabb")
        False # a:3, b:2
    """
    if not s:
        return True  # empty string — trivially equal frequencies

    counts = Counter(s)
    return len(set(counts.values())) == 1


if __name__ == "__main__":
    examples = [
        ("abacbc", True),
        ("aaabb", False),
        ("a", True),
        ("", True),
        ("abcabc", True),
        ("aabbccddd", False),
    ]
    for inp, expected in examples:
        out = are_occurrences_equal(inp)
        print(f"{inp!r} -> {out} (expected {expected})")
