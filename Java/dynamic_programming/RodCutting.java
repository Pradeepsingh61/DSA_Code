// File: RodCutting.java
import java.util.Scanner;

public class RodCutting {
    public static int rodCutting(int price[], int n) {
        int dp[] = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            int maxVal = Integer.MIN_VALUE;
            for (int j = 0; j < i; j++) {
                maxVal = Math.max(maxVal, price[j] + dp[i - j - 1]);
            }
            dp[i] = maxVal;
        }
        return dp[n];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number of lengths: ");
        int n = sc.nextInt();
        int price[] = new int[n];
        System.out.println("Enter prices for length 1 to " + n + ":");
        for (int i = 0; i < n; i++) {
            price[i] = sc.nextInt();
        }
        int result = rodCutting(price, n);
        System.out.println("Maximum obtainable value is " + result);
        sc.close();
    }
}
