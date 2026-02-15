#include <vector>
using namespace std;
// 给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。

// 你可以按 任何顺序 返回答案。

// 示例 1：

// 输入：n = 4, k = 2
// 输出：
// [
//   [2,4],
//   [3,4],
//   [2,3],
//   [1,2],
//   [1,3],
//   [1,4],
// ]
// 示例 2：

// 输入：n = 1, k = 1
// 输出：[[1]]

// 提示：

// 1 <= n <= 20
// 1 <= k <= n
class Solution
{
public:
    vector<vector<int>> combine(int n, int k)
    {
        vector<vector<int>> result;
        if (k > n)
            return result;
        vector<int> path;
        backtrack(n, k, 1, path, result);
        return result;
    }

private:
    void backtrack(int n, int k, int index, vector<int> &path, vector<vector<int>> &result)
    {
        if (path.size() == k)
        {
            result.push_back(path);
            return;
        }
        for (int i = index; i <= n; i++)
        {
            path.push_back(i);
            backtrack(n, k, i + 1, path, result);
            path.pop_back();
        }
    }
};

class Solution2
{
private:
    vector<vector<int>> res;
    vector<int> path;

    void dfs(int n, int k, int startIndex)
    {
        if (path.size() + (n - startIndex + 1) < k)
            return;
        if (path.size() == k)
        {
            res.push_back(path);
            return;
        }
        path.push_back(startIndex); // 选择当前位置
        dfs(n, k, startIndex + 1);
        path.pop_back(); // 不选择当前位置
        dfs(n, k, startIndex + 1);
    }

public:
    vector<vector<int>> combine(int n, int k)
    {
        dfs(n, k, 1);
        return res;
    }
};
