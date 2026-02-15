#include <vector>
#include <deque>
using namespace std;
// 在给定的 m x n 网格 grid 中，每个单元格可以有以下三个值之一：

// 值 0 代表空单元格；
// 值 1 代表新鲜橘子；
// 值 2 代表腐烂的橘子。
// 每分钟，腐烂的橘子 周围 4 个方向上相邻 的新鲜橘子都会腐烂。

// 返回 直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1 。

// 示例 1：

// 输入：grid = [[2,1,1],[1,1,0],[0,1,1]]
// 输出：4
// 示例 2：

// 输入：grid = [[2,1,1],[0,1,1],[1,0,1]]
// 输出：-1
// 解释：左下角的橘子（第 2 行， 第 0 列）永远不会腐烂，因为腐烂只会发生在 4 个方向上。
// 示例 3：

// 输入：grid = [[0,2]]
// 输出：0
// 解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0 。

// 提示：

// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 10
// grid[i][j] 仅为 0、1 或 2
// 方法一： 广度优先搜索
class Solution
{
public:
    int orangesRotting(vector<vector<int>> &grid)
    {
        int row = grid.size();
        int col = grid[0].size();

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        int minutes = 0;
        int fresh_count = 0;
        deque<pair<int, int>> queue;

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (grid[i][j] == 2)
                {
                    queue.push_back({i, j});
                }
                else if (grid[i][j] == 1)
                {
                    fresh_count++;
                }
            }
        }
        while (fresh_count > 0 && !queue.empty())
        {
            int size = queue.size();
            for (int i = 0; i < size; i++)
            {
                auto [x, y] = queue.front();
                queue.pop_front();
                for (int j = 0; j < 4; j++)
                {
                    int nx = x + dx[j];
                    int ny = y + dy[j];
                    if (nx >= 0 && nx < row && ny >= 0 && ny < col && grid[nx][ny] == 1)
                    {
                        grid[nx][ny] = 2;
                        fresh_count--;
                        queue.push_back({nx, ny});
                    }
                }
            }
            minutes++;
        }
        return fresh_count == 0 ? minutes : -1;
    }
};