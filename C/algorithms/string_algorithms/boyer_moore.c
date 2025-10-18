/*
 * Algorithm: Boyer-Moore String Matching
 * Description: Efficient string searching algorithm using bad character and good suffix heuristics
 *              to skip characters during pattern matching, achieving sublinear time in best case
 * Time Complexity: O(n/m) best case, O(n*m) worst case (n = text length, m = pattern length)
 * Space Complexity: O(σ + m) where σ is alphabet size
 * Author: Abhijit
 * Date: October 2025
 * Hacktoberfest 2025
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 256  // ASCII character set

/**
 * Preprocesses the pattern for bad character heuristic
 * Creates a table storing the rightmost occurrence of each character in the pattern
 */
void computeBadCharacterTable(char* pattern, int patternLength, int badChar[ALPHABET_SIZE]) {
    int i;
    
    // Initialize all occurrences as -1
    for (i = 0; i < ALPHABET_SIZE; i++) {
        badChar[i] = -1;
    }
    
    // Fill the actual value of last occurrence of each character
    for (i = 0; i < patternLength; i++) {
        badChar[(int)pattern[i]] = i;
    }
}

/**
 * Utility function to compute suffix array for good suffix heuristic
 */
void computeSuffixArray(char* pattern, int patternLength, int* suffix) {
    int i, j;
    
    suffix[patternLength - 1] = patternLength;
    
    for (i = patternLength - 2; i >= 0; i--) {
        j = i;
        while (j >= 0 && pattern[j] == pattern[patternLength - 1 - i + j]) {
            j--;
        }
        suffix[i] = i - j;
    }
}

/**
 * Preprocesses the pattern for good suffix heuristic
 */
void computeGoodSuffixTable(char* pattern, int patternLength, int* goodSuffix) {
    int i, j;
    int* suffix = (int*)malloc(patternLength * sizeof(int));
    
    // Initialize good suffix table
    for (i = 0; i < patternLength; i++) {
        goodSuffix[i] = patternLength;
    }
    
    // Compute suffix array
    computeSuffixArray(pattern, patternLength, suffix);
    
    // Case 1: Pattern appears again in the text
    j = 0;
    for (i = patternLength - 1; i >= 0; i--) {
        if (suffix[i] == i + 1) {
            for (; j < patternLength - 1 - i; j++) {
                if (goodSuffix[j] == patternLength) {
                    goodSuffix[j] = patternLength - 1 - i;
                }
            }
        }
    }
    
    // Case 2: Suffix appears as a substring
    for (i = 0; i < patternLength - 1; i++) {
        goodSuffix[patternLength - 1 - suffix[i]] = patternLength - 1 - i;
    }
    
    free(suffix);
}

/**
 * Returns maximum of two integers
 */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * Boyer-Moore string matching algorithm
 * Searches for pattern in text and returns the index of first occurrence
 */
int boyerMooreSearch(char* text, char* pattern) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);
    
    if (patternLength == 0) return -1;
    if (patternLength > textLength) return -1;
    
    // Preprocessing
    int badChar[ALPHABET_SIZE];
    int* goodSuffix = (int*)malloc(patternLength * sizeof(int));
    
    computeBadCharacterTable(pattern, patternLength, badChar);
    computeGoodSuffixTable(pattern, patternLength, goodSuffix);
    
    int shift = 0;  // Shift of the pattern with respect to text
    
    while (shift <= (textLength - patternLength)) {
        int j = patternLength - 1;
        
        // Keep reducing index j while characters match
        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }
        
        // If pattern is found
        if (j < 0) {
            printf("Pattern found at index %d\n", shift);
            free(goodSuffix);
            return shift;
        }
        
        // Calculate shift using both heuristics
        int badCharShift = j - badChar[(int)text[shift + j]];
        int goodSuffixShift = goodSuffix[j];
        
        shift += max(badCharShift, goodSuffixShift);
    }
    
    free(goodSuffix);
    return -1;  // Pattern not found
}

/**
 * Enhanced Boyer-Moore that finds all occurrences
 */
