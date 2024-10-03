def is_palindrome(s: str) -> bool:
    s = ''.join(filter(str.isalnum, s)).lower()
    return s == s[::-1]

# Example usage
print(is_palindrome("A man, a plan, a canal: Panama"))  # Output: True
