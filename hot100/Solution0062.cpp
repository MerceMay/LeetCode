#include <vector>
using namespace std;
// 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

// 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

// 问总共有多少条不同的路径？

// 示例 1：

// 输入：m = 3, n = 7
// 输出：28
// 示例 2：

// 输入：m = 3, n = 2
// 输出：3
// 解释：
// 从左上角开始，总共有 3 条路径可以到达右下角。
// 1. 向右 -> 向下 -> 向下
// 2. 向下 -> 向下 -> 向右
// 3. 向下 -> 向右 -> 向下
// 示例 3：

// 输入：m = 7, n = 3
// 输出：28
// 示例 4：

// 输入：m = 3, n = 3
// 输出：6
class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == 0 || j == 0)
                    dp[i][j] = 1;
                else
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};

// 滚动数组压缩:
// 需要上和左。上属于前一个状态，左属于当前状态的左边一个，因此需要从左往右更新
class Solution2
{
public:
    int uniquePaths(int m, int n)
    {
        vector<int> dp(n, 1);
        for (int i = 0; i < m; i++)
        {
            for (int j = 1; j < n; j++)
                dp[j] += dp[j - 1];
        }
        return dp[n - 1];
    }
};

// 组合数：一共m+n-2步，下m-1步，右n-1步
class Solution3
{
public:
    int uniquePaths(int m, int n)
    {
        long long ans = 1;
        for (int x = n, y = 1; y < m; ++x, ++y)
        {
            ans = ans * x / y;
        }
        return ans;
    }
};