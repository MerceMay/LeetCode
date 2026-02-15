#include <vector>
#include <climits>
using namespace std;
// 已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次 旋转 后，得到输入数组。例如，原数组 nums = [0,1,2,4,5,6,7] 在变化后可能得到：
// 若旋转 4 次，则可以得到 [4,5,6,7,0,1,2]
// 若旋转 7 次，则可以得到 [0,1,2,4,5,6,7]
// 注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0], a[1], a[2], ..., a[n-2]] 。

// 给你一个元素值 互不相同 的数组 nums ，它原来是一个升序排列的数组，并按上述情形进行了多次旋转。请你找出并返回数组中的 最小元素 。

// 你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。
// 必然有一边是有序的，如果右边有序，则最小值可以先更新为nums[mid]，然后在左边找，否则在右边找
class Solution
{
private:
    int minVal = INT_MAX;

public:
    int findMin(vector<int> &nums)
    {
        binarySearch(nums, 0, nums.size() - 1);
        return minVal;
    }

private:
    void binarySearch(vector<int> &nums, int left, int right)
    {
        if (left > right)
            return;
        int mid = left + (right - left) / 2;
        if (nums[mid] <= nums[right]) // 右边有序
        {
            minVal = min(minVal, nums[mid]);
            binarySearch(nums, left, mid - 1);
        }
        else // 左边有序
            binarySearch(nums, mid + 1, right);
    }
};

// while版
class Solution2
{
public:
    int findMin(vector<int> &nums)
    {
        int n = nums.size();
        int left = 0, right = n - 1;
        int minVal = INT_MAX;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= nums[right]) // 右边有序
            {
                minVal = min(minVal, nums[mid]);
                right = mid - 1;
            }
            else // 左边有序
                left = mid + 1;
        }
        return minVal;
    }
};

// 翻转后的数组中，先增加后突然减少然后再增加，这个地方就是最小值。
// 记两端增加的部分分别为A1和A2，中间减少的部分为B。
// 因此，如果mid和right都在A2，即nums[mid] < nums[right]，则最小值在A1和B中，令right = mid。
// 如果mid在A1，right在B，即nums[mid] > nums[right]，则最小值在mid和right之间，令left = mid + 1。
// mid和right永远不可能同时在A1中
class Solution3
{
public:
    int findMin(vector<int> &nums)
    {
        int n = nums.size();
        int left = 0, right = n - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < nums[right]) // mid在A2，right在A2
                right = mid;
            else // mid在A1，right在B
                left = mid + 1;
        }
        return nums[left];
    }
};