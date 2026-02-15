#include <vector>
#include <string>
using namespace std;
// 给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

// 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
class Solution
{
public:
    bool exist(vector<vector<char>> &board, string word)
    {
        int row = board.size();
        if (row == 0)
            return false;
        int col = board[0].size();

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (dfs(board, i, j, word, 0))
                    return true;
            }
        }
        return false;
    }

private:
    bool dfs(vector<vector<char>> &board, int row, int col, string word, int index)
    {
        if (index == word.size())
            return true;
        if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() || board[row][col] != word[index])
            return false;

        char temp = board[row][col];
        board[row][col] = '#';
        bool found = dfs(board, row + 1, col, word, index + 1) ||
                     dfs(board, row - 1, col, word, index + 1) ||
                     dfs(board, row, col + 1, word, index + 1) ||
                     dfs(board, row, col - 1, word, index + 1);
        board[row][col] = temp;
        return found;
    }
};