package anew;

// 给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。

// 计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。

// 你可以认为每种硬币的数量是无限的。

public class Solution0322 {
    public int coinChange(int[] coins, int amount) {
        int[] dp = new int[amount + 1];
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            int min = amount + 1;
            for (int coin : coins) {
                if (coin <= i) {
                    min = Math.min(min, dp[i - coin] + 1);
                }
            }
            dp[i] = min;
        }
        return dp[amount] == amount + 1 ? -1 : dp[amount];
    }

    private int[] dp;

    public int coinChange2(int[] coins, int amount) {
        dp = new int[amount + 1];
        dp[0] = 0;
        return dp(coins, amount);
    }

    private int dp(int[] coins, int remain) {
        if (remain < 0) {
            return -1;
        } else if (remain == 0) {
            return 0;
        }
        if (dp[remain] != 0) {
            return dp[remain];
        }
        int min = Integer.MAX_VALUE;
        for (int coin : coins) {
            int res = dp(coins, remain - coin);
            if (res >= 0) {
                min = Math.min(min, res + 1);
            }
        }
        dp[remain] = (min == Integer.MAX_VALUE) ? -1 : min;
        return dp[remain];
    }

    public static void main(String[] args) {
        Solution0322 solution = new Solution0322();
        int[] coins = { 1, 2, 5 };
        int amount = 11;
        int result = solution.coinChange(coins, amount);
        System.out.println(result); // 输出: 3 (11 = 5 + 5 + 1)
        int result2 = solution.coinChange2(coins, amount);
        System.out.println(result2); // 输出: 3 (11 = 5 + 5 + 1)
    }
}
