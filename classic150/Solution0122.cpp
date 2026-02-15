#include <vector>
using namespace std;
// 给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。

// 在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。

// 返回 你能获得的 最大 利润 。
// 方法一：贪心：只要第二天的价格高于今天的价格，就可以进行交易
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int profit = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            if (prices[i] > prices[i - 1])
            {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit;
    }
};

// 方法二：动态规划
// dp[i][0] 表示第 i 天不持有股票的最大利润
// dp[i][1] 表示第 i 天持有股票的最大利润
class Solution2
{
public:
    int maxProfit(vector<int> &prices)
    {
        vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
        dp[0][1] = -prices[0];
        for (int i = 1; i < prices.size(); i++)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]); // 今天不持有股票的最大利润 = max(昨天不持有, 昨天持有 + 今天卖出）
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]); // 今天持有股票的最大利润 = max(昨天持有, 昨天不持有 - 今天买入)
        }
        return dp[prices.size() - 1][0];
    }
};

class Solution3
{
public:
    int maxProfit(vector<int> &prices)
    {
        if (prices.empty())
            return 0;

        int n = prices.size();
        int dp_i_0 = 0, dp_i_1 = -prices[0];
        for (int i = 1; i < n; i++)
        {
            int temp = dp_i_0;
            dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
            dp_i_1 = max(dp_i_1, temp - prices[i]);
        }
        return dp_i_0;
    }
};