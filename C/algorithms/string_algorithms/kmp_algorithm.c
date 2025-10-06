/*
 * Algorithm Name:
 * KMP (Knuth-Morris-Pratt) String Matching Algorithm
 *
 * Programming Language:
 * C
 *
 * Category:
 * String Algorithms
 *
 * Difficulty Level:
 * Medium to Hard
 *
 * Algorithm Description:
 *
 * 1. Problem it solves:
 *    -> KMP algorithm efficiently finds all occurrences of a pattern string within
 *       a text string by avoiding unnecessary character comparisons through the use
 *       of a failure function (also called LPS - Longest Proper Prefix which is also Suffix).
 *
 * 2. Approach / Idea:
 *    -> Preprocess the pattern to create a failure function (LPS array)
 *    -> The LPS array tells us how many characters to skip when a mismatch occurs
 *    -> This eliminates the need to restart matching from the beginning after each mismatch
 *    -> Never move backwards in the text, only in the pattern
 *
 * 3. Complexity:
 *    Time: O(n + m) where n = length of text, m = length of pattern
 *    Space: O(m) for the LPS array
 *    
 * 4. Advantages over Naive Approach:
 *    -> Naive: O(n*m) time complexity
 *    -> KMP: O(n+m) time complexity - significant improvement for large texts
 *    -> Never re-examines text characters that have already been matched
 *
 * 5. Key Concepts:
 *    -> LPS Array: Longest Proper Prefix which is also Suffix
 *    -> Failure Function: Determines how much to shift pattern on mismatch
 *    -> Border: A string that is both prefix and suffix of another string
 *
 * Author:
 * Rishan Menezes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure to store match information
typedef struct {
    int position;
    int length;
} Match;

// Function prototypes
int* computeLPS(char pattern[], int m);
int* kmpSearch(char text[], char pattern[], int* matchCount);
void kmpSearchWithDetails(char text[], char pattern[]);
Match* kmpSearchAllMatches(char text[], char pattern[], int* matchCount);
int kmpSearchFirst(char text[], char pattern[]);
void displayLPSArray(char pattern[], int lps[]);
void demonstrateKMP(char text[], char pattern[]);
void printStringWithHighlight(char str[], int start, int length);
double measureSearchTime(char text[], char pattern[]);
int naiveSearch(char text[], char pattern[]);

int main() {
    int choice;
    char text[1000], pattern[100];
    
    printf("=== KMP (Knuth-Morris-Pratt) String Matching Algorithm ===\n\n");
    
    printf("Choose input method:\n");
    printf("1. Manual input\n");
    printf("2. Use predefined examples\n");
    printf("Enter your choice (1-2): ");
    scanf("%d", &choice);
    getchar(); // consume newline
    
    if (choice == 1) {
        printf("\nEnter the text string: ");
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = 0; // remove newline
        
        printf("Enter the pattern to search: ");
        fgets(pattern, sizeof(pattern), stdin);
        pattern[strcspn(pattern, "\n")] = 0; // remove newline
    } else {
        // Predefined example with multiple occurrences
        strcpy(text, "ABABDABACDABABCABCABCABCABC");
        strcpy(pattern, "ABABCAB");
        printf("\nUsing predefined example:\n");
        printf("Text: %s\n", text);
        printf("Pattern: %s\n", pattern);
    }
    
    printf("\nChoose operation:\n");
    printf("1. Find first occurrence\n");
    printf("2. Find all occurrences\n");
    printf("3. Detailed step-by-step demonstration\n");
    printf("4. Show LPS array construction\n");
    printf("5. Performance comparison with naive approach\n");
    printf("6. Complete analysis\n");
    printf("Enter your choice (1-6): ");
    scanf("%d", &choice);
    
    printf("\n=== Results ===\n");
    
    switch (choice) {
        case 1: {
            int pos = kmpSearchFirst(text, pattern);
            if (pos != -1) {
                printf("First occurrence found at position %d\n", pos);
                printStringWithHighlight(text, pos, strlen(pattern));
            } else {
                printf("Pattern not found in the text\n");
            }
            break;
        }
        
        case 2: {
            int matchCount = 0;
            Match* matches = kmpSearchAllMatches(text, pattern, &matchCount);
            
            if (matchCount > 0) {
                printf("Pattern found %d time(s):\n", matchCount);
                for (int i = 0; i < matchCount; i++) {
                    printf("  Position %d: ", matches[i].position);
                    printStringWithHighlight(text, matches[i].position, matches[i].length);
                }
                free(matches);
            } else {
                printf("Pattern not found in the text\n");
            }
            break;
        }
        
        case 3: {
            demonstrateKMP(text, pattern);
            break;
        }
        
        case 4: {
            int* lps = computeLPS(pattern, strlen(pattern));
            displayLPSArray(pattern, lps);
            free(lps);
            break;
        }
        
        case 5: {
            printf("Performance Comparison:\n");
            double kmpTime = measureSearchTime(text, pattern);
            
            clock_t start = clock();
            int naiveResult = naiveSearch(text, pattern);
            clock_t end = clock();
            double naiveTime = ((double)(end - start)) / CLOCKS_PER_SEC;
            
            printf("KMP Algorithm: %.6f seconds\n", kmpTime);
            printf("Naive Algorithm: %.6f seconds\n", naiveTime);
            
            if (naiveTime > 0) {
                printf("KMP is %.2fx faster\n", naiveTime / kmpTime);
            }
            break;
        }
        
        case 6: {
            kmpSearchWithDetails(text, pattern);
            break;
        }
        
        default:
            printf("Invalid choice!\n");
            return 1;
    }
    
    return 0;
}

/**
 * Compute the Longest Proper Prefix which is also Suffix (LPS) array
 * This is the preprocessing step that makes KMP efficient
 * 
 * @param pattern: The pattern string
 * @param m: Length of the pattern
 * @return: Pointer to the LPS array
 */
