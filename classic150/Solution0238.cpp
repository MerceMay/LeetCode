#include <vector>
using namespace std;
// 给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积 。

// 题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。

// 请 不要使用除法，且在 O(n) 时间复杂度内完成此题。
// 进阶：你可以在 O(1) 的额外空间复杂度内完成这个题目吗？（ 出于对空间复杂度分析的目的，输出数组 不被视为 额外空间。）
// 使用前缀积后缀积
class Solution
{
public:
    vector<int> productExceptSelf(vector<int> &nums)
    {
        vector<int> answer(nums.size());
        int leftProduct = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            answer[i] = leftProduct; // 先把左边的乘积存进去
            leftProduct *= nums[i];  // 更新左边的乘积
        }
        int rightProduct = 1;
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            answer[i] *= rightProduct; // 计算后缀积
            rightProduct *= nums[i];   // 更新右边的乘积
        }
        return answer;
    }
};