void boyerMooreSearchAll(char* text, char* pattern) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);
    int occurrences = 0;
    
    if (patternLength == 0 || patternLength > textLength) {
        printf("No occurrences found.\n");
        return;
    }
    
    // Preprocessing
    int badChar[ALPHABET_SIZE];
    int* goodSuffix = (int*)malloc(patternLength * sizeof(int));
    
    computeBadCharacterTable(pattern, patternLength, badChar);
    computeGoodSuffixTable(pattern, patternLength, goodSuffix);
    
    int shift = 0;
    
    printf("Searching for pattern \"%s\" in text \"%s\":\n", pattern, text);
    
    while (shift <= (textLength - patternLength)) {
        int j = patternLength - 1;
        
        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }
        
        if (j < 0) {
            printf("Pattern found at index %d\n", shift);
            occurrences++;
            shift += goodSuffix[0];
        } else {
            int badCharShift = j - badChar[(int)text[shift + j]];
            int goodSuffixShift = goodSuffix[j];
            shift += max(badCharShift, goodSuffixShift);
        }
    }
    
    if (occurrences == 0) {
        printf("Pattern not found in text.\n");
    } else {
        printf("Total occurrences: %d\n", occurrences);
    }
    
    free(goodSuffix);
}

/**
 * Demonstration function with multiple test cases
 */
void demonstrateBoyerMoore() {
    printf("=== Boyer-Moore String Matching Demonstration ===\n\n");
    
    // Test case 1: Simple match
    printf("Test Case 1 - Simple Pattern Matching:\n");
    char text1[] = "ABAAABCDABABCABCABCDAB";
    char pattern1[] = "ABCAB";
    boyerMooreSearchAll(text1, pattern1);
    printf("\n");
    
    // Test case 2: Multiple occurrences
    printf("Test Case 2 - Multiple Occurrences:\n");
    char text2[] = "ABABCABABA";
    char pattern2[] = "ABA";
    boyerMooreSearchAll(text2, pattern2);
    printf("\n");
    
    // Test case 3: Pattern not found
    printf("Test Case 3 - Pattern Not Found:\n");
    char text3[] = "ABCDEFGHIJK";
    char pattern3[] = "XYZ";
    boyerMooreSearchAll(text3, pattern3);
    printf("\n");
    
    // Test case 4: Pattern at beginning
    printf("Test Case 4 - Pattern at Beginning:\n");
    char text4[] = "HELLO WORLD";
    char pattern4[] = "HELLO";
    boyerMooreSearchAll(text4, pattern4);
    printf("\n");
    
    // Test case 5: Pattern at end
    printf("Test Case 5 - Pattern at End:\n");
    char text5[] = "PROGRAMMING";
    char pattern5[] = "ING";
    boyerMooreSearchAll(text5, pattern5);
    printf("\n");
}

int main() {
    int choice;
    
    printf("Boyer-Moore String Matching Algorithm in C\n");
    printf("==========================================\n");
    printf("1. Interactive mode (enter your own text and pattern)\n");
    printf("2. Demonstration mode (predefined test cases)\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    getchar(); // consume newline
    
    if (choice == 1) {
        // Interactive mode
        char text[1000], pattern[100];
        
        printf("\nEnter the text: ");
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = '\0'; // Remove newline
        
        printf("Enter the pattern to search: ");
        fgets(pattern, sizeof(pattern), stdin);
        pattern[strcspn(pattern, "\n")] = '\0'; // Remove newline
        
        printf("\n");
        boyerMooreSearchAll(text, pattern);
        
    } else if (choice == 2) {
        // Demonstration mode
        demonstrateBoyerMoore();
        
    } else {
        printf("Invalid choice! Please run the program again.\n");
        return 1;
    }
    
    printf("\nAlgorithm Information:\n");
    printf("- Best Case Time Complexity: O(n/m) - can skip characters!\n");
    printf("- Worst Case Time Complexity: O(n*m)\n");
    printf("- Space Complexity: O(σ + m) where σ is alphabet size\n");
    printf("- Uses bad character and good suffix heuristics\n");
    printf("- Efficient for large texts and small patterns\n");
    printf("- Used in text editors, grep, and search engines\n");
    
    return 0;
}