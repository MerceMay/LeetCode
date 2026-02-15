#include <vector>
#include <cmath>
using namespace std;
// 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

// 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

// 示例 1：

// 输入：n = 2
// 输出：2
// 解释：有两种方法可以爬到楼顶。
// 1. 1 阶 + 1 阶
// 2. 2 阶
// 示例 2：

// 输入：n = 3
// 输出：3
// 解释：有三种方法可以爬到楼顶。
// 1. 1 阶 + 1 阶 + 1 阶
// 2. 1 阶 + 2 阶
// 3. 2 阶 + 1 阶

// 提示：

// 1 <= n <= 45
class Solution
{
public:
    int climbStairs(int n)
    {
        if (n == 1)
            return 1;
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};

// 方法二：通项公式，求特征值
class Solution2
{
public:
    int climbStairs(int n)
    {
        double sqrt5 = sqrt(5);
        double fibn = pow((1 + sqrt5) / 2, n + 1) - pow((1 - sqrt5) / 2, n + 1);
        return (int)round(fibn / sqrt5);
    }
};

// 方法三：滚动数组
class Solution3
{
public:
    int climbStairs(int n)
    {
        int x1 = 0, x2 = 0, x3 = 1;
        for (int i = 1; i <= n; i++)
        {
            x1 = x2;
            x2 = x3;
            x3 = x1 + x2;
        }
        return x3;
    }
};

// 把特征方程转换成矩阵方程