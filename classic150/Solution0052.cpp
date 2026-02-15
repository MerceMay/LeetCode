#include <unordered_set>
#include <vector>
using namespace std;
// n 皇后问题 研究的是如何将 n 个皇后放置在 n × n 的棋盘上，并且使皇后彼此之间不能相互攻击。

// 给你一个整数 n ，返回 n 皇后问题 不同的解决方案的数量。

// 示例 1：

// 输入：n = 4
// 输出：2
// 解释：如上图所示，4 皇后问题存在两个不同的解法。
// 示例 2：

// 输入：n = 1
// 输出：1

// 提示：

// 1 <= n <= 9
class Solution
{
private:
    unordered_set<int> cols;
    unordered_set<int> diag1;
    unordered_set<int> diag2;

public:
    int totalNQueens(int n)
    {
        int count = 0;
        backtrack(0, n, count);
        return count;
    }

private:
    void backtrack(int row, int n, int &count)
    {
        if (row == n)
        {
            count++;
            return;
        }
        for (int col = 0; col < n; col++)
        {
            if (isValid(row, col))
            {
                cols.insert(col);
                diag1.insert(row - col);
                diag2.insert(row + col);
                backtrack(row + 1, n, count);
                cols.erase(col);
                diag1.erase(row - col);
                diag2.erase(row + col);
            }
        }
    }
    bool isValid(int row, int col)
    {
        return !cols.count(col) && !diag1.count(row - col) && !diag2.count(row + col);
    }
};

class Solution2
{
public:
    int totalNQueens(int n)
    {
        vector<bool> cols(n, false);
        vector<bool> diag1(2 * n - 1, false);
        vector<bool> diag2(2 * n - 1, false);
        int count = 0;
        backtrack(0, n, count, cols, diag1, diag2);
        return count;
    }

private:
    void backtrack(int row, int n, int &count, vector<bool> &cols, vector<bool> &diag1, vector<bool> &diag2)
    {
        if (row == n)
        {
            count++;
            return;
        }
        for (int col = 0; col < n; col++)
        {
            if (!cols[col] && !diag1[row - col + n - 1] && !diag2[row + col])
            {
                cols[col] = true;
                diag1[row - col + n - 1] = true;
                diag2[row + col] = true;
                backtrack(row + 1, n, count, cols, diag1, diag2);
                cols[col] = false;
                diag1[row - col + n - 1] = false;
                diag2[row + col] = false;
            }
        }
    }
};