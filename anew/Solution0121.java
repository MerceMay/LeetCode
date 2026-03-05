package anew;

// 给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

// 你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

// 返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。

public class Solution0121 {
    public int maxProfit(int[] prices) {
        int maxProfit = 0;
        int minPrice = Integer.MAX_VALUE; // 记录第i天之前的最低价格

        for (int price : prices) {
            minPrice = Math.min(minPrice, price);
            maxProfit = Math.max(maxProfit, price - minPrice); // 非要在第i天卖出，计算利润
        }
        return maxProfit;
    }

    public int maxProfit2(int[] prices) {
        int n = prices.length;
        int[][] dp = new int[n][2];
        dp[0][0] = 0; // 第一天不持有股票的利润
        dp[0][1] = -prices[0]; // 第一天持有股票的利润
        for (int i = 1; i < n; i++) {
            dp[i][0] = Math.max(dp[i - 1][1] + prices[i], dp[i - 1][0]); // 卖出股票或保持不持有
            dp[i][1] = Math.max(dp[i - 1][1], -prices[i]); // 保持持有或买入股票
        }
        return dp[n - 1][0];
    }

    public int maxProfit3(int[] prices) {
        int n = prices.length;
        int dp_i_0 = 0; // 不持有股票的利润
        int dp_i_1 = -prices[0]; // 持有股票的利润
        for (int i = 1; i < n; i++) {
            dp_i_0 = Math.max(dp_i_1 + prices[i], dp_i_0); // 卖出股票或保持不持有
            dp_i_1 = Math.max(dp_i_1, -prices[i]); // 保持持有或买入股票
        }
        return dp_i_0;
    }

    public static void main(String[] args) {
        Solution0121 solution = new Solution0121();
        int[] prices = { 7, 1, 5, 3, 6, 4 };
        int maxProfit = solution.maxProfit(prices);
        System.out.println(maxProfit); // 输出: 最大利润: 5
        int maxProfit2 = solution.maxProfit2(prices);
        System.out.println(maxProfit2); // 输出: 最大利润: 5
        int maxProfit3 = solution.maxProfit3(prices);
        System.out.println(maxProfit3); // 输出: 最大利润: 5
    }
}
