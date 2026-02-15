#include <vector>
using namespace std;
// 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

// 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
class Solution
{
private:
    vector<int> dp;

public:
    int climbStairs(int n)
    {
        dp.resize(n + 1, -1);
        dp[0] = 1;
        dp[1] = 1;
        return climb(n);
    }

private:
    int climb(int n)
    {
        if (n < 0)
            return 0;
        if (dp[n] != -1)
            return dp[n];
        dp[n] = climb(n - 1) + climb(n - 2);
        return dp[n];
    }
};

class Solution2
{
public:
    int climbStairs(int n)
    {
        int first = 1, second = 1; // f(0)=1, f(1)=1
        for (int i = 2; i <= n; i++)
        {
            int third = first + second; // f(n)=f(n-1)+f(n-2)
            first = second;
            second = third;
        }
        return second;
    }
};