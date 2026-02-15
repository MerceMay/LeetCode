#include <vector>
using namespace std;
// 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

// 示例 1：

// 输入：nums = [1,2,3]
// 输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
// 示例 2：

// 输入：nums = [0,1]
// 输出：[[0,1],[1,0]]
// 示例 3：

// 输入：nums = [1]
// 输出：[[1]]

// 提示：

// 1 <= nums.length <= 6
// -10 <= nums[i] <= 10
// nums 中的所有整数 互不相同
class Solution
{
public:
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> result;
        backtrack(nums, 0, result);
        return result;
    }

private:
    void backtrack(vector<int> &nums, int start, vector<vector<int>> &result)
    {
        if (start == nums.size()) // 只剩下一个数字
        {
            result.push_back(nums);
            return;
        }
        for (int i = start; i < nums.size(); ++i)
        {
            swap(nums[start], nums[i]); // 交换
            backtrack(nums, start + 1, result);
            swap(nums[start], nums[i]); // 还原
        }
    }
};

// 套路：
// void backtracking(参数) {
//     if (终止条件) {
//         存放结果;
//         return;
//     }
//     for (选择 : 本层集合中的元素) {
//         处理节点;
//         backtracking(路径, 选择列表); // 递归
//         撤销处理; // 回溯
//     }
// }