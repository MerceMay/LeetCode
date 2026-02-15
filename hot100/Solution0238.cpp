#include <iostream>
#include <vector>
using namespace std;
// 给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积 。

// 题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。

// 请 不要使用除法，且在 O(n) 时间复杂度内完成此题。

// 示例 1:

// 输入: nums = [1,2,3,4]
// 输出: [24,12,8,6]
// 示例 2:

// 输入: nums = [-1,1,0,-3,3]
// 输出: [0,0,9,0,0]

// 提示：

// 2 <= nums.length <= 105
// -30 <= nums[i] <= 30
// 输入 保证 数组 answer[i] 在  32 位 整数范围内

// 进阶：你可以在 O(1) 的额外空间复杂度内完成这个题目吗？（ 出于对空间复杂度分析的目的，输出数组 不被视为 额外空间。）
class Solution
{
public:
    vector<int> productExceptSelf(vector<int> &nums)
    {
        // 使用前缀积和后缀积
        // 第一次只算前缀积，第二次算后缀积。因此某一次的answer[i] * left_product * right_product
        // 需要把left_product设计的使得其在乘以answer[i]时还没有乘以nums[i]
        int n = nums.size();
        vector<int> answer(n, 1);
        int left_product = 1;
        for (int i = 0; i < n; i++)
        {
            answer[i] *= left_product;
            left_product *= nums[i];
        }
        int right_product = 1;
        for (int i = n - 1; i >= 0; i--)
        {
            answer[i] *= right_product;
            right_product *= nums[i];
        }
        return answer;
    }
};