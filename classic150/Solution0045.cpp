#include <vector>
using namespace std;
// 给定一个长度为 n 的 0 索引整数数组 nums。初始位置在下标 0。

// 每个元素 nums[i] 表示从索引 i 向后跳转的最大长度。换句话说，如果你在索引 i 处，你可以跳转到任意 (i + j) 处：

// 0 <= j <= nums[i] 且
// i + j < n
// 返回到达 n - 1 的最小跳跃次数。测试用例保证可以到达 n - 1。

// 示例 1:

// 输入: nums = [2,3,1,1,4]
// 输出: 2
// 解释: 跳到最后一个位置的最小跳跃数是 2。
//      从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
// 示例 2:

// 输入: nums = [2,3,0,1,4]
// 输出: 2

// 提示:

// 1 <= nums.length <= 104
// 0 <= nums[i] <= 1000
// 题目保证可以到达 n - 1
class Solution
{
public:
    int jump(vector<int> &nums)
    {
        if (nums.size() == 1)
            return 0;
        int count = 0;
        int i = 0;
        while (i < nums.size())
        {
            int nextPos = 0;
            int maxReach = 0;
            for (int j = 1; j <= nums[i]; j++)
            {
                if (i + j >= nums.size() - 1) // 能直接跳到终点
                    return count + 1;
                if (i + j + nums[i + j] > maxReach)
                {
                    maxReach = i + j + nums[i + j];
                    nextPos = i + j;
                }
            }
            i = nextPos;
            count++;
        }
        return count;
    }
};

// 从结尾开始跳，每次看谁能跳到这里，选下标最小的
class Solution2
{
public:
    int jump(vector<int> &nums)
    {
        int pos = nums.size() - 1;
        int count = 0;
        while (pos > 0)
        {
            for (int i = 0; i < pos; i++)
            {
                if (i + nums[i] >= pos)
                {
                    pos = i;
                    count++;
                }
            }
        }
        return count;
    }
};

class Solution3
{
public:
    int jump(vector<int> &nums)
    {
        int count = 0;
        int end = 0;
        int maxReach = 0; // 在[end,maxReach中试探]，每次end取上一个maxreach的值，当遍历到了end，说明必须跳了
        for (int i = 0; i < nums.size(); i++)
        {
            maxReach = max(maxReach, i + nums[i]);
            if (i == end)
            {
                end = maxReach;
                count++;
            }
        }
        return count;
    }
};