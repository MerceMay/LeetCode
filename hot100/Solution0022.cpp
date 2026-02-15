#include <vector>
#include <string>
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
// 方法一：回溯
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
    void backtrack(vector<string> &result, string current, int open, int close, int max)
    {
        if (current.length() == max * 2)
        {
            result.push_back(current);
            return;
        }
        if (open < max) // 左括号不足max继续添加
            backtrack(result, current + "(", open + 1, close, max);
        if (close < open) // 右括号不足左括号继续添加
            backtrack(result, current + ")", open, close + 1, max);
    }
};

// 方法二：暴力递归
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
    void recursive(vector<string> &result, string current, int n)
    {
        if (current.length() == n * 2)
        {
            if (isValid(current))
                result.push_back(current);
            return;
        }
        recursive(result, current + "(", n);
        recursive(result, current + ")", n);
    }
};

// 方法三：动态规划
// 所有有效的括号字符串分解成以下结构：
// ( A ) B
// A 和 B 本身都是有效的括号组合。
// A 和 B 的总长度加起来等于 n-1，因为我们已经用了一个 ( 和一个 )
class Solution3
{
private:
    shared_ptr<vector<string>> cache[100] = {nullptr}; // dp[i]存放i对括号的所有有效组合
public:
    vector<string> generateParenthesis(int n)
    {
        return *dp(n); // 返回cache[n]
    }

private:
    shared_ptr<vector<string>> dp(int n)
    {
        if (cache[n] != nullptr) // 如果cache[n]已经计算过，直接返回
            return cache[n];
        if (n == 0) // 对于基准情况n=0，返回一个空字符串
            cache[n] = make_shared<vector<string>>(vector<string>{""});
        else
        {
            auto result = make_shared<vector<string>>();
            for (int i = 0; i < n; i++)
            {
                auto left = dp(i); // A
                auto right = dp(n - 1 - i); // B
                for (const string &l : *left)
                {
                    for (const string &r : *right)
                    {
                        result->push_back("(" + l + ")" + r);
                    }
                }
            }
            cache[n] = result;
        }
        return cache[n];
    }
};