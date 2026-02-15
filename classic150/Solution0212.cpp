#include <vector>
#include <string>
#include <memory>
#include <array>
#include <set>
using namespace std;
// 给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words， 返回所有二维网格上的单词 。

// 单词必须按照字母顺序，通过 相邻的单元格 内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母在一个单词中不允许被重复使用。
class Solution
{
    class TrieNode
    {
    public:
        string word = "";
        array<unique_ptr<TrieNode>, 26> nexts = {};
    };
    unique_ptr<TrieNode> root = make_unique<TrieNode>();

public:
    vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
    {
        vector<string> result;
        int rows = board.size();
        if (rows == 0)
            return vector<string>();
        int cols = board[0].size();

        for (const string &word : words)
            insert(word);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                dfs(board, i, j, root.get(), result);
            }
        }
        return result;
    }

private:
    void dfs(vector<vector<char>> &board, int i, int j, TrieNode *node, vector<string> &result)
    {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size())
            return;
        char ch = board[i][j];
        if (ch == '#')
            return; // 已经访问过

        int index = ch - 'a';
        if (!node->nexts[index])
            return;
        node = node->nexts[index].get();
        if (!node->word.empty())
        {
            result.push_back(node->word);
            node->word.clear(); // 找到了的话，清空，防止重复添加
        }
        board[i][j] = '#'; // 标记为已访问
        dfs(board, i + 1, j, node, result);
        dfs(board, i - 1, j, node, result);
        dfs(board, i, j + 1, node, result);
        dfs(board, i, j - 1, node, result);
        board[i][j] = ch; // 回溯，恢复现场
    }

    void insert(const string &word)
    {
        if (word.empty())
            return;
        TrieNode *node = root.get();
        for (char ch : word)
        {
            int index = ch - 'a';
            if (!node->nexts[index])
                node->nexts[index] = make_unique<TrieNode>();
            node = node->nexts[index].get();
        }
        node->word = word;
    }
};