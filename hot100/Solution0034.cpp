#include <vector>
using namespace std;
// 给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。

// 如果数组中不存在目标值 target，返回 [-1, -1]。

// 你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。

// 示例 1：

// 输入：nums = [5,7,7,8,8,10], target = 8
// 输出：[3,4]
// 示例 2：

// 输入：nums = [5,7,7,8,8,10], target = 6
// 输出：[-1,-1]
// 示例 3：

// 输入：nums = [], target = 0
// 输出：[-1,-1]

// 提示：

// 0 <= nums.length <= 105
// -109 <= nums[i] <= 109
// nums 是一个非递减数组
// -109 <= target <= 109
class Solution
{
private:
    int begin = -1;
    int end = -1;

public:
    vector<int> searchRange(vector<int> &nums, int target)
    {
        vector<int> result;
        findRange(nums, 0, nums.size() - 1, target);
        result.push_back(begin);
        result.push_back(end);
        return result;
    }

private:
    void findRange(vector<int> &nums, int leftIndex, int rightIndex, int target)
    {
        if (leftIndex > rightIndex) // left > right 时，这表示我们的搜索区间已经为空了
            return;
        int mid = leftIndex + (rightIndex - leftIndex) / 2;
        if (nums[mid] == target)
        {
            if (begin == -1 || mid < begin)
                begin = mid;
            if (end == -1 || mid > end)
                end = mid;
            findRange(nums, leftIndex, mid - 1, target);
            findRange(nums, mid + 1, rightIndex, target);
        }
        else if (nums[mid] < target)
            findRange(nums, mid + 1, rightIndex, target);
        else
            findRange(nums, leftIndex, mid - 1, target);
    }
};

// 方法二：while实现
class Solution3
{
public:
    vector<int> searchRange(vector<int> &nums, int target)
    {
        int begin = -1;
        int end = -1;
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
            {
                begin = mid;
                end = mid;
                while (begin > 0 && nums[begin - 1] == target)
                    --begin;
                while (end < nums.size() - 1 && nums[end + 1] == target)
                    ++end;
                return {begin, end};
            }
            else if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return {-1, -1};
    }
};