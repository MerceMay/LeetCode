#include <vector>
#include <queue>
using namespace std;
// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

// 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

// 此外，你可以假设该网格的四条边均被水包围。

// 示例 1：

// 输入：grid = [
//   ["1","1","1","1","0"],
//   ["1","1","0","1","0"],
//   ["1","1","0","0","0"],
//   ["0","0","0","0","0"]
// ]
// 输出：1
// 示例 2：

// 输入：grid = [
//   ["1","1","0","0","0"],
//   ["1","1","0","0","0"],
//   ["0","0","1","0","0"],
//   ["0","0","0","1","1"]
// ]
// 输出：3

// 提示：

// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 300
// grid[i][j] 的值为 '0' 或 '1'
// 方法一：深度优先搜索
class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        int row_length = grid.size();
        if (!row_length)
            return 0;
        int col_length = grid[0].size();
        int count = 0;
        for (int i = 0; i < row_length; i++)
        {
            for (int j = 0; j < col_length; j++)
            {
                if (grid[i][j] == '1')
                {
                    count++;
                    dfs(grid, i, j, row_length, col_length);
                }
            }
        }
        return count;
    }

private:
    void dfs(vector<vector<char>> &grid, int i, int j, int row_length, int col_length)
    {
        if (i < 0 || i >= row_length || j < 0 || j >= col_length || grid[i][j] == '0')
            return;
        grid[i][j] = '0';
        dfs(grid, i + 1, j, row_length, col_length);
        dfs(grid, i - 1, j, row_length, col_length);
        dfs(grid, i, j + 1, row_length, col_length);
        dfs(grid, i, j - 1, row_length, col_length);
    }
};

// 方法二：广度优先搜索
class Solution2
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        int row_length = grid.size();
        if (!row_length)
            return 0;
        int col_length = grid[0].size();
        int count = 0;
        for (int i = 0; i < row_length; i++)
        {
            for (int j = 0; j < col_length; j++)
            {
                if (grid[i][j] == '1')
                {
                    count++;
                    bfs(grid, i, j, row_length, col_length);
                }
            }
        }
        return count;
    }

private:
    void bfs(vector<vector<char>> &grid, int i, int j, int row_length, int col_length)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        grid[i][j] = '0';
        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();
            if (x + 1 < row_length && grid[x + 1][y] == '1')
            {
                q.push({x + 1, y});
                grid[x + 1][y] = '0';
            }
            if (x - 1 >= 0 && grid[x - 1][y] == '1')
            {
                q.push({x - 1, y});
                grid[x - 1][y] = '0';
            }
            if (y + 1 < col_length && grid[x][y + 1] == '1')
            {
                q.push({x, y + 1});
                grid[x][y + 1] = '0';
            }
            if (y - 1 >= 0 && grid[x][y - 1] == '1')
            {
                q.push({x, y - 1});
                grid[x][y - 1] = '0';
            }
        }
    }
};

// 方法三：并查集
class Solution3
{
private:
    class UnionFind
    {
    private:
        vector<int> parent; // 并查集下标为 (i * col_length + j)
        vector<int> rank;   // rank表示以[i, j]为父节点的树的高度
        int count;          // 岛的数量

    public:
        UnionFind(vector<vector<char>> &grid)
        {
            int row_length = grid.size();
            if (!row_length)
                return;
            int col_length = grid[0].size();
            parent.resize(row_length * col_length);
            rank.resize(row_length * col_length, 0);
            count = 0;
            for (int i = 0; i < row_length; i++)
            {
                for (int j = 0; j < col_length; j++)
                {
                    if (grid[i][j] == '1') // 如果这个是陆地，初始化时都视为一个岛，并且其父亲指向自己
                    {
                        parent[i * col_length + j] = i * col_length + j;
                        count++;
                    }
                    else // 如果这个是水，初始化时视为一个岛的父亲指向-1
                    {
                        parent[i * col_length + j] = -1;
                    }
                }
            }
        }
        // 找到根节点
        int find(int x)
        {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        }
        // 合并两个树
        void Union(int x, int y)
        {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY) // 如果两个数不在一起
            {
                if (rank[rootX] > rank[rootY]) // 找到更高的树，把矮的树挂到高的树上
                {
                    parent[rootY] = rootX; 
                }
                else if (rank[rootX] < rank[rootY])
                {
                    parent[rootX] = rootY;
                }
                else // 一样高，随便挂，并增加树的高度
                {
                    parent[rootY] = rootX;
                    rank[rootX]++;
                }
                count--; // 合并后，岛的数量减一
            }
        }
        int getCount()
        {
            return count;
        }
    };

public:
    int numIslands(vector<vector<char>> &grid)
    {
        int row_length = grid.size();
        if (!row_length)
            return 0;
        int col_length = grid[0].size();
        UnionFind uf(grid);
        for (int i = 0; i < row_length; i++)
        {
            for (int j = 0; j < col_length; j++)
            {
                if (grid[i][j] == '1')
                {
                    grid[i][j] = '0';
                    if (i + 1 < row_length && grid[i + 1][j] == '1')
                        uf.Union(i * col_length + j, (i + 1) * col_length + j);
                    if (j + 1 < col_length && grid[i][j + 1] == '1')
                        uf.Union(i * col_length + j, i * col_length + (j + 1));
                    if (i - 1 >= 0 && grid[i - 1][j] == '1')
                        uf.Union(i * col_length + j, (i - 1) * col_length + j);
                    if (j - 1 >= 0 && grid[i][j - 1] == '1')
                        uf.Union(i * col_length + j, i * col_length + (j - 1));
                }
            }
        }
        return uf.getCount();
    }
};