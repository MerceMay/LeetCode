#include <vector>
#include <algorithm>
using namespace std;
// 给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续 子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

// 测试用例的答案是一个 32-位 整数。

// 示例 1:

// 输入: nums = [2,3,-2,4]
// 输出: 6
// 解释: 子数组 [2,3] 有最大乘积 6。
// 示例 2:

// 输入: nums = [-2,0,-1]
// 输出: 0
// 解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。

// 提示:

// 1 <= nums.length <= 2 * 104
// -10 <= nums[i] <= 10
// nums 的任何子数组的乘积都 保证 是一个 32-位 整数
class Solution
{
public:
    int maxProduct(vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        int result = nums[0];
        int imax = nums[0], imin = nums[0];
        for (int i = 1; i < nums.size(); ++i)
        {
            if (nums[i] < 0)
                swap(imax, imin);
            imax = max(nums[i], imax * nums[i]);
            imin = min(nums[i], imin * nums[i]);
            result = max(result, imax);
        }
        return result;
    }
};

// 如果使用缓存
class Solution2
{
public:
    int maxProduct(vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        vector<int> imax(nums.size()), imin(nums.size());
        imax[0] = nums[0], imin[0] = nums[0];
        int result = nums[0];
        for (int i = 1; i < nums.size(); ++i)
        {
            int prev_max = imax[i - 1];
            int prev_min = imin[i - 1];
            // 如果当前数是负数，最大值可能由上一个最小乘积得到
            if (nums[i] < 0)
            {
                imax[i] = max(nums[i], prev_min * nums[i]);
                imin[i] = min(nums[i], prev_max * nums[i]);
            }
            else
            {
                imax[i] = max(nums[i], prev_max * nums[i]);
                imin[i] = min(nums[i], prev_min * nums[i]);
            }

            result = max(result, imax[i]);
        }
        return result;
    }
};