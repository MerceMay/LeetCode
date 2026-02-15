#include <vector>
#include <algorithm>
using namespace std;
// 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

// 子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。
// 你能将算法的时间复杂度降低到 O(n log(n)) 吗?
// 要求使用二分查找优化
class Solution
{
public:
    // 假设遍历到第i个数，现在已经有了一个单调递增的序列mono，
    // 如果nums[i]比mono中的所有数都大，那么就把nums[i]接在mono的后面
    // 否则在mono中找到第一个比nums[i]大的数，把它替换成nums[i]
    // 这样做的好处是，mono的长度不断增加，而替换成更小的数
    // 可以让后续的数有更大的概率接在mono的后面，从而增加mono的长度
    int lengthOfLIS(vector<int> &nums)
    {
        vector<int> mono;
        for (int num : nums)
        {
            auto it = lower_bound(mono.begin(), mono.end(), num);
            if (it == mono.end())
            {
                mono.push_back(num);
            }
            else
            {
                *it = num;
            }
        }
        return mono.size();
    }
};

class Solution2
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        vector<int> dp(n, 1);
        // dp[i]表示以nums[i]结尾的最长递增子序列的长度
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[i] > nums[j])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};