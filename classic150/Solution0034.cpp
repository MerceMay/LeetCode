#include <vector>
using namespace std;
// 给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。

// 如果数组中不存在目标值 target，返回 [-1, -1]。

// 你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。
class Solution
{
private:
    int start = -1;
    int end = -1;

public:
    vector<int> searchRange(vector<int> &nums, int target)
    {
        binarySearch(nums, 0, nums.size() - 1, target);
        return {start, end};
    }

private:
    void binarySearch(vector<int> &nums, int left, int right, int target)
    {
        if (left > right)
            return;
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
        {
            if (start == -1 || mid < start)
                start = mid;
            if (end == -1 || mid > end)
                end = mid;
            binarySearch(nums, left, mid - 1, target);
            binarySearch(nums, mid + 1, right, target);
        }
        else if (nums[mid] < target)
            binarySearch(nums, mid + 1, right, target);
        else
            binarySearch(nums, left, mid - 1, target);
    }
};

// while版
class Solution2
{
public:
    vector<int> searchRange(vector<int> &nums, int target)
    {
        int n = nums.size();
        int left = 0, right = n - 1;
        int start = -1, end = -1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
            {
                if (start == -1 || mid < start)
                    start = mid;
                if (end == -1 || mid > end)
                    end = mid;
                // 向两边扩展
                int l = mid - 1, r = mid + 1;
                while (l >= left && nums[l] == target)
                {
                    start = l;
                    l--;
                }
                while (r <= right && nums[r] == target)
                {
                    end = r;
                    r++;
                }
                break; // 找到目标值后退出循环
            }
            else if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return {start, end};
    }
};