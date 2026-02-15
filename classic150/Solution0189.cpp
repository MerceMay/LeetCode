#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
// 给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。

// 示例 1:

// 输入: nums = [1,2,3,4,5,6,7], k = 3
// 输出: [5,6,7,1,2,3,4]
// 解释:
// 向右轮转 1 步: [7,1,2,3,4,5,6]
// 向右轮转 2 步: [6,7,1,2,3,4,5]
// 向右轮转 3 步: [5,6,7,1,2,3,4]
// 示例 2:

// 输入：nums = [-1,-100,3,99], k = 2
// 输出：[3,99,-1,-100]
// 解释:
// 向右轮转 1 步: [99,-1,-100,3]
// 向右轮转 2 步: [3,99,-1,-100]

// 提示：

// 1 <= nums.length <= 105
// -231 <= nums[i] <= 231 - 1
// 0 <= k <= 105

// 进阶：

// 尽可能想出更多的解决方案，至少有 三种 不同的方法可以解决这个问题。
// 你可以使用空间复杂度为 O(1) 的 原地 算法解决这个问题吗？
class Solution
{
public:
    void rotate(vector<int> &nums, int k)
    {
        k = k % nums.size();
        reverse(nums.begin(), nums.begin() + nums.size() - k); // 反转前n-k个元素
        reverse(nums.begin() + nums.size() - k, nums.end());   // 反转后k个元素
        reverse(nums.begin(), nums.end());                     // 反转整个数组
    }
};

class Solution
{
public:
    void rotate(vector<int> &nums, int k)
    {
        k = k % nums.size();
        int count = gcd(nums.size(), k); // 求最大公约数
        for (int i = 0; i < count; i++)
        {
            int current = i;
            int prev = nums[i];
            do
            {
                int next = (current + k) % nums.size();
                swap(nums[next], prev);
                current = next;
            } while (i != current);
        }
    }
};