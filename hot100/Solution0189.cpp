#include <iostream>
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

// 方法一：暴力解。其实和方法三没什么区别
class Solution1
{
public:
    void rotate(vector<int> &nums, int k)
    {
        k = k % nums.size(); // 处理 k 大于数组长度的情况
        vector<int> temp(nums.size());
        for (int i = 0; i < k; i++)
        {
            temp[i] = nums[nums.size() - k + i];
        }
        for (int i = 0; i < nums.size() - k; i++)
        {
            temp[k + i] = nums[i];
        }
        nums = temp;
    }
};

// 方法二：使用反转
class Solution2
{
public:
    void rotate(vector<int> &nums, int k)
    {
        k = k % nums.size(); // 处理 k 大于数组长度的情况
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};

// 方法三：使用额外数组
class Solution3
{
public:
    void rotate(vector<int> &nums, int k)
    {
        k = k % nums.size(); // 处理 k 大于数组长度的情况
        vector<int> temp(nums.size());
        for (int i = 0; i < nums.size(); i++)
        {
            temp[(i + k) % nums.size()] = nums[i];
        }
        nums = temp;
    }
};

// 方法四：环状替换
// 下标为i的元素会被放在 (i+k)modn 的位置
// 因此，可以求出k和n的最大公约数gcd，再把i从0到gcd-1遍历
class Solution4
{
public:
    void rotate(vector<int> &nums, int k)
    {
        k = k % nums.size(); // 处理 k 大于数组长度的情况
        int gcd = std::gcd(k, (int)nums.size());
        for (int i = 0; i < gcd; i++)
        {
            int current_index = i;
            int current_num = nums[i];
            do
            {
                int next_index = (current_index + k) % nums.size();
                swap(current_num, nums[next_index]);
                current_index = next_index;
            } while (current_index != i);
        }
    }

private:
    void swap(int &a, int &b)
    {
        if (a == b)
            return;
        a ^= b;
        b ^= a;
        a ^= b;
    }
};