#include <vector>
using namespace std;
// 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

// 请必须使用时间复杂度为 O(log n) 的算法。

// 示例 1:

// 输入: nums = [1,3,5,6], target = 5
// 输出: 2
// 示例 2:

// 输入: nums = [1,3,5,6], target = 2
// 输出: 1
// 示例 3:

// 输入: nums = [1,3,5,6], target = 7
// 输出: 4

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
        return findMid(nums, 0, nums.size() - 1, target);
    }

private:
    int findMid(vector<int> &nums, int left, int right, int target)
    {
        if (left > right) // left > right 时，这表示我们的搜索区间已经为空了.当 left 最终越过 right 时，它刚好停在了所有比 target 小的元素之后、所有比 target 大的元素之前的位置。这个位置，就是 target 的正确插入点。
            return left;
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] < target)
            return findMid(nums, mid + 1, right, target);
        else
            return findMid(nums, left, mid - 1, target);
    }
};

// 方法二：while实现
class Solution2
{
public:
    int searchInsert(vector<int> &nums, int target)
    {
        int left = 0;
        int right = nums.size() - 1;
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