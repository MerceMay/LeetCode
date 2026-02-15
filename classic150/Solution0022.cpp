#include <vector>
#include <string>
#include <array>
#include <memory>
using namespace std;
// 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

// 示例 1：

// 输入：n = 3
// 输出：["((()))","(()())","(())()","()(())","()()()"]
// 示例 2：

// 输入：n = 1
// 输出：["()"]

// 提示：

// 1 <= n <= 8
class Solution
{
public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> result;
        backtrack(result, "", 0, 0, n);
        return result;
    }

private:
    void backtrack(vector<string> &result, string path, int left, int right, int n)
    {
        if (path.size() == n * 2)
        {
            result.push_back(path);
            return;
        }
        if (left < n)
            backtrack(result, path + "(", left + 1, right, n);
        if (right < left)
            backtrack(result, path + ")", left, right + 1, n);
    }
};

class Solution2
{
public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> result;
        recursive(result, "", n);
        return result;
    }

private:
    void recursive(vector<string> result, string path, int n)
    {
        if (path.size() == n * 2)
        {
            if (isValid(path))
                result.push_back(path);
            return;
        }
        recursive(result, path + "(", n);
        recursive(result, path + ")", n);
    }
    bool isValid(string s)
    {
        int balance = 0;
        for (char c : s)
        {
            if (c == '(')
                balance++;
            else
                balance--;
            if (balance < 0)
                return false;
        }
        return balance == 0;
    }
};

class Solution3
{
private:
    array<shared_ptr<vector<string>>, 9> f;

public:
    vector<string> generateParenthesis(int n)
    {
        return *dp(n);
    }

private:
    shared_ptr<vector<string>> dp(int n)
    {
        if (f[n] != nullptr)
            return f[n];
        auto ans = make_shared<vector<string>>();
        if (n == 0)
        {
            ans->push_back("");
        }
        else
        {
            for (int c = 0; c < n; ++c)
            {
                for (auto left : *dp(c))
                {
                    for (auto right : *dp(n - 1 - c))
                    {
                        ans->push_back("(" + left + ")" + right);
                    }
                }
            }
        }
        f[n] = ans;
        return f[n];
    }
};