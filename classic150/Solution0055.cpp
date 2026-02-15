#include <vector>
using namespace std;
// 给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。

// 判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。
// 记录最远距离，然后遍历每个阶梯，如果遍历到一个阶梯比最远距离都长，说明不能到达该阶梯，直接返回 false
class Solution
{
public:
    bool canJump(vector<int> &nums)
    {
        int maxReach = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (i > maxReach)
                return false;
            maxReach = max(maxReach, i + nums[i]);
        }
        return true;
    }
};