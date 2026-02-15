#include <vector>
using namespace std;
// 给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

// 说明：每次只能向下或者向右移动一步。

// 示例 1：

// 输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
// 输出：7
// 解释：因为路径 1→3→1→1→1 的总和最小。
// 示例 2：

// 输入：grid = [[1,2,3],[4,5,6]]
// 输出：12
class Solution
{
public:
    int minPathSum(vector<vector<int>> &grid)
    {
        vector<vector<int>> sum(grid.size(), vector<int>(grid[0].size(), 0));
        for(int i = 0; i < grid.size(); ++i)
        {
            for(int j = 0; j < grid[0].size(); ++j)
            {
                if(i == 0 && j == 0)
                    sum[i][j] = grid[i][j];
                else if(i == 0)
                    sum[i][j] = sum[i][j - 1] + grid[i][j];
                else if(j == 0)
                    sum[i][j] = sum[i - 1][j] + grid[i][j];
                else
                    sum[i][j] = min(sum[i - 1][j], sum[i][j - 1]) + grid[i][j];
            }
        }
        return sum[grid.size() - 1][grid[0].size() - 1];
    }
};