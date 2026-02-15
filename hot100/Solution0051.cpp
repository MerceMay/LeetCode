#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
using namespace std;
// 按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。

// n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。

// 给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。

// 每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

// 示例 1：

// 输入：n = 4
// 输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
// 解释：如上图所示，4 皇后问题存在两个不同的解法。
// 示例 2：

// 输入：n = 1
// 输出：[["Q"]]
// 方法一：带剪枝的暴力回溯
class Solution1
{
public:
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> result;
        vector<string> path(n, string(n, '.'));
        backtrack(path, 0, n, result);
        return result;
    }

private:
    void backtrack(vector<string> &path, int row, int n, vector<vector<string>> &result)
    {
        if (row == n)
        {
            result.push_back(path);
            return;
        }
        for (int col = 0; col < n; col++)
        {
            if (isValid(path, row, col, n))
            {
                path[row][col] = 'Q';
                backtrack(path, row + 1, n, result);
                path[row][col] = '.'; // 撤销选择
            }
        }
    }
    bool isValid(vector<string> &path, int row, int col, int n)
    {
        // 检查列
        for (int i = 0; i < row; i++)
            if (path[i][col] == 'Q')
                return false;
        // 检查左上角
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
            if (path[i][j] == 'Q')
                return false;
        // 检查右上角
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
            if (path[i][j] == 'Q')
                return false;
        return true;
    }
};

// 方法二：使用哈希来优化isValid的逻辑
class Solution2
{
private:
    unordered_set<int> cols;
    unordered_set<int> diag1;
    unordered_set<int> diag2;
public:
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> result;
        vector<string> path(n, string(n, '.'));
        backtrack(path, 0, n, result);
        return result;
    }

private:
    void backtrack(vector<string> &path, int row, int n, vector<vector<string>> &result)
    {
        if (row == n)
        {
            result.push_back(path);
            return;
        }
        for (int col = 0; col < n; col++)
        {
            if (isValid(row, col))
            {
                path[row][col] = 'Q';
                cols.insert(col);
                diag1.insert(row - col);
                diag2.insert(row + col);
                backtrack(path, row + 1, n, result);
                path[row][col] = '.';
                cols.erase(col);
                diag1.erase(row - col);
                diag2.erase(row + col);
            }
        }
    }
    bool isValid(int row, int col)
    {
        return cols.find(col) == cols.end() &&
               diag1.find(row - col) == diag1.end() &&
               diag2.find(row + col) == diag2.end();
    }
};

// 也可以使用位运算表示是否可以占位，但是时间复杂度没什么本质区别，空间复杂度为O(1)