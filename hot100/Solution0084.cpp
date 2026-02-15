#include <vector>
#include <climits>
#include <stack>
using namespace std;
// 给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

// 求在该柱状图中，能够勾勒出来的矩形的最大面积。

// 示例 1:

// 输入：heights = [2,1,5,6,2,3]
// 输出：10
// 解释：最大的矩形为图中红色区域，面积为 10
// 示例 2：

// 输入： heights = [2,4]
// 输出： 4

// 提示：

// 1 <= heights.length <=105
// 0 <= heights[i] <= 104

// 核心思想：遍历数组中每个元素i
// 第i个元素作为高，保证在[left, right)中，i是最大值，则面积等于(right-left)*heights[i]。注意，right是下一个柱子的开始
// 因此，如果使用单调递增栈，则可以保证对于栈顶元素，其之下一定是left-1，
// 对于right，只要当有一个元素不能入栈，说明他是比他是比栈顶小的，则他是right+1;
class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        int max_area = 0;
        int n = heights.size();
        stack<int> stk;
        heights.push_back(0);                    // 哨兵：迫使栈中所有元素出栈；
        for (int right = 0; right <= n; right++) // 包括哨兵也要进站，迫使其他元素出栈
        {
            while (!stk.empty() && heights[stk.top()] > heights[right])
            {
                int height = heights[stk.top()];
                stk.pop();

                int left = stk.empty() ? -1 : stk.top(); // 这里的left是真实的LEFT-1
                int width = right - left - 1;            // left+1才是真正的LEFT
                max_area = max(max_area, height * width);
            }
            // 直到heights[right]大于heights[stk.top()]，即right的左边界是stk.top()+1
            stk.push(right);
        }
        heights.pop_back(); // 恢复现场
        return max_area;
    }
};