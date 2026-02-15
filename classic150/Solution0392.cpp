#include <string>
#include <vector>
using namespace std;
// 给定字符串 s 和 t ，判断 s 是否为 t 的子序列。

// 字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。

// 进阶：

// 如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >= 10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？
class Solution
{
public:
    bool isSubsequence(string s, string t)
    {
        int n = s.size();
        int m = t.size();
        int i = 0, j = 0;
        while (i < n && j < m)
        {
            if (s[i] == t[j])
                i++;
            j++;
        }
        return i == n;
    }
};

class Solution2
{
public:
    // dp[i][j] 表示t在位置i后，字符j第一次出现的位置
    bool isSubsequence(string s, string t)
    {
        int n = s.size(), m = t.size();
        vector<vector<int>> dp(m + 1, vector<int>(26, 0));
        for (int i = 0; i < 26; i++)
            dp[m][i] = m;

        for (int i = m - 1; i >= 0; i--)
        {
            for (int j = 0; j < 26; j++)
                if (t[i] - 'a' == j)
                    dp[i][j] = i;
                else
                    dp[i][j] = dp[i + 1][j];
        }
        int pos = 0;
        for (int i = 0; i < n; i++)
        {
            if (dp[pos][s[i] - 'a'] == m)
                return false;
            pos = dp[pos][s[i] - 'a'] + 1;
        }
        return true;
    }
};