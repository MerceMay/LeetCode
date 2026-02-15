#include <string>
#include <vector>
using namespace std;
// 给你一个字符串 s，找到 s 中最长的 回文 子串。

// 示例 1：

// 输入：s = "babad"
// 输出："bab"
// 解释："aba" 同样是符合题意的答案。
// 示例 2：

// 输入：s = "cbbd"
// 输出："bb"
// 方法一：动态规划，dp[i][j]表示s[i..j]是否为回文串
class Solution
{
public:
    string longestPalindrome(string s)
    {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        string result;
        for (int i = s.size() - 1; i >= 0; --i)
        {
            for (int j = i; j < s.size(); ++j)
            {
                if (s[i] == s[j])
                {
                    if (j - i < 3) // 如果长度为 1 或 2，就是回文
                        dp[i][j] = true;
                    else // 如果长度从3开始了，那么需要其内部也是回文
                        dp[i][j] = dp[i + 1][j - 1];
                }
                if (dp[i][j] && j - i + 1 > result.size())
                    result = s.substr(i, j - i + 1);
            }
        }
        return result;
    }
};

// 方法二：中心扩展法
// P(i,j)←P(i+1,j−1)←P(i+2,j−2)←⋯←某一边界情况 转移方程只和左下角有关，直到对角线。因此，直接从对角线和上对角线开始遍历
// 也就是说，我们可以从每一种边界情况开始「扩展」，也可以得出所有的状态对应的答案。
class Solution2
{
public:
    string longestPalindrome(string s)
    {
        if (s.empty())
            return "";
        int start = 0, end = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            auto [left1, right1] = expandAroundCenter(s, i, i);     // 从对角线开始
            auto [left2, right2] = expandAroundCenter(s, i, i + 1); // 从上对角线开始
            if (right1 - left1 > end - start)
                start = left1, end = right1;
            if (right2 - left2 > end - start)
                start = left2, end = right2;
        }
        return s.substr(start, end - start + 1);
    }

private:
    pair<int, int> expandAroundCenter(const string &s, int left, int right)
    {
        while (left >= 0 && right < s.size() && s[left] == s[right])
            --left, ++right;
        return {left + 1, right - 1};
    }
};

// 方法三：Manacher算法
// 这里的臂长不包括中心字符
class Solution3
{
public:
    string longestPalindrome(string s)
    {
        string str = preProcess(s);
        vector<int> arm_length(str.size(), 0);
        int start = 0, end = 0;      // 记录最优解的开始和结束下标
        int right = -1, center = -1; // 目前访问过的最右边界及其中心
        for (int current = 0; current < str.size(); current++)
        {
            if (current < right) // 如果当前点在最右边界内，利用已知信息，即current关于center的对称点存储了其臂长
            {
                int min_cur_arm_len = min(right - current, arm_length[2 * center - current]); // 即：min(关于center的对称点的臂长, 最右边界-当前位置)
                arm_length[current] = expandArmLength(str, current - min_cur_arm_len, current + min_cur_arm_len);
            }
            else // 当前点在最右边界外，直接扩展
            {
                arm_length[current] = expandArmLength(str, current, current);
            }
            if (current + arm_length[current] > right) // 更新最右边界及其中心
            {
                right = current + arm_length[current];
                center = current;
            }
            if (arm_length[current] * 2 + 1 > end - start) // 更新最优解
            {
                start = current - arm_length[current];
                end = current + arm_length[current];
            }
        }
        string result;
        for (int i = start; i <= end; ++i)
        {
            if (str[i] != '#')
                result += str[i];
        }
        return result;
    }

private:
    string preProcess(const string &s)
    {
        string ret = "#";
        for (char c : s)
        {
            ret += c;
            ret += "#";
        }
        return ret;
    }

    int expandArmLength(const string &s, int left, int right)
    {
        while (left >= 0 && right < s.size() && s[left] == s[right])
            --left, ++right;
        return (right - left - 2) / 2; // 减去两端多扩展的部分，再除以2
    }
};