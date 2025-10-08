# 📌 Combination Sum Algorithm

"""
Algorithm: Combination Sum
Description: Finds all unique combinations in a given set of numbers (candidates) where the candidate numbers sum to a target.
Each number in candidates may only be used once in the combination.

This problem is typically solved using a backtracking approach.

Time Complexity: O(2^N) in the worst case, where N is the number of candidates. This is because, in the worst case, we might explore all possible subsets.
Space Complexity: O(target) for the recursion stack and to store the current combination.

Author: Gemini
"""

def combination_sum(candidates: list[int], target: int) -> list[list[int]]:
    """
    Finds all unique combinations in `candidates` where the numbers sum to `target`.
    Each number in `candidates` may only be used once in the combination.

    Args:
        candidates (list[int]): A list of unique candidate numbers.
        target (int): The target sum.

    Returns:
        list[list[int]]: A list of unique combinations.
    """
    results = []
    # Sort candidates to handle duplicates and optimize pruning
    candidates.sort()

    def backtrack(remain, combo, start):
        if remain == 0:
            # Found a combination that sums to the target
            results.append(list(combo))
            return
        if remain < 0:
            # Current combination sum exceeds target, prune this path
            return

        for i in range(start, len(candidates)):
            # Skip duplicates to ensure unique combinations
            if i > start and candidates[i] == candidates[i-1]:
                continue
            
            # Include the current candidate in the combination
            combo.append(candidates[i])
            # Recursively call backtrack with updated remaining target and starting index
            backtrack(remain - candidates[i], combo, i + 1) # i + 1 because each number can be used once
            # Backtrack: remove the current candidate to explore other combinations
            combo.pop()

    backtrack(target, [], 0)
    return results


if __name__ == "__main__":
    print("Combination Sum Algorithm Tests:")

    test_cases = [
        ([10, 1, 2, 7, 6, 1, 5], 8, [[1, 7], [1, 2, 5], [2, 6], [1, 1, 6]]),
        ([2, 5, 2, 1, 2], 5, [[1, 2, 2], [5]]),
        ([2, 3, 6, 7], 7, [[7]]),
        ([2, 3, 5], 8, [[3, 5]]),
        ([1], 1, [[1]]),
        ([1], 2, []),
        ([], 5, []),
        ([1, 1, 1, 1], 2, [[1, 1]])
    ]

    for candidates, target, expected in test_cases:
        result = combination_sum(candidates, target)
        # Sort both result and expected for consistent comparison
        sorted_result = sorted([sorted(c) for c in result])
        sorted_expected = sorted([sorted(c) for c in expected])
        print(f"Candidates: {candidates}, Target: {target}, Result: {sorted_result}, Expected: {sorted_expected}")
        assert sorted_result == sorted_expected, f"Test failed for candidates={candidates}, target={target}"

    print("\nAll test cases passed!")