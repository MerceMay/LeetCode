#include <string>
#include <vector>
using namespace std;
// 给你一个字符串 s，找到 s 中最长的 回文 子串。
class Solution
{
public:
    // dp[i][j]表示s[i..j]是否是回文串
    string longestPalindrome(string s)
    {
        int n = s.size();
        if (n == 0)
            return "";
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        string result;
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i; j < n; j++)
            {
                if (s[i] == s[j])
                {
                    if (j - i <= 1)
                        dp[i][j] = true;
                    else
                        dp[i][j] = dp[i + 1][j - 1];
                }
                if (dp[i][j] && j - i + 1 > result.size())
                {
                    result = s.substr(i, j - i + 1);
                }
            }
        }
        return result;
    }
};

// 只和左下角有关，直到对角线。因此，直接从对角线和上对角线开始遍历
// 也就是说，我们可以从每一种边界情况开始「扩展」，也可以得出所有的状态对应的答案。
class Solution2
{
public:
    string longestPalindrome(string s)
    {
        int n = s.size();
        if (n == 0)
            return "";
        vector<bool> dp(n, false);
        string result;
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = n - 1; j >= i; j--)
            {
                if (s[i] == s[j])
                {
                    if (j - i <= 1)
                        dp[j] = true;
                    else
                        dp[j] = dp[j - 1];
                }
                else
                {
                    dp[j] = false;
                }
                if (dp[j] && j - i + 1 > result.size())
                {
                    result = s.substr(i, j - i + 1);
                }
            }
        }
        return result;
    }
};

// 中心扩展法
class Solution3
{
public:
    string longestPalindrome(string s)
    {
        int n = s.size();
        if (n == 0)
            return "";
        int start = 0, end = 0;
        for (int i = 0; i < n; i++)
        {
            auto [left1, right1] = expandAroundCenter(s, i, i);     // 奇数长度回文
            auto [left2, right2] = expandAroundCenter(s, i, i + 1); // 偶数长度回文
            if (right1 - left1 > end - start)
            {
                start = left1;
                end = right1;
            }
            if (right2 - left2 > end - start)
            {
                start = left2;
                end = right2;
            }
        }
        return s.substr(start, end - start + 1);
    }

private:
    pair<int, int> expandAroundCenter(const string &s, int left, int right)
    {
        int n = s.size();
        while (left >= 0 && right < n && s[left] == s[right])
        {
            left--;
            right++;
        }
        return {left + 1, right - 1};
    }
};

// 马拉车算法
class Solution4
{
public:
    string longestPalindrome(string s)
    {
        string str = preprocess(s);
        vector<int> p(str.size(), 0); // p[i]表示以i为中心的最长回文半径
        int center = 0, right = 0;
        int start = 0, end = 0; // 记录最长回文子串在原字符串中的起始和结束位置
        for (int i = 0; i < str.size(); i++)
        {
            if (i < right)
            {
                int minLen = min(p[2 * center - i], right - i);
                p[i] = expandAroundCenter(str, i - minLen, i + minLen);
            }
            else
            {
                p[i] = expandAroundCenter(str, i, i);
            }
            if (i + p[i] > right)
            {
                center = i;
                right = i + p[i];
            }
            if (2 * p[i] + 1 > end - start + 1)
            {
                start = i - p[i];
                end = i + p[i];
            }
        }
        string result;
        for (int i = start; i <= end; i++)
        {
            if (str[i] != '#')
                result += str[i];
        }
        return result;
    }

private:
    string preprocess(const string &s)
    {
        string res = "#";
        for (char c : s)
        {
            res += c;
            res += "#";
        }
        return res;
    }

    int expandAroundCenter(const string &s, int left, int right)
    {
        int n = s.size();
        while (left >= 0 && right < n && s[left] == s[right])
        {
            left--;
            right++;
        }
        return (right - left - 2) / 2; // 减去2是因为最后一次扩展失败
    }
};