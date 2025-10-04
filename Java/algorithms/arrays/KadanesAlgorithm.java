public class KadanesAlgorithm {
    public static int maxSubArraySum(int[] nums) {
        int maxSoFar = nums[0];
        int currentMax = nums[0];

        for (int i = 1; i < nums.length; i++) {
          
            currentMax = Math.max(nums[i], currentMax + nums[i]);

            maxSoFar = Math.max(maxSoFar, currentMax);
        }

        return maxSoFar;
    }

    public static void main(String[] args) {
        int[] nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        int maxSum = maxSubArraySum(nums);
        System.out.println("Maximum subarray sum is: " + maxSum);
    }
}
