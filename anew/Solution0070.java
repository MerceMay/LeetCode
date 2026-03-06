package anew;

// 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

// 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

public class Solution0070 {
    public int climbStairs(int n) {
        if (n <= 0) {
            return 0;
        }
        int[] dp = new int[n + 1];
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }

    public int climbStairsOptimized(int n) {
        if (n <= 0) {
            return 0;
        }
        if (n == 1) {
            return 1;
        }
        int first = 1; // dp[0]
        int second = 1; // dp[1]
        for (int i = 2; i <= n; i++) {
            int current = first + second; // dp[i] = dp[i-1] + dp[i-2]
            first = second; // 更新 dp[i-2] 为 dp[i-1]
            second = current; // 更新 dp[i-1] 为 dp[i]
        }
        return second; // 最终返回 dp[n]
    }

    public static void main(String[] args) {
        Solution0070 solution = new Solution0070();
        int n = 5;
        int result = solution.climbStairs(n);
        System.out.println("爬 " + n + " 阶楼梯的方法数: " + result);
        
        int resultOptimized = solution.climbStairsOptimized(n);
        System.out.println("爬 " + n + " 阶楼梯的方法数(优化): " + resultOptimized);
    }
}