int* computeLPS(char pattern[], int m) {
    int* lps = (int*)calloc(m, sizeof(int));
    int len = 0;  // length of the previous longest prefix suffix
    int i = 1;
    
    // lps[0] is always 0
    lps[0] = 0;
    
    // Calculate lps[i] for i = 1 to m-1
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                // This is tricky. Consider the example "AAACAAAA" and i = 7
                len = lps[len - 1];
                // Also note that we do not increment i here
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    return lps;
}

/**
 * KMP Search - Find all occurrences of pattern in text
 * 
 * @param text: The text string to search in
 * @param pattern: The pattern string to search for
 * @param matchCount: Pointer to store the number of matches found
 * @return: Array of positions where matches are found
 */
int* kmpSearch(char text[], char pattern[], int* matchCount) {
    int n = strlen(text);
    int m = strlen(pattern);
    
    if (m == 0 || n == 0 || m > n) {
        *matchCount = 0;
        return NULL;
    }
    
    // Compute LPS array
    int* lps = computeLPS(pattern, m);
    
    // Array to store match positions (worst case: all positions match)
    int* matches = (int*)malloc(n * sizeof(int));
    *matchCount = 0;
    
    int i = 0; // index for text
    int j = 0; // index for pattern
    
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        
        if (j == m) {
            // Found a match
            matches[*matchCount] = i - j;
            (*matchCount)++;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            // Mismatch after j matches
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    free(lps);
    
    if (*matchCount == 0) {
        free(matches);
        return NULL;
    }
    
    // Resize array to actual count
    matches = (int*)realloc(matches, (*matchCount) * sizeof(int));
    return matches;
}

/**
 * Find first occurrence of pattern in text using KMP
 * 
 * @param text: The text string to search in
 * @param pattern: The pattern string to search for
 * @return: Position of first match, or -1 if not found
 */
int kmpSearchFirst(char text[], char pattern[]) {
    int matchCount = 0;
    int* matches = kmpSearch(text, pattern, &matchCount);
    
    if (matchCount > 0) {
        int firstMatch = matches[0];
        free(matches);
        return firstMatch;
    }
    
    return -1;
}

/**
 * Find all matches with detailed information
 * 
 * @param text: The text string to search in
 * @param pattern: The pattern string to search for
 * @param matchCount: Pointer to store the number of matches found
 * @return: Array of Match structures containing position and length
 */
Match* kmpSearchAllMatches(char text[], char pattern[], int* matchCount) {
    int* positions = kmpSearch(text, pattern, matchCount);
    
    if (*matchCount == 0) {
        return NULL;
    }
    
    Match* matches = (Match*)malloc((*matchCount) * sizeof(Match));
    int patternLen = strlen(pattern);
    
    for (int i = 0; i < *matchCount; i++) {
        matches[i].position = positions[i];
        matches[i].length = patternLen;
    }
    
    free(positions);
    return matches;
}

/**
 * Detailed KMP search with step-by-step demonstration
 * 
 * @param text: The text string to search in
 * @param pattern: The pattern string to search for
 */
void kmpSearchWithDetails(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);
    
    printf("Text: %s (length: %d)\n", text, n);
    printf("Pattern: %s (length: %d)\n\n", pattern, m);
    
    // Show LPS array
    int* lps = computeLPS(pattern, m);
    displayLPSArray(pattern, lps);
    
    printf("\nSearching process:\n");
    printf("Text:    %s\n", text);
    
    int i = 0, j = 0;
    int step = 1;
    int matches = 0;
    
    while (i < n) {
        printf("\nStep %d: Comparing text[%d]='%c' with pattern[%d]='%c'\n", 
               step++, i, text[i], j, pattern[j]);
        
        if (pattern[j] == text[i]) {
            printf("Match! Moving both pointers forward.\n");
            i++;
            j++;
        }
        
        if (j == m) {
            printf("*** PATTERN FOUND at position %d ***\n", i - j);
            matches++;
            printStringWithHighlight(text, i - j, m);
            j = lps[j - 1];
            printf("Using LPS: j = lps[%d] = %d\n", m - 1, j);
        } else if (i < n && pattern[j] != text[i]) {
            printf("Mismatch!\n");
            if (j != 0) {
                printf("Using LPS: j = lps[%d] = %d\n", j - 1, lps[j - 1]);
                j = lps[j - 1];
            } else {
                printf("j = 0, moving text pointer forward.\n");
                i++;
            }
        }
    }
    
    printf("\nSearch completed. Total matches found: %d\n", matches);
    free(lps);
}

