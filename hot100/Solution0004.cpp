#include <vector>
#include <climits>
#include <memory>
using namespace std;
// 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。

// 算法的时间复杂度应该为 O(log (m+n)) 。

// 示例 1：

// 输入：nums1 = [1,3], nums2 = [2]
// 输出：2.00000
// 解释：合并数组 = [1,2,3] ，中位数 2
// 示例 2：

// 输入：nums1 = [1,2], nums2 = [3,4]
// 输出：2.50000
// 解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5

// 提示：

// nums1.length == m
// nums2.length == n
// 0 <= m <= 1000
// 0 <= n <= 1000
// 1 <= m + n <= 2000
// -106 <= nums1[i], nums2[i] <= 106

// 方法一：
// 在 nums1 中找到一个分割点 cut_point_1，它将 nums1 分成左右两部分：nums1_left 和 nums1_right。
// 在 nums2 中找到一个分割点 cut_point_2，它将 nums2 分成左右两部分：nums2_left 和 nums2_right。
// 使得len(nums1_left) + len(nums2_left) == (m+n+1)/2。
// 这样，左半部分的元素个数要么和右半部分相等（当 m+n 为偶数时），要么比右半部分多一个（当 m+n 为奇数时）。
// cut_point_1表示nums1中在cut_point_1左边一共有cut_point_1个元素；
// 因此，设计cut_point_1 = nums1_left.size(); cut_point_2 = nums2_left.size()
// 满足max(nums1_left, nums2_left) <= min(nums1_right, nums2_right)。即left_max <= right_min;
class Solution
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        // 使得nums1的大小小于nums2。
        // 因为cut_point_1 + cut_point_2 === (m+n+1)/2。如果让更长的数组2的cut_point_2来取值，cut_point_1可能出现负数
        if (nums1.size() > nums2.size())
            return findMedianSortedArrays(nums2, nums1);
        int m = nums1.size();
        int n = nums2.size();
        // 一个m长度的数组，切点一共有m+1中情况。因此，left和right和常规的二分法不同，这里[left, right]表示的是切点cut_point_1的取值范围
        int left = 0, right = m;
        int left_max = 0, right_min = 0; // 这两个值就是切点的左右边界
        while (left <= right)            // 直到遍历完整个数组1
        {
            // 每次找到两个数组的切点。
            // 两个的切点是互斥的，即，数组1的切点在1中越靠右，数组2的切点在2中越靠左
            int cut_point_1 = left + (right - left) / 2; // 二分法
            int cut_point_2 = (m + n + 1) / 2 - cut_point_1;

            // 不考虑边界的情况下：// nums1[cut_point_1] = nums1_right_min;nums2[cut_point_2] = nums2_right_min
            int nums1_left_max = (cut_point_1 == 0 ? INT_MIN : nums1[cut_point_1 - 1]);
            int nums1_right_min = (cut_point_1 == m ? INT_MAX : nums1[cut_point_1]);
            int nums2_left_max = (cut_point_2 == 0 ? INT_MIN : nums2[cut_point_2 - 1]);
            int nums2_right_min = (cut_point_2 == n ? INT_MAX : nums2[cut_point_2]);

            // 条件一：nums1_left_max <= nums2_right_min：即if分支，这部分是满足的。
            // 条件二：nums2_left_max <= nums1_right_min：这部分可能满足，也可能不满足。
            // 至少当前的切分结果是 有希望的，即数组1的切点还可以往右移。
            // 数组1的切点往右移的同时，数组2的切点往左移。所以，在数组1移动的过程中，第二个条件会逐渐满足
            if (nums1_left_max <= nums2_right_min)
            {
                // 因为不确定条件二是否满足，所以需要暂时保存left_max和right_min
                left_max = max(nums1_left_max, nums2_left_max);
                right_min = min(nums1_right_min, nums2_right_min);
                left = cut_point_1 + 1;
            }
            else // 条件一不满足，直接左移
            {
                right = cut_point_1 - 1;
            }
        }
        // 如果数组长度是偶数，则切点在正中间，left_max和right_min刚好在两边；如果是奇数，left_max就是中间的值
        return (m + n) % 2 == 0 ? (left_max + right_min) / 2.0 : left_max;
    }
};

// 方法二：从找第k个元素来进行二分
// 我们在 nums1 中取第 k/2 个元素：pivot1 = nums1[k/2 - 1]。
// 我们在 nums2 中取第 k/2 个元素：pivot2 = nums2[k/2 - 1]。
// 情况一：pivot1 <= pivot2,安全地把 nums1 的这 k/2 个元素排除掉。
// 排除掉之后，问题就变成了：在剩下的元素中，找第 k - k/2 小的元素
// 边界情况
// nums1 或 nums2 变空： 如果一个数组的所有元素都被排除了，那问题就简单了，直接在另一个数组里找第 k 小的元素就行。
class Solution2
{
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int total_length = nums1.size() + nums2.size();
        if (total_length % 2 == 1)
            return getKthElement(nums1, nums2, total_length / 2 + 1);
        else
            return getKthElement(nums1, nums2, total_length / 2 + 1) + getKthElement(nums1, nums2, total_length / 2) / 2.0;
    }

private:
    int getKthElement(vector<int> &nums1, vector<int> &nums2, int k)
    {
        int index1 = 0;
        int index2 = 0;
        while (true)
        {
            if (index1 == nums1.size()) // nums1排除空了
                return nums2[index2 + k - 1];
            if (index2 == nums2.size()) // nums2排除空了
                return nums1[index1 + k - 1];
            if (k == 1) // k已经缩小到1了
                return min(nums1[index1], nums2[index2]);

            int newIndex1 = min(index1 + k / 2 - 1, static_cast<int>(nums1.size() - 1));
            int newIndex2 = min(index2 + k / 2 - 1, static_cast<int>(nums2.size() - 1));
            int pivot1 = nums1[newIndex1], pivot2 = nums2[newIndex2];
            if (pivot1 <= pivot2)
            {
                k -= (newIndex1 - index1 + 1);
                index1 = newIndex1 + 1;
            }
            else
            {
                k -= (newIndex2 - index2 + 1);
                index2 = newIndex2 + 1;
            }
        }
    }
};