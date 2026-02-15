#include <vector>
using namespace std;
// 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

// 子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。

// 示例 1：

// 输入：nums = [10,9,2,5,3,7,101,18]
// 输出：4
// 解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
// 示例 2：

// 输入：nums = [0,1,0,3,2,3]
// 输出：4
// 示例 3：

// 输入：nums = [7,7,7,7,7,7,7]
// 输出：1

// 提示：

// 1 <= nums.length <= 2500
// -104 <= nums[i] <= 104

// 进阶：

// 你能将算法的时间复杂度降低到 O(n log(n)) 吗?
// 方法一：动态规划
class Solution
{
public:
    // 注意：可以不连续
    int lengthOfLIS(vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        vector<int> dp(nums.size(), 1);
        int result = 1;
        for (int i = 1; i < nums.size(); ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (nums[i] > nums[j])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
            result = max(result, dp[i]);
        }
        return result;
    }
};

// 方法二：二分查找：想要子序列最长，则总是希望找到最小的元素。
// 而又希望其有序性，因此，可以逐个遍历nums，维护一个最长的单调递增子序列数组mono
// 如果nums中的元素比mono中的最大元素还大，则可以直接添加到mono中
// 如果nums中的元素小于等于mono中的最大元素，则可以用它来替代mono中第一个大于等于它的元素
class Solution2
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        vector<int> mono;
        for (int num : nums)
        {
            auto it = lower_bound(mono.begin(), mono.end(), num); // 在mono中找到第一个大于等于num的元素
            if (it == mono.end())
                mono.push_back(num);
            else
                *it = num;
        }
        return mono.size();
    }
};