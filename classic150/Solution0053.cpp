#include <vector>
#include <climits>
using namespace std;
// 给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

// 子数组是数组中的一个连续部分。

// 进阶：如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的 分治法 求解。
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int max_sum = nums[0];
        // current_sum表示以当前元素结尾的最大子数组和，如果遍历一个元素后current_sum减小，开始计算
        int current_sum = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            current_sum = max(nums[i], current_sum + nums[i]); // 如果当前元素大于当前和，则重新开始计算
            max_sum = max(max_sum, current_sum);
        }
        return max_sum;
    }
};

// 遍历到一个数的时候，要么这个数在区间内，要么不在区间内，因此，可以使用分治法：
// 分别算出左半部分的最大子数组和，右半部分的最大子数组和，以及跨越中点的最大子数组和，三者取最大值即为所求。
class Solution2
{
public:
    int maxSubArray(vector<int> &nums)
    {
        return combine(nums, 0, nums.size() - 1);
    }

private:
    int combine(vector<int> &nums, int left, int right)
    {
        if (left == right)
        {
            return nums[left];
        }
        int mid = (left + right) / 2;
        int left_sum = combine(nums, left, mid);       // 左子区间的最大子数组和
        int right_sum = combine(nums, mid + 1, right); // 左右区间的最大子数组和

        int cross_sum = 0;
        int left_max = INT_MIN;  // 包含mid的左侧最大子数组和
        int right_max = INT_MIN; // 包含mid的右侧最大子数组和

        // 计算包含mid的最大子数组和
        for (int i = mid; i >= left; i--)
        {
            cross_sum += nums[i];
            left_max = max(left_max, cross_sum);
        }

        cross_sum = 0;
        for (int i = mid + 1; i <= right; i++)
        {
            cross_sum += nums[i];
            right_max = max(right_max, cross_sum);
        }

        return max(left_sum, max(right_sum, left_max + right_max)); // 三者取最大值
    }
};

class Solution3
{
    struct Info
    {
        int lSum; // 以左端点为起点的最大子数组和
        int rSum; // 以右端点为终点的最大子数组和
        int mSum; // 最大子数组和
        int iSum; // 区间和
    };

public:
    int maxSubArray(vector<int> &nums)
    {
        return Conquer(nums, 0, nums.size() - 1).mSum;
    }

private:
    Info Conquer(vector<int> &nums, int left, int right)
    {
        if (left == right)
        {
            return {nums[left], nums[left], nums[left], nums[left]};
        }
        int mid = (left + right) / 2;
        Info lSub = Conquer(nums, left, mid);
        Info rSub = Conquer(nums, mid + 1, right);
        return pushUp(lSub, rSub);
    }

    Info pushUp(Info lSub, Info rSub)
    {
        int iSum = lSub.iSum + rSub.iSum;
        int lSum = max(lSub.lSum, lSub.iSum + rSub.lSum);
        int rSum = max(rSub.rSum, rSub.iSum + lSub.rSum);
        int mSum = max(max(lSub.mSum, rSub.mSum), lSub.rSum + rSub.lSum);
        return {lSum, rSum, mSum, iSum};
    }
};