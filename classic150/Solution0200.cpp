#include <vector>
using namespace std;
// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

// 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

// 此外，你可以假设该网格的四条边均被水包围。
class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        int rows = grid.size();
        if (rows == 0)
            return 0;
        int cols = grid[0].size();
        int count = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] == '1')
                {
                    count++;
                    dfs(grid, i, j);
                }
            }
        }
        return count;
    }

private:
    void dfs(vector<vector<char>> &grid, int i, int j)
    {
        int rows = grid.size();
        int cols = grid[0].size();
        if (i < 0 || i >= rows || j < 0 || j >= cols || grid[i][j] == '0')
            return;
        grid[i][j] = '0';    // 将访问过的陆地标记为水，避免重复访问
        dfs(grid, i + 1, j); // 下
        dfs(grid, i - 1, j); // 上
        dfs(grid, i, j + 1); // 右
        dfs(grid, i, j - 1); // 左
    }
};

class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        int rows = grid.size();
        if (rows == 0)
            return 0;
        int cols = grid[0].size();
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int count = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] == '1')
                {
                    count++;
                    grid[i][j] = '0';
                    vector<pair<int, int>> queue = {{i, j}};
                    while (!queue.empty())
                    {
                        auto [x, y] = queue.back();
                        queue.pop_back();
                        for (auto [dx, dy] : directions)
                        {
                            int newX = x + dx;
                            int newY = y + dy;
                            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && grid[newX][newY] == '1')
                            {
                                grid[newX][newY] = '0';
                                queue.push_back({newX, newY});
                            }
                        }
                    }
                }
            }
        }
        return count;
    }
};

class Solution
{
private:
    class UnionFind
    {
    private:
        vector<int> parent;
        vector<int> rank;
        int count;

    public:
        UnionFind(vector<vector<char>> &grid)
        {
            int rows = grid.size();
            int cols = grid[0].size();
            parent.resize(rows * cols);
            rank.resize(rows * cols, 0);
            count = 0;
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (grid[i][j] == '1')
                    {
                        int id = i * cols + j;
                        parent[id] = id;
                        count++;
                    }
                }
            }
        }

        void unionSets(int x, int y)
        {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY)
            {
                if (rank[rootX] > rank[rootY])
                {
                    parent[rootY] = rootX;
                }
                else if (rank[rootX] < rank[rootY])
                {
                    parent[rootX] = rootY;
                }
                else
                {
                    parent[rootY] = rootX;
                    rank[rootX]++;
                }
                count--;
            }
        }
        int getCount() const
        {
            return count;
        }

    private:
        int find(int x)
        {
            if (parent[x] != x)
            {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
    };

public:
    int numIslands(vector<vector<char>> &grid)
    {
        int rows = grid.size();
        if (rows == 0)
            return 0;
        int cols = grid[0].size();
        UnionFind uf(grid);
        vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] == '1')
                {
                    grid[i][j] = '0'; // 标记为已访问
                    for (auto [dx, dy] : directions)
                    {
                        int newX = i + dx;
                        int newY = j + dy;
                        if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && grid[newX][newY] == '1')
                        {
                            uf.unionSets(i * cols + j, newX * cols + newY);
                        }
                    }
                }
            }
        }
        return uf.getCount();
    }
};