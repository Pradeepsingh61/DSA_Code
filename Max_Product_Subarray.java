public class _12_max_product_subarray {
    // brute force 
    // TC -> O(n^2)
    // SC -> O(1)
    // static public int maxProduct(int[] nums) {
    //     int n = nums.length;
    //     long maxproduct = Integer.MIN_VALUE;
    //     for (int i=0; i<n; i++) {
    //         long temp = 1;
    //         for (int j=i; j<n; j++) {
    //             temp *= nums[j];
    //             maxproduct = Math.max(maxproduct, temp);
    //         }
    //     }
    //     return (int)maxproduct;
    // }


    // optimal solution -> based on observation
    // 1. all +ve
    // 2. even -ve and rest +ve
    // 3. odd -ve and rest +ve
    // 4. if it have zeroes 
    // TC -> O(n)
    // SC -> O(1)
    static public int maxProduct(int[] nums) {
        int n = nums.length;
        int max = Integer.MIN_VALUE;
        int prefix = 1;
        int sufix = 1;
        for (int i=0; i<n; i++) {
            if (prefix == 0) prefix = 1;
            if (sufix == 0) sufix = 1;
            prefix *= nums[i];
            sufix *= nums[n-i-1];
            max = Math.max(max, Math.max(prefix, sufix));
        }
        return max;
    }
    public static void main(String[] args) {
        int[] arr = {2,3,-2,4};
        System.out.println(maxProduct(arr));
    }
}
