#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// 给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

// 子数组是数组中的一个连续部分。

// 示例 1：

// 输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
// 输出：6
// 解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
// 示例 2：

// 输入：nums = [1]
// 输出：1
// 示例 3：

// 输入：nums = [5,4,-1,7,8]
// 输出：23

// 提示：

// 1 <= nums.length <= 105
// -104 <= nums[i] <= 104

// 进阶：如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的 分治法 求解。
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int max_sum = nums[0];
        int current_sum = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            current_sum = max(nums[i], current_sum + nums[i]); // 如果当前元素大于当前和，则重新开始计算
            max_sum = max(max_sum, current_sum);
        }
        return max_sum;
    }
};

// 时间复杂度：是 O(n log n)
class Solution2
{
public:
    int Combine(vector<int> &arr, int left, int right)
    {
        if (left == right)
        {
            return arr[left];
        }
        int mid = (left + right) / 2;
        int left_sum = Combine(arr, left, mid);       // 左子区间的最大子数组和
        int right_sum = Combine(arr, mid + 1, right); // 左右区间的最大子数组和

        int cross_sum = 0;
        int left_max = INT_MIN;
        int right_max = INT_MIN;

        // 计算包含mid的最大子数组和
        for (int i = mid; i >= left; i--)
        {
            cross_sum += arr[i];
            left_max = max(left_max, cross_sum);
        }

        cross_sum = 0;
        for (int i = mid + 1; i <= right; i++)
        {
            cross_sum += arr[i];
            right_max = max(right_max, cross_sum);
        }

        return max(left_sum, max(right_sum, left_max + right_max));
    }

    int maxSubArray(vector<int> &nums)
    {
        return Combine(nums, 0, nums.size() - 1);
    }
};

// 更精妙的
class Solution3
{
public:
    struct Status
    {
        int interval_sum,                      // 区间和
            left_as_endpoint_max_segment_sum,  // 子区间作为左端点的最大和
            right_as_endpoint_max_segment_sum, // 子区间作为右端点的最大和
            segment_max_sum;                   // 子区间和
    };

    Status Combine(Status left_subinterval_status, Status right_subinterval_status)
    {
        Status status;
        status.interval_sum = left_subinterval_status.interval_sum + right_subinterval_status.interval_sum;
        status.left_as_endpoint_max_segment_sum = max(left_subinterval_status.left_as_endpoint_max_segment_sum, left_subinterval_status.interval_sum + right_subinterval_status.left_as_endpoint_max_segment_sum);
        status.right_as_endpoint_max_segment_sum = max(right_subinterval_status.right_as_endpoint_max_segment_sum, right_subinterval_status.interval_sum + left_subinterval_status.right_as_endpoint_max_segment_sum);
        status.segment_max_sum = max(max(left_subinterval_status.segment_max_sum, right_subinterval_status.segment_max_sum), left_subinterval_status.right_as_endpoint_max_segment_sum + right_subinterval_status.left_as_endpoint_max_segment_sum);
        return status;
    }

    Status Conquer(vector<int> &arr, int left_endpoint, int right_endpoint)
    {
        if (left_endpoint == right_endpoint)
        {
            return Status{arr[left_endpoint], arr[left_endpoint], arr[left_endpoint], arr[left_endpoint]};
        }
        int mid = (left_endpoint + right_endpoint) / 2;
        Status left_subinterval_status = Conquer(arr, left_endpoint, mid);
        Status right_subinterval_status = Conquer(arr, mid + 1, right_endpoint);
        return Combine(left_subinterval_status, right_subinterval_status);
    }

    int maxSubArray(vector<int> &nums)
    {
        return Conquer(nums, 0, nums.size() - 1).segment_max_sum;
    }
};