#include <vector>
using namespace std;
// 给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。

// 你可以假设数组是非空的，并且给定的数组总是存在多数元素。

// 进阶：尝试设计时间复杂度为 O(n)、空间复杂度为 O(1) 的算法解决此问题。
class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        int candidate = nums[0];
        int votes = 1;
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] == candidate)
                votes++;
            else
                votes--;
            if (votes == 0)
            {
                candidate = nums[i];
                votes = 1;
            }
        }
        return candidate;
    }
};