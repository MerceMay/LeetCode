#include <vector>
using namespace std;
// 给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

// 说明：每次只能向下或者向右移动一步。
class Solution
{
public:
    int minPathSum(vector<vector<int>> &grid)
    {
        vector<vector<int>> sum(grid.size(), vector<int>(grid[0].size(), 0));
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[0].size(); ++j)
            {
                if (i == 0 && j == 0)
                    sum[i][j] = grid[i][j];
                else if (i == 0)
                    sum[i][j] = sum[i][j - 1] + grid[i][j];
                else if (j == 0)
                    sum[i][j] = sum[i - 1][j] + grid[i][j];
                else
                    sum[i][j] = min(sum[i - 1][j], sum[i][j - 1]) + grid[i][j];
            }
        }
        return sum[grid.size() - 1][grid[0].size() - 1];
    }
};

// 只和上和左有关，可以用一维数组滚动数组优化
class Solution2
{
public:
    int minPathSum(vector<vector<int>> &grid)
    {
        vector<int> sum(grid[0].size(), 0);
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[0].size(); ++j)
            {
                if (i == 0 && j == 0)
                    sum[j] = grid[i][j];
                else if (i == 0)
                    sum[j] = sum[j - 1] + grid[i][j];
                else if (j == 0)
                    sum[j] = sum[j] + grid[i][j];
                else
                    sum[j] = min(sum[j - 1], sum[j]) + grid[i][j];
            }
        }
        return sum[grid[0].size() - 1];
    }
};