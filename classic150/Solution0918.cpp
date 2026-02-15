#include <vector>
#include <deque>
using namespace std;
// 给定一个长度为 n 的环形整数数组 nums ，返回 nums 的非空 子数组 的最大可能和 。

// 环形数组 意味着数组的末端将会与开头相连呈环状。形式上， nums[i] 的下一个元素是 nums[(i + 1) % n] ， nums[i] 的前一个元素是 nums[(i - 1 + n) % n] 。

// 子数组 最多只能包含固定缓冲区 nums 中的每个元素一次。形式上，对于子数组 nums[i], nums[i + 1], ..., nums[j] ，不存在 i <= k1, k2 <= j 其中 k1 % n == k2 % n 。

// 提示：

// n == nums.length
// 1 <= n <= 3 * 104
// -3 * 104 <= nums[i] <= 3 * 104​​​​​​​
class Solution
{
private:
    struct Info
    {
        int leftMaxSum;
        int leftMinSum;
        int rightMaxSum;
        int rightMinSum;
        int subMaxSum;
        int subMinSum;
        int intervalSum;
    };

public:
    int maxSubarraySumCircular(vector<int> &nums)
    {
        Info info = Conquer(nums, 0, nums.size() - 1);
        if (info.intervalSum == info.subMinSum) // 说明所有数都是负数
            return info.subMaxSum;
        int result = max(info.subMaxSum, info.intervalSum - info.subMinSum);
        return result;
    }

private:
    Info Conquer(vector<int> &nums, int left, int right)
    {
        if (left == right)
        {
            return {nums[left], nums[left], nums[left], nums[left], nums[left], nums[left], nums[left]};
        }
        int mid = left + (right - left) / 2;
        Info leftInfo = Conquer(nums, left, mid);
        Info rightInfo = Conquer(nums, mid + 1, right);

        return pushUp(leftInfo, rightInfo);
    }
    Info pushUp(Info &leftInfo, Info &rightInfo)
    {
        Info info;
        info.leftMaxSum = max(leftInfo.leftMaxSum, leftInfo.intervalSum + rightInfo.leftMaxSum);
        info.leftMinSum = min(leftInfo.leftMinSum, leftInfo.intervalSum + rightInfo.leftMinSum);
        info.rightMaxSum = max(rightInfo.rightMaxSum, rightInfo.intervalSum + leftInfo.rightMaxSum);
        info.rightMinSum = min(rightInfo.rightMinSum, rightInfo.intervalSum + leftInfo.rightMinSum);
        info.subMaxSum = max(max(leftInfo.subMaxSum, rightInfo.subMaxSum), leftInfo.rightMaxSum + rightInfo.leftMaxSum);
        info.subMinSum = min(min(leftInfo.subMinSum, rightInfo.subMinSum), leftInfo.rightMinSum + rightInfo.leftMinSum);
        info.intervalSum = leftInfo.intervalSum + rightInfo.intervalSum;
        return info;
    }
};

// 首先计算中间的最大子数组和：
// 使用pre表示以i结尾的最大子数组和，res表示全局最大子数组和
// 然后计算两头的：
// 从右到左计算[j, n-1] 以及[0, i]的和
// 因此第二次遍历负责算[j, n-1]，第一次遍历负责算[0, i]及pre
class Solution2
{
public:
    int maxSubarraySumCircular(vector<int> &nums)
    {
        int n = nums.size();
        int result = nums[0];
        int pre = nums[0];
        int leftSum = nums[0];
        vector<int> leftMax(n);
        leftMax[0] = nums[0];
        for (int i = 1; i < n; i++)
        {
            pre = max(pre + nums[i], nums[i]); // 如果变小了，就重置
            result = max(result, pre);
            leftSum += nums[i];
            leftMax[i] = max(leftMax[i - 1], leftSum);
        }

        int rightSum = 0;
        for (int i = n - 1; i > 0; i--) // 不能重复，因此不能取到0
        {
            rightSum += nums[i];
            result = max(result, rightSum + leftMax[i - 1]);
        }
        return result;
    }
};

class Solution3
{
public:
    int maxSubarraySumCircular(vector<int> &nums)
    {
        int n = nums.size();
        int preMax = nums[0], preMin = nums[0];
        int maxSum = nums[0], minSum = nums[0];
        int total = nums[0];
        for (int i = 1; i < n; i++)
        {
            preMax = max(preMax + nums[i], nums[i]);
            maxSum = max(maxSum, preMax);
            preMin = min(preMin + nums[i], nums[i]);
            minSum = min(minSum, preMin);
            total += nums[i];
        }
        return maxSum > 0 ? max(maxSum, total - minSum) : maxSum;
    }
};

// 双倍数组
class Solution3
{
public:
    int maxSubarraySumCircular(vector<int> &nums)
    {
        int n = nums.size();
        // 单调递增队列，存放着递增的前缀和
        deque<pair<int, int>> dq; // <index, preSum> pair 的第一个元素是索引，第二个是前缀和。
        int preSum = 0, result = nums[0]; // preSum 记录当前的前缀和。
        dq.push_back({0, preSum});
        for (int i = 0; i < 2 * n; i++)
        {
            while (!dq.empty() && i - dq.front().first > n) // 保证子数组长度不超过n
                dq.pop_front();
            preSum += nums[i % n];
            // preSum 是从 nums[0] 到 nums[i % n] 的总和，dq.front().second 则是窗口中最靠左的、前缀和最小的值。两者的差就是以 i 结尾的、且长度不超过 n 的最大子数组和
            result = max(result, preSum - dq.front().second); // 计算以i结尾的最大子数组和
            while (!dq.empty() && dq.back().second >= preSum) // 如果当前的前缀和 preSum 小于或等于队列末尾的前缀和，那么队列末尾的元素就没有存在的价值了。
                dq.pop_back();
            dq.push_back({i + 1, preSum});
        }
        return result;
    }
};