#include <vector>
#include <stack>
using namespace std;
// 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
class Solution
{
public:
    // 单调下降栈：遇见一个更高的墙就可以装水
    int trap(vector<int> &height)
    {
        int water = 0;
        stack<int> stack;
        for (int i = 0; i < height.size(); i++)
        {
            while (!stack.empty() && height[i] > height[stack.top()])
            {
                int lowindex = stack.top();
                stack.pop();
                if (stack.empty()) // 说明当前栈中都是递增的，无法储存水
                    break;
                int w = i - stack.top() - 1;
                int h = min(height[i], height[stack.top()]) - height[lowindex];
                water += w * h;
            }
            stack.push(i);
        }
        return water;
    }
};

// 记录第i个位置的左侧最高墙和右侧最高墙
class Solution
{
public:
    int trap(vector<int> &height)
    {
        int n = height.size();
        if (!n)
            return n;
        vector<int> left_height(n), right_height(n);
        for (int i = 0; i < n; i++)
            left_height[i] = (i == 0) ? height[i] : max(left_height[i - 1], height[i]);
        for (int i = n - 1; i >= 0; i--)
            right_height[i] = (i == n - 1) ? height[i] : max(right_height[i + 1], height[i]);
        int water = 0;
        for (int i = 0; i < n; i++)
            water += min(left_height[i], right_height[i]) - height[i];
        return water;
    }
};

// 双指针：
class Solution
{
public:
    int trap(vector<int> &height)
    {
        int left = 0, right = height.size() - 1;
        int left_max = 0, right_max = 0;
        int water = 0;
        while (left < right)
        {
            if (height[left] < height[right])
            {
                left_max = max(left_max, height[left]);
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