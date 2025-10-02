/*
 * Algorithm: Naive String Matching
 * Description: Simple pattern matching algorithm that checks for the pattern
 *              at every position in the text without any preprocessing.
 * Time Complexity: O(n * m) in worst case (n = text length, m = pattern length)
 * Space Complexity: O(1)
 * Author: tanshen-kun
 *
 * Hacktoberfest2025
 */

#include <stdio.h>
#include <string.h>

/**
 * Naive string matching algorithm
 * Searches for all occurrences of a pattern in a given text
 *
 * @param text : string / text to search
 * @param pattern : pattern to search
 * @return : None
 */
void naive_search(char *text, char *pattern) {
  int textLength = strlen(text);
  int patternLength = strlen(pattern);
  int occurrences = 0;

  if (patternLength == 0 || patternLength > textLength) {
    printf("[x] No occurrences found.\n");
    return;
  }

  printf("[-] Searching for pattern %s in text %s:\n", pattern, text);

  for (int i = 0; i <= textLength - patternLength; i++) {
    int j;
    for (j = 0; j < patternLength; j++) {
      if (text[i + j] != pattern[j]) {
        break;
      }
    }

    if (j == patternLength) {
      printf("[*] Pattern found at index %d\n", i);
      occurrences++;
    }
  }

  if (occurrences == 0) {
    printf("[x] Pattern not found in text.\n");
  } else {
    printf("[*]Total occurrences: %d\n", occurrences);
  }
}

/**
 * Test function with multiple test cases
 */
void test_naive_algorithm() {

  // Test case 1: Simple match
  printf("[-] Test Case 1 - Simple Pattern Matching:\n");
  char text1[] = "ABAAABCDABABCABCABCDAB";
  char pattern1[] = "ABCAB";
  naive_search(text1, pattern1);
  printf("\n");

  // Test case 2: Multiple occurrences
  printf("[-] Test Case 2 - Multiple Occurrences:\n");
  char text2[] = "ABABCABABA";
  char pattern2[] = "ABA";
  naive_search(text2, pattern2);
  printf("\n");

  // Test case 3: Pattern not found
  printf("[-] Test Case 3 - Pattern Not Found:\n");
  char text3[] = "ABCDEFGHIJK";
  char pattern3[] = "XYZ";
  naive_search(text3, pattern3);
  printf("\n");

  // Test case 4: Pattern at beginning
  printf("[-] Test Case 4 - Pattern at Beginning:\n");
  char text4[] = "HELLO WORLD";
  char pattern4[] = "HELLO";
  naive_search(text4, pattern4);
  printf("\n");

  // Test case 5: Pattern at end
  printf("[-] Test Case 5 - Pattern at End:\n");
  char text5[] = "PROGRAMMING";
  char pattern5[] = "ING";
  naive_search(text5, pattern5);
  printf("\n");
}

int main() {
  printf("[--- Naive String Matching Algorithm in C ---]\n\n");

  test_naive_algorithm();

  printf("Algorithm Information :\n");
  printf("=> Time Complexity: O(n * m)\n");
  printf("=> Space Complexity: O(1)\n");
  printf("=> No preprocessing or optimization\n");
  printf("=> Useful for small strings\n");
  printf("=> Inefficient for large inputs or repetitive patterns\n");

  return 0;
}
