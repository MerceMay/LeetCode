#include <vector>
#include <algorithm>
using namespace std;
// 给定一个三角形 triangle ，找出自顶向下的最小路径和。

// 每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。也就是说，如果正位于当前行的下标 i ，那么下一步可以移动到下一行的下标 i 或 i + 1 。
class Solution
{
public:
    int minimumTotal(vector<vector<int>> &triangle)
    {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        dp[0][0] = triangle[0][0];
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                if (j == 0)
                {
                    dp[i][j] = dp[i - 1][j] + triangle[i][j];
                }
                else if (j == i)
                {
                    dp[i][j] = dp[i - 1][j - 1] + triangle[i][j];
                }
                else
                {
                    dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
                }
            }
        }
        int ans = dp[n - 1][0];
        for (int j = 1; j < n; j++)
        {
            ans = min(ans, dp[n - 1][j]);
        }
        return ans;
    }
};

// 只和上和左上有关，可以用一维数组滚动数组优化
// 需要从后往前更新，否则会把上一行更新过的值覆盖掉
class Solution2
{
public:
    int minimumTotal(vector<vector<int>> &triangle)
    {
        int n = triangle.size();
        vector<int> dp(n, 0);
        dp[0] = triangle[0][0];
        for (int i = 1; i < n; i++)
            for (int j = i; j >= 0; j--)
                if (j == 0)
                    dp[j] = dp[j] + triangle[i][j];
                else if (j == i)
                    dp[j] = dp[j - 1] + triangle[i][j];
                else
                    dp[j] = min(dp[j - 1], dp[j]) + triangle[i][j];
        return *min_element(dp.begin(), dp.end());
    }
};