/**
 * Demonstrate the KMP algorithm with visual representation
 * 
 * @param text: The text string to search in
 * @param pattern: The pattern string to search for
 */
void demonstrateKMP(char text[], char pattern[]) {
    printf("KMP Algorithm Demonstration:\n");
    printf("===========================\n\n");
    
    kmpSearchWithDetails(text, pattern);
}

/**
 * Display the LPS array with explanation
 * 
 * @param pattern: The pattern string
 * @param lps: The LPS array
 */
void displayLPSArray(char pattern[], int lps[]) {
    int m = strlen(pattern);
    
    printf("LPS Array Construction:\n");
    printf("Pattern: ");
    for (int i = 0; i < m; i++) {
        printf("%c ", pattern[i]);
    }
    printf("\n");
    
    printf("Index:   ");
    for (int i = 0; i < m; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    printf("LPS:     ");
    for (int i = 0; i < m; i++) {
        printf("%d ", lps[i]);
    }
    printf("\n\n");
    
    printf("LPS[i] represents the length of the longest proper prefix\n");
    printf("of pattern[0..i] which is also a suffix of pattern[0..i]\n");
}

/**
 * Print string with highlighted portion
 * 
 * @param str: The string to print
 * @param start: Start position of highlight
 * @param length: Length of highlight
 */
void printStringWithHighlight(char str[], int start, int length) {
    printf("Text: ");
    for (int i = 0; str[i] != '\0'; i++) {
        if (i >= start && i < start + length) {
            printf("[%c]", str[i]);
        } else {
            printf("%c", str[i]);
        }
    }
    printf("\n");
}

/**
 * Measure the execution time of KMP search
 * 
 * @param text: The text string to search in
 * @param pattern: The pattern string to search for
 * @return: Time taken in seconds
 */
double measureSearchTime(char text[], char pattern[]) {
    clock_t start = clock();
    
    int matchCount = 0;
    int* matches = kmpSearch(text, pattern, &matchCount);
    
    clock_t end = clock();
    
    if (matches) {
        free(matches);
    }
    
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

/**
 * Naive string matching for comparison
 * 
 * @param text: The text string to search in
 * @param pattern: The pattern string to search for
 * @return: Position of first match, or -1 if not found
 */
int naiveSearch(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);
    
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            return i; // Found at position i
        }
    }
    
    return -1; // Not found
}
