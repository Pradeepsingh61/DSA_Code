"""
Algorithm: Generate Valid Parentheses
Description: Generate all valid combinations of n pairs of parentheses using backtracking
Time Complexity: O(4^n / √n) - nth Catalan number
Space Complexity: O(n) for recursion stack
Author: DSA Code Repository
Date: 2025-10-02
"""

def generate_parentheses(n):
    """
    Generate all valid combinations of n pairs of parentheses.
    
    Args:
        n: Number of pairs of parentheses
        
    Returns:
        list: All valid parentheses combinations
        
    Examples:
        >>> generate_parentheses(3)
        ['((()))', '(()())', '(())()', '()(())', '()()()']
    """
    result = []
    
    def backtrack(current, open_count, close_count):
        """
        Backtracking helper function.
        
        Args:
            current: Current string being built
            open_count: Number of opening brackets used
            close_count: Number of closing brackets used
        """
        # Base case: completed valid combination
        if len(current) == 2 * n:
            result.append(current)
            return
        
        # Add opening bracket if we haven't used all n
        if open_count < n:
            backtrack(current + '(', open_count + 1, close_count)
        
        # Add closing bracket if it doesn't exceed opening brackets
        if close_count < open_count:
            backtrack(current + ')', open_count, close_count + 1)
    
    backtrack('', 0, 0)
    return result

def is_valid_parentheses(s):
    """
    Check if a string of parentheses is valid.
    
    Args:
        s: String containing only '(' and ')'
        
    Returns:
        bool: True if valid, False otherwise
    """
    count = 0
    for char in s:
        if char == '(':
            count += 1
        elif char == ')':
            count -= 1
            if count < 0:  # More closing than opening
                return False
    return count == 0  # All brackets matched

def generate_parentheses_multiple_types(n):
    """
    Generate valid combinations using multiple types of brackets.
    
    Args:
        n: Number of pairs for each type
        
    Returns:
        list: Valid combinations using (), [], {}
    """
    result = []
    brackets = ['()', '[]', '{}']
    
    def backtrack(current, stack):
        """
        Backtracking with stack to track opening brackets.
        
        Args:
            current: Current string
            stack: Stack of opening brackets
        """
        if len(current) == 6 * n:  # 3 types * 2 chars * n pairs
            if not stack:  # All brackets closed
                result.append(current)
            return
        
        # Try adding opening brackets
        for bracket_pair in brackets:
            opening = bracket_pair[0]
            if current.count(opening) < n:
                stack.append(opening)
                backtrack(current + opening, stack)
                stack.pop()
        
        # Try adding closing brackets
        if stack:
            opening = stack[-1]
            for bracket_pair in brackets:
                if bracket_pair[0] == opening:
                    closing = bracket_pair[1]
                    stack.pop()
                    backtrack(current + closing, stack)
                    stack.append(opening)
                    break
    
    backtrack('', [])
    return result

def count_valid_parentheses(n):
    """
    Count the number of valid parentheses combinations (Catalan number).
    
    Args:
        n: Number of pairs
        
    Returns:
        int: Count of valid combinations
    """
    if n <= 1:
        return 1
    
    # Using dynamic programming approach for Catalan number
    dp = [0] * (n + 1)
    dp[0] = dp[1] = 1
    
    for i in range(2, n + 1):
        for j in range(i):
            dp[i] += dp[j] * dp[i - 1 - j]
    
    return dp[n]

def generate_parentheses_with_minimum_removes(s):
    """
    Generate valid parentheses by removing minimum number of invalid brackets.
    
    Args:
        s: String with potentially invalid parentheses
        
    Returns:
        list: All possible valid strings with minimum removals
    """
    def min_removals_needed(string):
        """Calculate minimum removals needed."""
        left_rem = right_rem = 0
        for char in string:
            if char == '(':
                left_rem += 1
            elif char == ')':
                if left_rem > 0:
                    left_rem -= 1
                else:
                    right_rem += 1
        return left_rem, right_rem
    
    result = set()
    left_rem, right_rem = min_removals_needed(s)
    
    def backtrack(index, current, left_count, right_count, left_rem, right_rem):
        """Backtrack to find all valid combinations."""
        if index == len(s):
            if left_rem == 0 and right_rem == 0:
                result.add(current)
            return
        
        char = s[index]
        
        # Option 1: Remove current character (if it's a bracket that needs removal)
        if (char == '(' and left_rem > 0) or (char == ')' and right_rem > 0):
            new_left_rem = left_rem - 1 if char == '(' else left_rem
            new_right_rem = right_rem - 1 if char == ')' else right_rem
            backtrack(index + 1, current, left_count, right_count, 
                     new_left_rem, new_right_rem)
        
        # Option 2: Keep current character
        if char != '(' and char != ')':
            # Not a bracket, just add it
            backtrack(index + 1, current + char, left_count, right_count, 
                     left_rem, right_rem)
        elif char == '(':
            # Opening bracket
            backtrack(index + 1, current + char, left_count + 1, right_count, 
                     left_rem, right_rem)
        elif char == ')' and right_count < left_count:
            # Closing bracket (only if valid)
            backtrack(index + 1, current + char, left_count, right_count + 1, 
                     left_rem, right_rem)
    
    backtrack(0, '', 0, 0, left_rem, right_rem)
    return list(result)

