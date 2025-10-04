/**
 * Radix Sort Algorithm Implementation
 *
 * Description:
 * Radix Sort is a non-comparative sorting algorithm that sorts integers by 
 * processing individual digits. It processes digits from least significant digit (LSD) 
 * to most significant digit (MSD) using a stable intermediate sorting algorithm 
 * (like Counting Sort).
 *
 * Algorithm Steps:
 * 1. Find the maximum number to determine the number of digits
 * 2. For each digit position (starting from LSD):
 *    - Use counting sort to sort elements based on current digit
 *    - Maintain stability to preserve relative order
 * 3. Repeat until all digits are processed
 *
 * Time Complexity: 
 * - Best Case: O(d * (n + b)) where d = number of digits, n = number of elements, b = base (10)
 * - Average Case: O(d * (n + b))
 * - Worst Case: O(d * (n + b))
 *
 * Space Complexity: O(n + b) - for output array and counting array
 *
 * Advantages:
 * - Linear time complexity for fixed number of digits
 * - Stable sorting algorithm
 * - No comparisons needed
 *
 * Disadvantages:
 * - Only works with non-negative integers (or requires modification)
 * - Uses extra space
 * - Performance depends on number of digits
 *
 * Author: Generated for Issue #407
 * Category: Sorting Algorithms
 * Difficulty: Medium (Intermediate)
 */

import java.util.Arrays;
import java.util.Scanner;

public class RadixSort {
    
    /**
     * Main method to demonstrate Radix Sort with user input and test cases
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        try {
            System.out.println("=== Radix Sort Algorithm ===");
            System.out.println("Choose an option:");
            System.out.println("1. Enter your own array");
            System.out.println("2. Run predefined test cases");
            System.out.print("Enter choice (1 or 2): ");
            
            int choice = getValidInteger(scanner);
            
            if (choice == 1) {
                // User input
                System.out.print("Enter the number of elements: ");
                int n = getValidInteger(scanner);
                
                if (n <= 0) {
                    System.out.println("Array size must be positive!");
                    return;
                }
                
                int[] arr = new int[n];
                System.out.println("Enter " + n + " non-negative integers:");
                
                for (int i = 0; i < n; i++) {
                    System.out.print("Element " + (i + 1) + ": ");
                    int value = getValidInteger(scanner);
                    if (value < 0) {
                        System.out.println("Warning: Radix sort works best with non-negative integers.");
                        System.out.println("Converting negative number to positive: " + Math.abs(value));
                        value = Math.abs(value);
                    }
                    arr[i] = value;
                }
                
                System.out.println("\nOriginal array: " + Arrays.toString(arr));
                
                // Perform radix sort
                long startTime = System.nanoTime();
                radixSort(arr);
                long endTime = System.nanoTime();
                
                System.out.println("Sorted array:   " + Arrays.toString(arr));
                System.out.printf("Time taken: %.3f ms%n", (endTime - startTime) / 1_000_000.0);
                
            } else if (choice == 2) {
                // Run test cases
                runTestCases();
            } else {
                System.out.println("Invalid choice!");
            }
            
        } catch (Exception e) {
            System.out.println("An error occurred: " + e.getMessage());
        } finally {
            scanner.close();
        }
    }
    
    /**
     * Radix Sort implementation using Counting Sort as subroutine
     * Time Complexity: O(d * (n + b)) where d = digits, n = elements, b = base
     * Space Complexity: O(n + b)
     * 
     * @param arr Array of non-negative integers to be sorted
     */
    public static void radixSort(int[] arr) {
        if (arr == null || arr.length <= 1) {
            return; // Already sorted or empty
        }
        
        // Find the maximum number to determine number of digits
        int max = getMaximum(arr);
        
        // Process each digit position (1s, 10s, 100s, etc.)
        // exp represents the current digit position (1, 10, 100, ...)
        for (int exp = 1; max / exp > 0; exp *= 10) {
            countingSortByDigit(arr, exp);
        }
    }
    
