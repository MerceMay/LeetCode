#include <vector>
#include <climits>
using namespace std;
// 给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。

// 计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。

// 你可以认为每种硬币的数量是无限的。

// 示例 1：

// 输入：coins = [1, 2, 5], amount = 11
// 输出：3
// 解释：11 = 5 + 5 + 1
// 示例 2：

// 输入：coins = [2], amount = 3
// 输出：-1
// 示例 3：

// 输入：coins = [1], amount = 0
// 输出：0

// 提示：

// 1 <= coins.length <= 12
// 1 <= coins[i] <= 231 - 1
// 0 <= amount <= 104
// 方法一：记忆化搜索
class Solution
{
private:
    vector<int> f;

public:
    int coinChange(vector<int> &coins, int amount)
    {
        if (amount < 1)
            return 0;
        f.resize(amount + 1);
        return helper(coins, amount);
    }

private:
    int helper(vector<int> &coins, int rest)
    {
        if (rest < 0)
            return -1;
        if (f[rest] != 0 || rest == 0)
            return f[rest];
        int MIN = INT_MAX;
        for (int coin : coins)
        {
            int res = helper(coins, rest - coin);
            if (res >= 0 && res < MIN)
                MIN = res + 1;
        }
        f[rest] = MIN == INT_MAX ? -1 : MIN;
        return f[rest];
    }
};

// 方法二：动态规划
class Solution2
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++)
        {
            for (int j = 0; j < coins.size(); j++)
            {
                if (i - coins[j] >= 0)
                {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return dp[amount] == amount + 1 ? -1 : dp[amount];
    }
};