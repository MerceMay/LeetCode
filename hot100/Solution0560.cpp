#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
// 给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。

// 子数组是数组中元素的连续非空序列。

// 示例 1：

// 输入：nums = [1,1,1], k = 2
// 输出：2
// 示例 2：

// 输入：nums = [1,2,3], k = 3
// 输出：2

// 提示：

// 1 <= nums.length <= 2 * 104
// -1000 <= nums[i] <= 1000
// -107 <= k <= 107
class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> prefixSumCount; // 存储前缀和及其出现次数
        prefixSumCount[0] = 1;
        int currentSum = 0;
        int count = 0;
        for (int num : nums)
        {
            currentSum += num; // 更新当前前缀和
            if (prefixSumCount.find(currentSum - k) != prefixSumCount.end())
            {
                count += prefixSumCount[currentSum - k];
            }
            prefixSumCount[currentSum]++;
        }
        return count;
    }
};