    /**
     * Counting Sort implementation for a specific digit position
     * This is a stable sort that maintains relative order of equal elements
     * 
     * @param arr Array to be sorted
     * @param exp Current digit position (1 for units, 10 for tens, etc.)
     */
    private static void countingSortByDigit(int[] arr, int exp) {
        int n = arr.length;
        int[] output = new int[n]; // Output array to store sorted elements
        int[] count = new int[10]; // Count array for digits 0-9
        
        // Step 1: Count occurrences of each digit (0-9) at current position
        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % 10;
            count[digit]++;
        }
        
        // Step 2: Transform count array to store actual positions
        // count[i] now contains the position where digit i should be placed
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        
        // Step 3: Build output array in reverse order to maintain stability
        // Processing from right to left ensures stable sorting
        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--; // Decrement count for next occurrence
        }
        
        // Step 4: Copy sorted elements back to original array
        System.arraycopy(output, 0, arr, 0, n);
    }
    
    /**
     * Helper method to find maximum element in array
     * 
     * @param arr Input array
     * @return Maximum element in the array
     */
    private static int getMaximum(int[] arr) {
        int max = arr[0];
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        return max;
    }
    
    /**
     * Gets a valid integer from user input with error handling
     * 
     * @param scanner Scanner object for input
     * @return Valid integer input
     */
    private static int getValidInteger(Scanner scanner) {
        while (!scanner.hasNextInt()) {
            System.out.println("Invalid input. Please enter an integer.");
            scanner.next(); // Clear invalid input
        }
        return scanner.nextInt();
    }
    
    /**
     * Runs comprehensive test cases as specified in the issue
     */
    private static void runTestCases() {
        System.out.println("\n=== Running Test Cases ===");
        
        // Test Case 1: Small array
        System.out.println("\nTest Case 1: Small array");
        int[] test1 = {170, 45, 75, 90, 2, 802, 24, 66};
        System.out.println("Original: " + Arrays.toString(test1));
        radixSort(test1);
        System.out.println("Sorted:   " + Arrays.toString(test1));
        
        // Test Case 2: Array with repeated numbers
        System.out.println("\nTest Case 2: Array with repeated numbers");
        int[] test2 = {5, 2, 8, 2, 9, 1, 5, 5, 8};
        System.out.println("Original: " + Arrays.toString(test2));
        radixSort(test2);
        System.out.println("Sorted:   " + Arrays.toString(test2));
        
        // Test Case 3: Single-element array
        System.out.println("\nTest Case 3: Single-element array");
        int[] test3 = {42};
        System.out.println("Original: " + Arrays.toString(test3));
        radixSort(test3);
        System.out.println("Sorted:   " + Arrays.toString(test3));
        
        // Test Case 4: Already sorted array
        System.out.println("\nTest Case 4: Already sorted array");
        int[] test4 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        System.out.println("Original: " + Arrays.toString(test4));
        radixSort(test4);
        System.out.println("Sorted:   " + Arrays.toString(test4));
        
        // Test Case 5: Reverse sorted array
        System.out.println("\nTest Case 5: Reverse sorted array");
        int[] test5 = {987, 654, 321, 100, 50, 25, 10, 5, 1};
        System.out.println("Original: " + Arrays.toString(test5));
        radixSort(test5);
        System.out.println("Sorted:   " + Arrays.toString(test5));
        
        // Test Case 6: Large numbers with different digit counts
        System.out.println("\nTest Case 6: Numbers with different digit counts");
        int[] test6 = {1, 23, 456, 7890, 12345, 67, 8, 901};
        System.out.println("Original: " + Arrays.toString(test6));
        radixSort(test6);
        System.out.println("Sorted:   " + Arrays.toString(test6));
        
        // Test Case 7: Empty array
        System.out.println("\nTest Case 7: Empty array");
        int[] test7 = {};
        System.out.println("Original: " + Arrays.toString(test7));
        radixSort(test7);
        System.out.println("Sorted:   " + Arrays.toString(test7));
        
        System.out.println("\nAll test cases completed successfully!");
        System.out.println("\nComplexity Analysis:");
        System.out.println("- Time Complexity: O(d * (n + b))");
        System.out.println("  where d = number of digits, n = number of elements, b = base (10)");
        System.out.println("- Space Complexity: O(n + b)");
        System.out.println("- Stable: Yes (maintains relative order of equal elements)");
        System.out.println("- In-place: No (requires additional space)");
    }
}
