using namespace std;
// 给你两个整数 left 和 right ，表示区间 [left, right] ，返回此区间内所有数字 按位与 的结果（包含 left 、right 端点）。
// left和right都大于等于0，因此结果前面肯定全是0，找出left和right最高位的1，如果位数不相等，结果就是0，否则就是该位数对应的数
class Solution
{
public:
    int rangeBitwiseAnd(int left, int right)
    {
        int shift = 0;
        // 找到left和right最高位相等的位置，如果最高位的1不相等，shift停下来的位置就是0，否则就是1
        while (left != right)
        {
            left >>= 1;
            right >>= 1;
            shift++;
        }
        return left << shift; // 将left或right左移shift位，补齐后返回
    }
};

// Brian Kernighan 算法：number 和 number−1 之间进行按位与运算后，number 中最右边的 1 会被抹去变成 0
class Solution2
{
public:
    int rangeBitwiseAnd(int m, int n)
    {
        while (m < n)
        {
            // 对数字 n 迭代地应用上述技巧，清除最右边的 1，直到它小于或等于 m，此时非公共前缀部分的 1 均被消去
            n = n & (n - 1);
        }
        return n;
    }
};