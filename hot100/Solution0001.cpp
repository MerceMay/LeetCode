#include <iostream>
#include <vector>
#include <unordered_map>
// 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

// 你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。

// 你可以按任意顺序返回答案。

// 方法一：直接嵌套循环
class Solution
{
public:
    std::vector<int> twoSum(const std::vector<int> &nums, int target)
    {
        std::unordered_map<int, int> num_map; // 存储数字及其对应的索引
        for (int i = 0; i < nums.size(); ++i)
        {
            int complement = target - nums[i]; // 计算补数
            if (num_map.find(complement) != num_map.end())
            {
                return {num_map[complement], i}; // 找到目标值，返回索引
            }
            num_map[nums[i]] = i; // 存储当前数字及其索引
        }
        return {}; // 如果没有找到，返回空数组
    }
};
