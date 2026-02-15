#include <vector>
using namespace std;
// 给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。

// 判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。

// 示例 1：

// 输入：nums = [2,3,1,1,4]
// 输出：true
// 解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。
// 示例 2：

// 输入：nums = [3,2,1,0,4]
// 输出：false
// 解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。

// 提示：

// 1 <= nums.length <= 104
// 0 <= nums[i] <= 105
// 方法一：模拟每次跳跃
class Solution
{
public:
    bool canJump(vector<int> &nums)
    {
        for (int i = 0; i < nums.size();)
        {
            if (i + nums[i] >= nums.size() - 1)
                return true;
            if (nums[i] == 0) // 跳到这里，跳不动了
                return false; 
            int maxReach = 0;
            int nextPos = i;
            for (int j = 1; j <= nums[i]; j++) // 每次尝试在范围内跳跃，看看能跳多远
            {
                if (i + j + nums[i + j] > maxReach)
                {
                    maxReach = i + j + nums[i + j];
                    nextPos = i + j;
                }
            }
            i = nextPos;
        }
        return false;
    }
};

// 方法二：在每次跳跃记录最远可达位置maxReach，然后递增i，只要i没超过maxReach一定是可以到达的
class Solution2
{
public:
    bool canJump(vector<int> &nums)
    {
        int maxReach = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (i > maxReach) // 如果当前下标超过了最远可达位置，说明无法到达
                return false;
            maxReach = max(maxReach, i + nums[i]);
        }
        return true;
    }
};