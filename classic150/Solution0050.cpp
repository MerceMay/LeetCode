using namespace std;
// 实现 pow(x, n) ，即计算 x 的整数 n 次幂函数（即，xn ）。

// 示例 1：

// 输入：x = 2.00000, n = 10
// 输出：1024.00000
// 示例 2：

// 输入：x = 2.10000, n = 3
// 输出：9.26100
// 示例 3：

// 输入：x = 2.00000, n = -2
// 输出：0.25000
// 解释：2-2 = 1/22 = 1/4 = 0.25

// 提示：

// -100.0 < x < 100.0
// -231 <= n <= 231-1
// n 是一个整数
// 要么 x 不为零，要么 n > 0 。
// -104 <= xn <= 104
class Solution
{
public:
    double myPow(double x, int n)
    {
        // n可能是-2^31，因此需要使用long long
        long long N = n;
        return N >= 0 ? quickMul(x, N) : 1.0 / quickMul(x, -N);
    }

private:
    double quickMul(double x, long long N)
    {
        if (N == 0)
            return 1.0;
        double y = quickMul(x, N / 2);
        return N % 2 == 0 ? y * y : y * y * x;
    }
};

class Solution2
{
public:
    double myPow(double x, int n)
    {
        // n可能是-2^31，因此需要使用long long
        long long N = n;
        return N >= 0 ? quickMul(x, N) : 1.0 / quickMul(x, -N);
    }

private:
    double quickMul(double x, long long N)
    {
        double ans = 1.0;
        double current_product = x;
        for (long long i = N; i > 0; i /= 2)
        {
            if (i % 2 == 1) // 如果N是奇数，需要再乘以一次自己，否则N是偶数，直接平方即可
            {
                ans = ans * current_product;
            }
            current_product = current_product * current_product;
        }
        return ans;
    }
};