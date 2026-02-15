#include <cmath>
using namespace std;
// 给你一个非负整数 x ，计算并返回 x 的 算术平方根 。

// 由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。

// 注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。

// 示例 1：

// 输入：x = 4
// 输出：2
// 示例 2：

// 输入：x = 8
// 输出：2
// 解释：8 的算术平方根是 2.82842..., 由于返回类型是整数，小数部分将被舍去。

// 提示：

// 0 <= x <= 231 - 1
class Solution
{
public:
    int mySqrt(int x)
    {
        int left = 0, right = x;
        int ans = -1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if ((long long)mid * mid <= x) // 注意防止溢出
            {
                ans = mid;      // 记录当前的mid
                left = mid + 1; // 继续在右侧查找更大的mid
            }
            else
            {
                right = mid - 1; // 在左侧查找
            }
        }
        return ans;
    }
};

// 没啥用
class Solution2
{
public:
    int mySqrt(int x)
    {
        int left = 1, right = 1 * 1;
        while (right <= x / right) // 防止溢出
        {
            left = right;
            right = right * 2; // 指数增长
        }
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (mid <= x / mid) // 防止溢出
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return right;
    }
};

// x^0.5 = e^(0.5lnx)
class Solution3
{
public:
    int mySqrt(int x)
    {
        if (x == 0)
            return 0;
        int ans = exp(0.5 * log(x));
        return (long long)(ans + 1) * (ans + 1) <= x ? ans + 1 : ans;
    }
};

// 牛顿迭代法：二次收敛，比二分法快
// f(y) = y^2 - x
// f'(y) = 2y
// y = y - f(y) / f'(y) = y - (y^2 - x) / 2y = (y + x / y) / 2
class Solution4
{
public:
    int mySqrt(int x)
    {
        if (x == 0)
            return 0;
        double y = x;
        while (true)
        {
            double ny = (y + x / y) / 2;
            if (fabs(ny - y) < 1e-7) // 精度足够
                break;
            y = ny;
        }
        return (int)y;
    }
};