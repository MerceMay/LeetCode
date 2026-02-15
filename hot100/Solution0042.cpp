#include <iostream>
#include <vector>
#include <stack>
using namespace std;
// 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

// 示例 1：

// 输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
// 输出：6
// 解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。
// 示例 2：

// 输入：height = [4,2,0,3,2,5]
// 输出：9

// 提示：

// n == height.length
// 1 <= n <= 2 * 104
// 0 <= height[i] <= 105

// 方法一：双指针
class Solution1
{
public:
    int trap(vector<int> &height)
    {
        // 重点在于理解短板效应
        // 双指针，当左指针矮于右指针的时候，说明这个下标可以接雨水。但是能接多少水还是得看左侧最高值，因此，left_max记录左侧最高值
        // 当右指针矮于左指针的时候，说明这个下标可以接雨水，因此，right_max记录右侧最高值
        int left = 0;
        int right = height.size() - 1;
        int left_max = 0, right_max = 0;
        int water = 0;
        while (left < right)
        {
            if (height[left] < height[right])
            {
                left_max = max(left_max, height[left]); // 更新左侧最高，如果当前是最高，下面的water就是+=0
                water += left_max - height[left];
                left++;
            }
            else
            {
                right_max = max(right_max, height[right]);
                water += right_max - height[right];
                right--;
            }
        }
        return water;
    }
};

// 方法二：动态规划
// 动态规划的本质是：最优子结构和无后效性。
// 最优子结构：一个问题的最优解可以由其子问题的最优解来构造。例如，要找到组成 aim 的最少硬币数，我们只需要知道组成 aim - arr[i] 的最少硬币数。
// 无后效性：一旦某个子问题被求解，它的结果就被存储下来。在求解后续问题时，我们只需要依赖这个结果，而不用关心它最初是如何被计算出来的。
class Solution2
{
public:
    // 接雨水问题也满足这两个条件，所以可以用动态规划来解。

    // 最优子结构：每个位置能接多少水，取决于它左边最高的墙和右边最高的墙。我们可以把“左边最高的墙”和“右边最高的墙”看作是子问题，它们的解可以帮助我们解决整个问题。

    // 无后效性：一旦我们计算出 left_max[i]（左边最高的墙），这个值就是确定的，在计算后续的 left_max 时，我们不需要再重新回到 0 去遍历。

    // 双指针和动态规划的时间复杂度为都是O(N)，但是动态规划的空间复杂度是O(N)，双指针的空间复杂度是O(1)，因此，可以把双指针看作是动态规划的降维
    int trap(vector<int> &height)
    {
        int n = height.size();
        if (n == 0)
            return 0;
        vector<int> left_max(n), right_max(n);
        for (int i = 0; i < n; ++i)
        {
            left_max[i] = (i == 0) ? height[i] : max(left_max[i - 1], height[i]);
        }
        for (int i = n - 1; i >= 0; --i)
        {
            right_max[i] = (i == n - 1) ? height[i] : max(right_max[i + 1], height[i]);
        }
        int water = 0;
        for (int i = 0; i < n; ++i)
        {
            water += min(left_max[i], right_max[i]) - height[i];
        }
        return water;
    }
};

// 方法三：单调栈
// 想象现在从左往右建墙，栈中存放的是一个单调递减的槽，水可以从左往右流
// 突然，出现了一个比栈顶还高的墙，这时就形成了一个小水槽，于是就可以计算这个小水槽的容量了（弹出栈顶，直到无法弹出）
// 并且容量计算是分层的，例如：
// [4, 0, 2, 3]
// 下标1第一次计算的容量是 [min(4, 2) - 0 = 2]*(2-0-1)，但实际上，下标一的水量包括在下一次的计算中。因此说计算是分层的
// 其下一次计算是在3
class Solution3
{
public:
    int trap(vector<int> &height)
    {
        int water = 0;
        stack<int> stack;
        for (int i = 0; i < height.size(); ++i)
        {
            while (!stack.empty() && height[i] > height[stack.top()])
            {
                int top = stack.top();
                stack.pop();
                if (stack.empty())
                    break;
                int distance = i - stack.top() - 1;
                int bounded_height = min(height[i], height[stack.top()]) - height[top];
                water += distance * bounded_height;
            }
            stack.push(i);
        }
        return water;
    }
};