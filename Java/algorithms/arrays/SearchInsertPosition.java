/*
 * Algorithm Name:Search Insert Position .
 * Programming Language: Java
 * Category: Array 
 * Difficulty Level: Easy
 *
 * Author: Priya Rani 
 *
 * Algorithm Description:Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You must write an algorithm with O(log n) runtime complexity.


 

 * Time Complexity: O(log n) Uses binary search, halving the search space each step
 * Space complexity: O(1) No extra data structures used, only a few variables
*/
public class SearchInsertPosition {
    public int searchInsert(int[] nums, int target) {
        int left = 0, right = nums.length - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return left; 
    }

    public static void main(String[] args) {
        SearchInsertPosition solution = new SearchInsertPosition();
        int[] nums = {1, 3, 5, 6};
        int target = 5;

        System.out.println("Output: " + solution.searchInsert(nums, target));
    }
}
