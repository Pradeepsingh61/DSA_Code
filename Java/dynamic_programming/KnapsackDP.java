import java.util.Scanner;

public class KnapsackDP {
    static int knapsackDP(int W, int wt[], int val[], int n) {
        int[][] dp = new int[n + 1][W + 1];

        // Build table dp[] in bottom-up manner
        for (int i = 0; i <= n; i++) {
            for (int w = 0; w <= W; w++) {
                if (i == 0 || w == 0)
                    dp[i][w] = 0;
                else if (wt[i - 1] <= w)
                    dp[i][w] = Math.max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
                else
                    dp[i][w] = dp[i - 1][w];
            }
        }
        return dp[n][W];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of items: ");
        int n = scanner.nextInt();

        int[] val = new int[n];
        int[] wt = new int[n];

        System.out.println("Enter the values of the items:");
        for (int i = 0; i < n; i++) {
            System.out.print("Value of item " + (i + 1) + ": ");
            val[i] = scanner.nextInt();
        }

        System.out.println("Enter the weights of the items:");
        for (int i = 0; i < n; i++) {
            System.out.print("Weight of item " + (i + 1) + ": ");
            wt[i] = scanner.nextInt();
        }

        System.out.print("Enter the maximum capacity of the knapsack: ");
        int W = scanner.nextInt();

        System.out.println("Maximum value in Knapsack (DP) = " + knapsackDP(W, wt, val, n));

        scanner.close();
    }
}
