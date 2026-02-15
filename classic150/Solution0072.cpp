#include <string>
#include <vector>
using namespace std;
// 给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。

// 你可以对一个单词进行如下三种操作：

// 插入一个字符
// 删除一个字符
// 替换一个字符
// dp[i][j] 表示将word1的前i个字符转换成word2的前j个字符所需的最少操作数
// 删除word1的第i个字符，dp[i][j] = dp[i-1][j] + 1
// 插入word2的第j个字符，dp[i][j] = dp[i][j-1] + 1
// 替换word1的第i个字符为word2的第j个字符，dp[i][j] = dp[i-1][j-1] + 1
// 如果word1的第i个字符等于word2的第j个字符，那么不需要操作，dp[i][j] = dp[i-1][j-1]
// dp[i][j] = min(dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1] + (word1[i-1] == word2[j-1] ? 0 : 1))
class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int m = word1.size();
        int n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i <= m; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                if (i == 0)
                    dp[i][j] = j; // word1为空，插入j个字符
                else if (j == 0)
                    dp[i][j] = i; // word2为空，删除i个字符
                else if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1]; // 字符相同，不需要操作
                else
                    dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1; // 删除、插入、替换
                        }
        }
        return dp[m][n];
    }
};

// 只和上，左，左上有关，可以用一维数组滚动数组优化
class Solution2
{
public:
    int minDistance(string word1, string word2)
    {
        if (word1.size() < word2.size())
            return minDistance(word2, word1);
        vector<int> dp(word2.size() + 1, 0);
        for (int j = 0; j <= word2.size(); j++) // 初始化第一行
            dp[j] = j;
        for (int i = 1; i <= word1.size(); i++)
        {
            int upleft = dp[0]; // dp[i-1][j-1]
            dp[0] = i;          // 第一列
            for (int j = 1; j <= word2.size(); j++)
            {
                int temp = dp[j]; // dp[i-1][j]
                if (word1[i - 1] == word2[j - 1])
                    dp[j] = upleft; // 字符相同，不需要操作
                else
                    dp[j] = min(dp[j], min(dp[j - 1], upleft)) + 1; // 删除、插入、替换
                upleft = temp;                                      // dp[i-1][j-1]
            }
        }
        return dp[word2.size()];
    }
};