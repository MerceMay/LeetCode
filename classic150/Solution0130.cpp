#include <vector>
#include <queue>
using namespace std;
// 给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' 组成，捕获 所有 被围绕的区域：

// 连接：一个单元格与水平或垂直方向上相邻的单元格连接。
// 区域：连接所有 'O' 的单元格来形成一个区域。
// 围绕：如果您可以用 'X' 单元格 连接这个区域，并且区域中没有任何单元格位于 board 边缘，则该区域被 'X' 单元格围绕。
// 通过 原地 将输入矩阵中的所有 'O' 替换为 'X' 来 捕获被围绕的区域。你不需要返回任何值。

// 遍历边界上的 'O'，使用dfs遍历与之相连的 'O'，将它们标记为非捕获状态'#'
class Solution
{
public:
    void solve(vector<vector<char>> &board)
    {
        int rows = board.size();
        if (rows == 0)
            return;
        int cols = board[0].size();
        for (int i = 0; i < rows; i++)
        {
            dfs(board, i, 0);
            dfs(board, i, cols - 1);
        }
        for (int j = 0; j < cols; j++)
        {
            dfs(board, 0, j);
            dfs(board, rows - 1, j);
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X'; // 捕获被围绕的区域
                else if (board[i][j] == '#')
                    board[i][j] = 'O'; // 恢复非捕获状态
            }
        }
    }

private:
    void dfs(vector<vector<char>> &board, int i, int j)
    {
        int rows = board.size();
        int cols = board[0].size();
        if (i < 0 || i >= rows || j < 0 || j >= cols || board[i][j] != 'O')
            return;
        board[i][j] = '#';    // 将访问过的陆地标记为非捕获状态
        dfs(board, i + 1, j); // 下
        dfs(board, i - 1, j); // 上
        dfs(board, i, j + 1); // 右
        dfs(board, i, j - 1); // 左
    }
};

class Solution2
{
public:
    void solve(vector<vector<char>> &board)
    {
        int rows = board.size();
        if (rows == 0)
            return;
        int cols = board[0].size();
        queue<pair<int, int>> q;
        for (int i = 0; i < rows; i++)
        {
            if (board[i][0] == 'O')
            {
                q.push({i, 0});
                board[i][0] = '#';
            }
            if (board[i][cols - 1] == 'O')
            {
                q.push({i, cols - 1});
                board[i][cols - 1] = '#';
            }
        }
        for (int j = 0; j < cols; j++)
        {
            if (board[0][j] == 'O')
            {
                q.push({0, j});
                board[0][j] = '#';
            }
            if (board[rows - 1][j] == 'O')
            {
                q.push({rows - 1, j});
                board[rows - 1][j] = '#';
            }
        }
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();
            for (auto [dx, dy] : directions)
            {
                int newX = x + dx;
                int newY = y + dy;
                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && board[newX][newY] == 'O')
                {
                    q.push({newX, newY});
                    board[newX][newY] = '#';
                }
            }
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X'; // 捕获被围绕的区域
                else if (board[i][j] == '#')
                    board[i][j] = 'O'; // 恢复非捕获状态
            }
        }
    }
};