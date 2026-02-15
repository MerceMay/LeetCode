#include <vector>
#include <unordered_map>
using namespace std;
// 给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。

// 你必须设计并实现线性时间复杂度的算法且使用常数级空间来解决此问题。

// 对每一位考虑，遍历数组，统计每一位的和 mod 3 ，出现3次的数mod3后为0，出现1次的数mod3后为1
class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        int result = 0;
        for (int i = 0; i < 32; i++) // int是32位
        {
            int bitSum = 0; // 统计第i位的和
            for (int num : nums)
                bitSum += (num >> i) & 1; // 将num右移i位后与1做与运算，得到第i位的值
            result |= (bitSum % 3) << i;  // 将第i位的值左移i位后与result做或运算，更新result
        }
        return result;
    }
};

class Solution2
{
public:
    int singleNumber(vector<int> &nums)
    {
        unordered_map<int, int> freq;
        for (int num : nums)
        {
            ++freq[num];
        }
        int ans = 0;
        for (auto [num, occ] : freq)
        {
            if (occ == 1)
            {
                ans = num;
                break;
            }
        }
        return ans;
    }
};

// 对于一个数，每次遍历到它时，在总体里面的取值情况是0, 1, 2;
// 因此，考虑使用一个变量记录0, 1, 2三种状态。但是由于只有二进制，需要使用两个变量
// 根据每次遍历的x，更新状态
// 00 -> 01 -> 10 -> 00
// 可以得到a = a = (~a & b & x) | (a & ~b & ~x); b = ~a & (b ˆ x)
class Solution3
{
public:
    int singleNumber(vector<int> &nums)
    {
        int a = 0, b = 0;
        for (int num : nums)
        {
            tie(a, b) = pair{(~a & b & num) | (a & ~b & ~num), ~a & (b ^ num)};
        }
        return b;
    }
};

// 优化a的表达式
class Solution4
{
public:
    int singleNumber(vector<int> &nums)
    {
        int a = 0, b = 0;
        for (int num : nums)
        {
            b = ~a & (b ^ num);
            a = ~b & (a ^ num);
        }
        return b;
    }
};