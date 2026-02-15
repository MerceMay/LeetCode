#include <iostream>
#include <vector>
using namespace std;
// 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

// 请注意 ，必须在不复制数组的情况下原地对数组进行操作。

// 示例 1:

// 输入: nums = [0,1,0,3,12]
// 输出: [1,3,12,0,0]
// 示例 2:

// 输入: nums = [0]
// 输出: [0]

// 提示:

// 1 <= nums.length <= 104
// -231 <= nums[i] <= 231 - 1

// 进阶：你能尽量减少完成的操作次数吗？

class Solution
{
public:
    void moveZeroes(vector<int> &nums)
    {
        // 要求不进行复制，说明需要使用指针。并且需要使用双指针
        int left = 0;  // 左指针指向非零的末尾；左指针左边全是非零元素
        int right = 0; // 右指针指向当前遍历的元素；右指针与左指针之间全是零

        while (right < nums.size())
        {
            if (nums[right] != 0)
            {
                swap(nums[left], nums[right]);
                left++;
            }
            right++;
        }
    }
};