using namespace std;
// 给定一个正整数 n，编写一个函数，获取一个正整数的二进制形式并返回其二进制表达式中 设置位 的个数（也被称为汉明重量）。

// 示例 1：

// 输入：n = 11
// 输出：3
// 解释：输入的二进制串 1011 中，共有 3 个设置位。
// 示例 2：

// 输入：n = 128
// 输出：1
// 解释：输入的二进制串 10000000 中，共有 1 个设置位。
// 示例 3：

// 输入：n = 2147483645
// 输出：30
// 解释：输入的二进制串 1111111111111111111111111111101 中，共有 30 个设置位。

// 提示：

// 1 <= n <= 231 - 1

// 进阶：

// 如果多次调用这个函数，你将如何优化你的算法？
class Solution
{
public:
    int hammingWeight(int n)
    {
        int count = 0;
        while (n > 0)
        {
            count += n & 1; // 统计最低位
            n >>= 1;
        }
        return count;
    }
};

class Solution2
{
public:
    int hammingWeight(int n)
    {
        int count = 0;
        for (int i = 0; i < 32; i++)
        {
            count += (n >> i) & 1; // 统计每一位
        }
        return count;
    }
};

// n & (n−1)，其运算结果恰为把 n 的二进制位中的最低位的 1 变为 0 之后的结果。
class Solution3
{
public:
    int hammingWeight(int n)
    {
        int count = 0;
        while (n > 0)
        {
            n &= (n - 1); // 消去最低位的1
            count++;
        }
        return count;
    }
};
