#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
// 峰值元素是指其值严格大于左右相邻值的元素。

// 给你一个整数数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。

// 你可以假设 nums[-1] = nums[n] = -∞ 。

// 你必须实现时间复杂度为 O(log n) 的算法来解决此问题。
class Solution
{
public:
    int findPeakElement(vector<int> &nums)
    {
        return findPeak(nums, 0, nums.size() - 1);
    }

private:
    // leftValue表示left左边的值，rightValue表示right右边的值
    int findPeak(vector<int> &nums, int left, int right)
    {
        if (left == right) // 只有一个元素
            return left;
        int mid = left + (right - left) / 2;
        int leftValue = (mid - 1 >= 0) ? nums[mid - 1] : INT_MIN;
        int rightValue = (mid + 1 < nums.size()) ? nums[mid + 1] : INT_MIN;
        if (nums[mid] > leftValue && nums[mid] > rightValue)
            return mid;
        else if (nums[mid] < rightValue) // 右边有更大的值，说明峰值一定可以在右边找到
            return findPeak(nums, mid + 1, right);
        else // 左边有更大的值，说明峰值一定可以在左边找到
            return findPeak(nums, left, mid - 1);
    }
};

// 寻找最大值，时间复杂度O(n)
class Solution2
{
public:
    int findPeakElement(vector<int> &nums)
    {
        return max_element(nums.begin(), nums.end()) - nums.begin();
    }
};

//  爬坡：
// 如果 nums[i−1]<nums[i]>nums[i+1]，那么位置 i 就是峰值位置，我们可以直接返回 i 作为答案；
// 如果 nums[i−1]<nums[i]<nums[i+1]，那么位置 i 处于上坡，我们需要往右走，即 i←i+1；
// 如果 nums[i−1]>nums[i]>nums[i+1]，那么位置 i 处于下坡，我们需要往左走，即 i←i−1；
// 如果 nums[i−1]>nums[i]<nums[i+1]，那么位置 i 位于山谷，两侧都是上坡，我们可以朝任意方向走。

// 总结：
// 如果 nums[i]<nums[i+1]，那么我们往右走；
// 如果 nums[i]>nums[i+1]，那么我们往左走。
class Solution3
{
public:
    int findPeakElement(vector<int> &nums)
    {
        int n = nums.size();
        int index = rand() % n; // 随机选一个位置开始
        auto getValue = [&](int i)
        {
            if (i < 0 || i >= n)
                return INT_MIN;
            return nums[i];
        };
        while (true)
        {
            int leftValue = getValue(index - 1);
            int rightValue = getValue(index + 1);
            if (nums[index] > leftValue && nums[index] > rightValue)
                return index;
            else if (nums[index] < rightValue) // 右边有更大的值，说明峰值一定可以在右边找到
                index++;
            else // 左边有更大的值，说明峰值一定可以在左边找到
                index--;
        }
    }
};

// 爬坡加二分查找
class Solution4
{
public:
    int findPeakElement(vector<int> &nums)
    {
        int n = nums.size();
        auto getValue = [&](int i)
        {
            if (i < 0 || i >= n)
                return INT_MIN;
            return nums[i];
        };
        int left = 0, right = n - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            int midValue = getValue(mid);
            int rightValue = getValue(mid + 1);
            if (midValue < rightValue) // 右边有更大的值，说明峰值一定可以在右边找到
                left = mid + 1;
            else // 左边有更大的值，说明峰值一定可以在左边找到
                right = mid;
        }
        return left;
    }
};