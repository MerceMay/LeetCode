#include <iostream>
#include <vector>
#include <deque>
#include <queue>
using namespace std;
// 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

// 返回 滑动窗口中的最大值 。

// 示例 1：

// 输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
// 输出：[3,3,5,5,6,7]
// 解释：
// 滑动窗口的位置                最大值
// ---------------               -----
// [1  3  -1] -3  5  3  6  7       3
//  1 [3  -1  -3] 5  3  6  7       3
//  1  3 [-1  -3  5] 3  6  7       5
//  1  3  -1 [-3  5  3] 6  7       5
//  1  3  -1  -3 [5  3  6] 7       6
//  1  3  -1  -3  5 [3  6  7]      7
// 示例 2：

// 输入：nums = [1], k = 1
// 输出：[1]

// 提示：

// 1 <= nums.length <= 105
// -104 <= nums[i] <= 104
// 1 <= k <= nums.length
// 方法一：暴力求解
class Solution1
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        vector<int> result;
        for (int left = 0; left < nums.size() - k + 1; left++)
        {
            int maxVal = nums[left];
            for (int i = left; i < left + k; i++)
            {
                maxVal = max(maxVal, nums[i]);
            }
            result.push_back(maxVal);
        }
        return result;
    }
};

// 方法二：单调队列
class Solution2
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        deque<int> q; // 单调队列，队列中存储的是下标，确保队头是最大值。
        vector<int> result;
        for (int i = 0; i < nums.size(); i++) // 遍历每一个元素
        {
            // 处理nums[i]，将队尾所有小于nums[i]元素全部移出，并把nums[i]压入队尾
            while (!q.empty() && nums[q.back()] <= nums[i])
            {
                q.pop_back();
            }
            q.push_back(i);

            // 移出过期元素
            if (!q.empty() && q.front() <= i - k)
            {
                q.pop_front();
            }

            // 记录窗口最大值
            if (i >= k - 1)
            {
                result.push_back(nums[q.front()]);
            }
        }
        return result;
    }
};

// 方法三：优先级队列，大根堆
class Solution3
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        priority_queue<pair<int, int>> pq; // 大根堆，存储元素和下标，把k个元素存入堆中
        for (int i = 0; i < k; i++)
        {
            pq.emplace(nums[i], i);
        }
        vector<int> result = {pq.top().first};
        for (int i = k; i < nums.size(); i++)
        {
            pq.emplace(nums[i], i);
            // 移除过期元素
            while (!pq.empty() && pq.top().second <= i - k)
            {
                pq.pop();
            }
            result.push_back(pq.top().first);
        }
        return result;
    }
};

// 方法四：分块 + 预处理
// 思路：当第i个元素作为框的最左边时，前缀最大值就是prefixMax[i + k -1];
// 第i个元素作为框的最左边时，后缀最大值就是suffixMax[i];
class Solution4
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        vector<int> result;
        vector<int> prefixMax(nums.size()), suffixMax(nums.size());
        for (int i = 0; i < nums.size(); i++)
        {
            if (i % k == 0)
            {
                prefixMax[i] = nums[i];
            }
            else
            {
                prefixMax[i] = max(prefixMax[i - 1], nums[i]);
            }
        }
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            if (i == nums.size() - 1 || (i + 1) % k == 0)
            {
                suffixMax[i] = nums[i];
            }
            else
            {
                suffixMax[i] = max(suffixMax[i + 1], nums[i]);
            }
        }
        for (int i = 0; i <= nums.size() - k; i++)
        {
            result.push_back(max(suffixMax[i], prefixMax[i + k - 1]));
        }
        return result;
    }
};