def longest_valid_parentheses_length(s):
    """
    Find the length of the longest valid parentheses substring.
    
    Args:
        s: String containing parentheses
        
    Returns:
        int: Length of longest valid parentheses substring
    """
    max_length = 0
    stack = [-1]  # Initialize with -1 to handle edge cases
    
    for i, char in enumerate(s):
        if char == '(':
            stack.append(i)
        else:  # char == ')'
            stack.pop()
            if not stack:
                stack.append(i)  # New base
            else:
                max_length = max(max_length, i - stack[-1])
    
    return max_length

def balance_parentheses(s):
    """
    Add minimum parentheses to make string valid.
    
    Args:
        s: String with parentheses
        
    Returns:
        str: Balanced string with minimum additions
    """
    # Count unmatched opening and closing brackets
    open_needed = close_needed = 0
    
    for char in s:
        if char == '(':
            open_needed += 1
        elif char == ')':
            if open_needed > 0:
                open_needed -= 1
            else:
                close_needed += 1
    
    # Add required closing brackets at the end
    # Add required opening brackets at the beginning
    return '(' * close_needed + s + ')' * open_needed

def main():
    """Test the parentheses generation algorithms with various examples."""
    print("Generate Valid Parentheses using Backtracking")
    print("=" * 50)
    
    # Test case 1: Basic parentheses generation
    print("Test Case 1: Generate Valid Parentheses")
    for n in range(1, 5):
        parens = generate_parentheses(n)
        count = count_valid_parentheses(n)
        print(f"n = {n}: {count} combinations")
        print(f"Generated: {parens}")
        print(f"Count verification: Generated {len(parens)}, Expected {count}")
        print()
    
    # Test case 2: Validation test
    print("Test Case 2: Parentheses Validation")
    test_strings = ["()", "((", "))", "(())", "())", "((()))", "()()()"]
    
    for s in test_strings:
        valid = is_valid_parentheses(s)
        print(f"'{s}' is {'valid' if valid else 'invalid'}")
    
    # Test case 3: Multiple bracket types
    print("\n" + "="*50)
    print("Test Case 3: Multiple Bracket Types")
    multi_parens = generate_parentheses_multiple_types(2)
    print(f"Valid combinations with (), [], {{}} (2 pairs each):")
    for i, combo in enumerate(multi_parens[:10], 1):  # Show first 10
        print(f"  {i}: {combo}")
    if len(multi_parens) > 10:
        print(f"  ... and {len(multi_parens) - 10} more")
    
    # Test case 4: Minimum removals
    print("\n" + "="*50)
    print("Test Case 4: Minimum Removals to Make Valid")
    
    invalid_strings = [
        "()())",
        "(((",
        "())",
        "((a))",
        "(()"
    ]
    
    for s in invalid_strings:
        valid_versions = generate_parentheses_with_minimum_removes(s)
        print(f"'{s}' -> {valid_versions}")
    
    # Test case 5: Longest valid substring
    print("\n" + "="*50)
    print("Test Case 5: Longest Valid Parentheses Substring")
    
    test_strings_long = [
        "(()",
        ")()())",
        "()(()",
        "",
        "((()))",
        ")()((("
    ]
    
    for s in test_strings_long:
        length = longest_valid_parentheses_length(s)
        print(f"'{s}' -> Longest valid length: {length}")
    
    # Test case 6: Balance parentheses
    print("\n" + "="*50)
    print("Test Case 6: Balance Parentheses with Minimum Additions")
    
    unbalanced_strings = [
        "(((",
        ")))",
        "())",
        "(()",
        ")((",
        ""
    ]
    
    for s in unbalanced_strings:
        balanced = balance_parentheses(s)
        print(f"'{s}' -> '{balanced}'")
    
    # Test case 7: Catalan number verification
    print("\n" + "="*50)
    print("Test Case 7: Catalan Number Verification")
    
    print("n\tCatalan(n)\tGenerated\tMatch")
    print("-" * 40)
    for n in range(1, 8):
        catalan = count_valid_parentheses(n)
        generated = len(generate_parentheses(n))
        match = "✓" if catalan == generated else "✗"
        print(f"{n}\t{catalan}\t\t{generated}\t\t{match}")
    
    # Test case 8: Performance analysis
    print("\n" + "="*50)
    print("Test Case 8: Performance Analysis")
    
    import time
    
    performance_data = []
    for n in range(1, 8):
        start_time = time.time()
        parens = generate_parentheses(n)
        end_time = time.time()
        
        time_taken = end_time - start_time
        count = len(parens)
        performance_data.append((n, count, time_taken))
    
    print("n\tCount\tTime (s)")
    print("-" * 25)
    for n, count, time_taken in performance_data:
        print(f"{n}\t{count}\t{time_taken:.6f}")

if __name__ == "__main__":
    main()