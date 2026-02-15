#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

// 示例 1：

// 输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
// 输出：[[1,6],[8,10],[15,18]]
// 解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
// 示例 2：

// 输入：intervals = [[1,4],[4,5]]
// 输出：[[1,5]]
// 解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。

// 提示：

// 1 <= intervals.length <= 104
// intervals[i].length == 2
// 0 <= starti <= endi <= 104
class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        if (intervals.size() <= 1)
        {
            return intervals;
        }
        // 这道题使用贪心算法，先对每个区间进行排序，再遍历排序后的区间
        sort(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b)
             {
                 return a[0] < b[0]; // 按照区间的起始位置排序
             });
        vector<vector<int>> result;
        vector<int> current_interval = intervals[0]; // 记录当前遍历区间
        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[i][0] <= current_interval[1])
            {
                current_interval[1] = max(current_interval[1], intervals[i][1]);
            }
            else
            {
                result.push_back(current_interval);
                current_interval = intervals[i];
            }
        }
        result.push_back(current_interval);
        return result;
    }
};