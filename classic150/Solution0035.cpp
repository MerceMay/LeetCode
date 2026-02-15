#include <vector>
using namespace std;
// 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

// 请必须使用时间复杂度为 O(log n) 的算法。
// 提示:

// 1 <= nums.length <= 104
// -104 <= nums[i] <= 104
// nums 为 无重复元素 的 升序 排列数组
// -104 <= target <= 104
class Solution
{
public:
    int searchInsert(vector<int> &nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return left;
    }
};

// 递归
class Solution2
{
public:
    int searchInsert(vector<int> &nums, int target)
    {
        return helper(nums, target, 0, nums.size() - 1);
    }

private:
    int helper(vector<int> &nums, int target, int left, int right)
    {
        if (left > right)
            return left;
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] < target)
            return helper(nums, target, mid + 1, right);
        else
            return helper(nums, target, left, mid - 1);
    }
};