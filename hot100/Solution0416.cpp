#include <vector>
using namespace std;
// 给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

// 示例 1：

// 输入：nums = [1,5,11,5]
// 输出：true
// 解释：数组可以分割成 [1, 5, 5] 和 [11] 。
// 示例 2：

// 输入：nums = [1,2,3,5]
// 输出：false
// 解释：数组不能分割成两个元素和相等的子集。

// 动态规划：使用左手坐标系，即i为y轴朝下，j为x轴朝右
// dp[i][j]表示在[0,i]之间存在子集等于j。因此dp[n-1][target]
class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        if (nums.size() < 2)
            return false;
        int sum = 0, maxNum = 0;
        for (int num : nums)
        {
            sum += num;
            maxNum = max(maxNum, num);
        }
        if (sum % 2 != 0 || maxNum > sum / 2)
            return false;
        int target = sum / 2;
        vector<vector<bool>> dp(nums.size(), vector<bool>(target + 1, false));
        for (int i = 0; i < nums.size(); ++i)
            dp[i][0] = true;
        for (int i = 0; i < nums.size(); ++i)
        {
            for (int j = 1; j <= target; ++j)
            {
                if (j >= nums[i]) // 如果剩余值大于等于当前数，则可以选择当前数也可以不选择
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i]];
                else // 剩余值小于当前数，则只能不选择当前数
                    dp[i][j] = dp[i - 1][j];
            }
        }
        return dp[nums.size() - 1][target];
    }
};

// 注意：(i,j)的位置和上和左上有关，因此，没必要使用i来记录，对i降维即可，即使用替换来更新上一行的状态
// 但是，在新一轮遍历的时候，需要从右往左遍历，这样就不会覆盖到上一轮的数据
class Solution2
{
public:
    bool canPartition(vector<int> &nums)
    {
        if (nums.size() < 2)
            return false;
        int sum = 0, maxNum = 0;
        for (int num : nums)
        {
            sum += num;
            maxNum = max(maxNum, num);
        }
        if (sum % 2 != 0 || maxNum > sum / 2)
            return false;
        int target = sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (int num : nums)
        {
            for (int j = target; j >= num; --j)
            {
                dp[j] = dp[j] || dp[j - num];
            }
        }
        return dp[target];
    }
};