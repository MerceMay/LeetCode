#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// 给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。

// 请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。

// 示例 1：

// 输入：nums = [1,2,0]
// 输出：3
// 解释：范围 [1,2] 中的数字都在数组中。
// 示例 2：

// 输入：nums = [3,4,-1,1]
// 输出：2
// 解释：1 在数组中，但 2 没有。
// 示例 3：

// 输入：nums = [7,8,9,11,12]
// 输出：1
// 解释：最小的正数 1 没有出现。

// 提示：

// 1 <= nums.length <= 105
// -231 <= nums[i] <= 231 - 1

// 思路：如果[1,n]全有，则答案是n+1；否则是[1,n]中第一个缺失的正数。
// 方法一：置换。把符合[1,n]的数放到对应的下标位置，这样利用下标记录[1,n]中出现的数。
// 对于不符合[1,n]的数，不用管，不会影响结果。
// 如果置换的两者相同，说明这个数已经在正确的位置上了，不用交换
class Solution
{
public:
    int firstMissingPositive(vector<int> &nums)
    {
        int n = nums.size();
        // 第一次遍历，对于非正数和大于n的可以忽略。要交换的时候，如果两者相等则跳过
        for (int i = 0; i < n; i++)
        {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
            {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        // 第二次遍历，寻找第一个缺失的正数
        for (int i = 0; i < n; i++)
        {
            if (nums[i] != i + 1)
            {
                return i + 1;
            }
        }
        return n + 1;
    }
};

// 方法二：不在[1,n]中的数没有用，可以替换成n+1。
// 同样，利用下标，把对应下标的值换成负数
// 这样，如果[1,n]全有，则全是负数，结果是n+1；否则，返回第一个正数的下标+1
class Solution
{
public:
    int firstMissingPositive(vector<int> &nums)
    {
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            if (nums[i] <= 0 || nums[i] > n)
            {
                nums[i] = n + 1; // 替换成n+1
            }
        }

        for (int i = 0; i < n; i++)
        {
            int num = abs(nums[i]);
            if (num <= n)
            {
                nums[num - 1] = -abs(nums[num - 1]);
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (nums[i] > 0)
            {
                return i + 1;
            }
        }
        return n + 1;
    }
};