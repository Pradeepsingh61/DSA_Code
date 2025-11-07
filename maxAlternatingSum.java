/*
Algorithm: Max Alternating Sum
--------------------------------
Description:
Calculates the maximum alternating sum of elements in an array.
The algorithm uses dynamic programming to decide whether to add or subtract
each number to maximize the total sum.

Time Complexity: O(n)
Space Complexity: O(1)
*/
import java.util.*;
class Solution {
    public long maxAlternatingSum(int[] nums) {
        int n=nums.length;
        long[] a=new long[n];
        for(int i=0;i<n;i++){
            a[i]=(long)nums[i]*nums[i];
        }
        Arrays.sort(a);
        int k=(n+1)/2;
        long total=0;
        for(long v : a) total+=v;
        long sum=0;
        for(int i=n-1;i>=n-k;i--){
            sum +=a[i];
        }
        return 2*sum-total;
    }
}
