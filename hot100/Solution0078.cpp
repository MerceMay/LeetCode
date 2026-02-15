#include <vector>
using namespace std;
// 给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。

// 解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

// 示例 1：

// 输入：nums = [1,2,3]
// 输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
// 示例 2：

// 输入：nums = [0]
// 输出：[[],[0]]

// 提示：

// 1 <= nums.length <= 10
// -10 <= nums[i] <= 10
// nums 中的所有元素 互不相同
// 方法一：每次遍历nums中一个数，然后添加到result中每个子集的结尾就算作一个新子集
class Solution
{
public:
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> result = {{}};
        for (int num : nums)
        {
            int currentSize = result.size();
            for (int i = 0; i < currentSize; i++)
            {
                vector<int> temp = result[i];
                temp.push_back(num);
                result.push_back(temp);
            }
        }
        return result;
    }

private:
};

// 方法二：使用位运算
class Solution2
{
public:
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> result;
        int n = nums.size();
        for (int mask = 0; mask < (1 << n); mask++)
        {
            vector<int> subset;
            for (int i = 0; i < n; i++) // 遍历每个num
                if (mask & (1 << i))    // 检查 mask 的第 i 位是否为 1。如果为 1，就将 nums 中对应位置的元素 nums[i] 加入到当前子集subset中
                    subset.push_back(nums[i]);
            result.push_back(subset);
        }
        return result;
    }
};

// 方法三：回溯
class Solution3
{
private:
    vector<vector<int>> result;
    vector<int> selectedNums;

public:
    vector<vector<int>> subsets(vector<int> &nums)
    {
        backtrack(nums, 0);
        return result;
    }

private:
    // 每次遍历，[0, start]中的数已经选好，start待选，[start+1,n]不确定
    void backtrack(vector<int> &nums, int start)
    {
        if (start == nums.size()) // 即遍历到完了，直接把已经选中的数放入结果
        {
            result.push_back(selectedNums);
            return;
        }
        selectedNums.push_back(nums[start]); // 选择当前数字
        backtrack(nums, start + 1);
        selectedNums.pop_back(); // 撤销选择，即不选择当前数字
        backtrack(nums, start + 1);
    }
};