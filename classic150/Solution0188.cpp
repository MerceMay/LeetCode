#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
// 给你一个整数数组 prices 和一个整数 k ，其中 prices[i] 是某支给定的股票在第 i 天的价格。

// 设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。也就是说，你最多可以买 k 次，卖 k 次。

// 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

// 示例 1：

// 输入：k = 2, prices = [2,4,1]
// 输出：2
// 解释：在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。
// 示例 2：

// 输入：k = 2, prices = [3,2,6,5,0,3]
// 输出：7
// 解释：在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。
//      随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出, 这笔交易所能获得利润 = 3-0 = 3 。

// 提示：

// 1 <= k <= 100
// 1 <= prices.length <= 1000
// 0 <= prices[i] <= 1000

// dp[i][j][0, 1] 表示第i天，最多交易了j次，持有或不持有股票的最大利润
class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        int n = prices.size();
        if (n == 0)
            return 0;
        k = min(k, n / 2); // k不可能大于n/2
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(k + 1, vector<int>(2, 0)));
        // 对于i=0的情况，持有或不持有
        for (int j = 0; j <= k; j++)
        {
            dp[0][j][0] = 0;
            dp[0][j][1] = -prices[0];
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j <= k; j++)
            {
                dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);     // 要么昨天没持有，今天也没持有；要么昨天持有，今天卖了
                dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]); // 要么昨天持有，今天也持有；要么昨天没持有，今天买了
            }
        }
        return dp[n - 1][k][0];
    }
};

class Solution2
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        int n = prices.size();
        if (n == 0)
            return 0;
        k = min(k, n / 2); // k不可能大于n/2
        vector<vector<int>> haveStock(n, vector<int>(k + 1, 0));
        vector<vector<int>> noStock(n, vector<int>(k + 1, 0));
        // 对于i=0的情况，持有或不持有
        for (int j = 0; j <= k; j++)
        {
            noStock[0][j] = 0;
            haveStock[0][j] = -prices[0];
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j <= k; j++)
            {
                noStock[i][j] = max(noStock[i - 1][j], haveStock[i - 1][j] + prices[i]);       // 要么昨天没持有，今天也没持有；要么昨天持有，今天卖了
                haveStock[i][j] = max(haveStock[i - 1][j], noStock[i - 1][j - 1] - prices[i]); // 要么昨天持有，今天也持有；要么昨天没持有，今天买了
            }
        }
        return noStock[n - 1][k];
    }
};

// noStock需要保留上和左上；haveStock，只需要保留上和左
class Solution3
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        int n = prices.size();
        if (n == 0)
            return 0;
        k = min(k, n / 2); // k不可能大于n/2
        vector<int> haveStock(k + 1, -prices[0]);
        vector<int> noStock(k + 1, 0);
        for (int i = 1; i < n; i++)
        {
            for (int j = k; j >= 1; j--) // 逆序更新，防止覆盖
            {
                noStock[j] = max(noStock[j], haveStock[j] + prices[i]);       // 要么昨天没持有，今天也没持有；要么昨天持有，今天卖了
                haveStock[j] = max(haveStock[j], noStock[j - 1] - prices[i]); // 要么昨天持有，今天也持有；要么昨天没持有，今天买了
            }
        }
        return noStock[k];
    }
};