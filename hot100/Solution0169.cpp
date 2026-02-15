#include <vector>
using namespace std;
// 给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。

// 你可以假设数组是非空的，并且给定的数组总是存在多数元素。

// 进阶：尝试设计时间复杂度为 O(n)、空间复杂度为 O(1) 的算法解决此问题。

// 摩尔投票法
// 假设相同数属于同一个党派
// 相同党派投赞同票，不同党派投反对票
// 最后肯定会剩下正数的票，而持有这个票的就是多数党派
class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        int candidate;
        int count = 0;
        for (int num : nums)
        {
            if (count == 0)
            {
                candidate = num;
                count = 1;
            }
            else if (num == candidate)
                count++;
            else
                count--;
        }
        return candidate;
    }
};