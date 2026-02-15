#include <vector>
#include <climits>
using namespace std;
// 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。

// 算法的时间复杂度应该为 O(log (m+n)) 。

// 方法：这里取切点cut_point_1, cut_point_2，其中cut_point_1 + cut_point_2 == (m+n+1)/2
// 当m+n为奇数时，左侧比右侧多一个元素，因此左侧的最大值就是中位数；当m+n为偶数时，左侧和右侧元素个数相等，中位数就是左侧最大值和右侧最小值的平均值
// 同时令cut_point_1 = nums1_left.size(); cut_point_2 = nums2_left.size()
// cut_point_1的取值范围是[0, m]，cut_point_2的取值范围是[0, n]，
// 因此和以往二分法不同， right = m，而不是m-1
class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size();
        int n = nums2.size();
        if (m > n)
            return findMedianSortedArrays(nums2, nums1);
        int left = 0, right = m;
        int left_max = 0, right_min = 0;
        while (left <= right)
        {
            int cut_point_1 = left + (right - left) / 2;
            int cut_point_2 = (m + n + 1) / 2 - cut_point_1;

            int left_max_1 = (cut_point_1 == 0) ? INT_MIN : nums1[cut_point_1 - 1];
            int right_min_1 = (cut_point_1 == m) ? INT_MAX : nums1[cut_point_1];
            int left_max_2 = (cut_point_2 == 0) ? INT_MIN : nums2[cut_point_2 - 1];
            int right_min_2 = (cut_point_2 == n) ? INT_MAX : nums2[cut_point_2];

            if (left_max_1 <= right_min_2)
            {
                left_max = max(left_max_1, left_max_2);
                right_min = min(right_min_1, right_min_2);
                // 右移，满足，还可以右移
                left = cut_point_1 + 1;
            }
            else
            {
                right = cut_point_1 - 1;
            }
        }
        return (m + n) % 2 ? left_max : (left_max + right_min) / 2.0;
    }
};

class Solution2
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size();
        int n = nums2.size();
        int total = m + n;
        if (total % 2 == 1)
        {
            return findKth(nums1, 0, nums2, 0, total / 2 + 1);
        }
        else
        {
            return (findKth(nums1, 0, nums2, 0, total / 2) + findKth(nums1, 0, nums2, 0, total / 2 + 1)) / 2.0;
        }
    }

private:
    int findKth(vector<int> &nums1, int start1, vector<int> &nums2, int start2, int k)
    {
        int m = nums1.size(), n = nums2.size();
        if (start1 >= m)
            return nums2[start2 + k - 1];
        if (start2 >= n)
            return nums1[start1 + k - 1];
        if (k == 1)
            return min(nums1[start1], nums2[start2]);

        int midVal1 = (start1 + k / 2 - 1 < m) ? nums1[start1 + k / 2 - 1] : INT_MAX;
        int midVal2 = (start2 + k / 2 - 1 < n) ? nums2[start2 + k / 2 - 1] : INT_MAX;

        if (midVal1 < midVal2)
        {
            return findKth(nums1, start1 + k / 2, nums2, start2, k - k / 2);
        }
        else
        {
            return findKth(nums1, start1, nums2, start2 + k / 2, k - k / 2);
        }
    }
};