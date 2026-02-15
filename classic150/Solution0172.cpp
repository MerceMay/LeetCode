#include <vector>
using namespace std;
// 给定一个整数 n ，返回 n! 结果中尾随零的数量。

// 提示 n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1
// 有多少个因子 5 就有多少个尾随零，因此需要计算n中有多少个5的倍数
// 但是25会贡献两个5，因此需要计算n中有多少个25的倍数
// 125会贡献三个5，因此需要计算n中有多少个125的倍数
// 每次n除以5 25 125...就可以知道一共有多少个5的倍数
// 时间复杂度为O(log5N)
class Solution
{
public:
    int trailingZeroes(int n)
    {
        int count = 0;
        while (n)
        {
            n /= 5;
            count += n;
        }
        return count;
    }
};

// 时间复杂度为O(N)
class Solution2
{
public:
    int trailingZeroes(int n)
    {
        int count = 0;
        for (int i = 5; i <= n; i *= 5)
        {
            for (int j = i; j % 5 == 0; j /= 5)
                count++;
        }
        return count;
    }
};