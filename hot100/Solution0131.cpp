#include <vector>
#include <string>
using namespace std;
// 给你一个字符串 s，请你将 s 分割成一些 子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。

// 示例 1：

// 输入：s = "aab"
// 输出：[["a","a","b"],["aa","b"]]
// 示例 2：

// 输入：s = "a"
// 输出：[["a"]]

// 提示：

// 1 <= s.length <= 16
// s 仅由小写英文字母组成
// 方法一：暴力回溯
class Solution
{
public:
    vector<vector<string>> partition(string s)
    {
        vector<vector<string>> result;
        vector<string> path;
        backtrack(s, 0, path, result);
        return result;
    }

private:
    void backtrack(string &s, int index, vector<string> path, vector<vector<string>> &result)
    {
        if (index == s.size())
        {
            if (isPalindrome(path))
                result.push_back(path);
            return;
        }
        for (int i = index; i < s.size(); i++)
        {
            path.push_back(s.substr(index, i - index + 1));
            backtrack(s, i + 1, path, result);
            path.pop_back();
        }
    }
    bool isPalindrome(vector<string> &path)
    {
        for (const string &s : path)
        {
            int left = 0, right = s.size() - 1;
            while (left < right)
            {
                if (s[left] != s[right])
                    return false;
                left++;
                right--;
            }
        }
        return true;
    }
};

// 方法二：回溯+动态规划.
// 当前搜索到字符串的第 i 个字符，且 s[0..i−1] 位置的所有字符已经被分割成若干个回文串
// 遍历j，使得s[i..j] 是一个回文串
// i>j，空字符串：True
// i=j，单字符串：True
// i<j，s[i] = s[j] && [i+1,j-1]是回文。
// 因此，使用cache[i][j]预处理s[i,j]是不是回文。之后回溯的时候就不需要再判断是否是回文了
class Solution2
{
private:
    vector<vector<bool>> cache;

public:
    vector<vector<string>> partition(string s)
    {
        int n = s.size();
        cache.assign(n, vector<bool>(n, true));
        vector<vector<string>> result;
        vector<string> path;
        for (int i = n - 1; i >= 0; i--) // 从字符串末尾开始
            for (int j = i + 1; j < n; j++)
                cache[i][j] = (s[i] == s[j]) && cache[i + 1][j - 1];

        backtrack(s, 0, path, result);
        return result;
    }

private:
    void backtrack(const string &s, int index, vector<string> &path, vector<vector<string>> &result)
    {
        if (index == s.size())
        {
            result.push_back(path);
            return;
        }

        for (int i = index; i < s.size(); i++)
        {
            if (cache[index][i])
            {
                path.push_back(s.substr(index, i - index + 1));
                backtrack(s, i + 1, path, result);
                path.pop_back();
            }
        }
    }
};

// 方法三：回溯+记忆化搜索。
// 即不要预处理生成cache，而是中途生成
class Solution3
{
private:
    vector<vector<int>> cache; // 0表示还未处理，1表示是回文，-1表示不是回文
public:
    vector<vector<string>> partition(string s)
    {
        int n = s.size();
        vector<vector<string>> result;
        vector<string> path;

        backtrack(s, 0, path, result);
        return result;
    }

private:
    void backtrack(const string &s, int index, vector<string> &path, vector<vector<string>> &result)
    {
        if (index == s.size())
        {
            result.push_back(path);
            return;
        }

        for (int i = index; i < s.size(); i++)
        {
            if (isPalindrome(s, index, i))
            {
                path.push_back(s.substr(index, i - index + 1));
                backtrack(s, i + 1, path, result);
                path.pop_back();
            }
        }
    }
    int isPalindrome(const string &s, int left, int right)
    {
        if (cache[left][right])
            return cache[left][right];
        if (left >= right)
        {
            return cache[left][right] = 1;
        }
        return cache[left][right] = (s[left] == s[right]) ? isPalindrome(s, left + 1, right - 1) : -1;
    }
};