// A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

// Given a string s, return true if it is a palindrome, or false otherwise.

// Example 1:

// Input: s = "A man, a plan, a canal: Panama"
// Output: true
// Explanation: "amanaplanacanalpanama" is a palindrome.
// Example 2:

// Input: s = "race a car"
// Output: false
// Explanation: "raceacar" is not a palindrome.
// Example 3:

// Input: s = " "
// Output: true
// Explanation: s is an empty string "" after removing non-alphanumeric characters.
// Since an empty string reads the same forward and backward, it is a palindrome.

import java.util.ArrayList;
import java.util.List;

class Valid_Palindrome {
    public boolean isPalindrome(String s) {
        List<Character> list = new ArrayList<>();
        for (char c : s.toCharArray()) {
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9') {
                list.add(Character.toLowerCase(c));
            }
        }
        int p1 = 0;
        int p2 = list.size() - 1;
        while (p1 < p2) {
            if (list.get(p1) != list.get(p2)) return false;
            p1++;
            p2--;
        }
        return true;
        
    }
}