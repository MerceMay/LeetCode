#include <vector>
#include <string>
using namespace std;
// 给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。

// 你可以对一个单词进行如下三种操作：

// 插入一个字符
// 删除一个字符
// 替换一个字符

// 示例 1：

// 输入：word1 = "horse", word2 = "ros"
// 输出：3
// 解释：
// horse -> rorse (将 'h' 替换为 'r')
// rorse -> rose (删除 'r')
// rose -> ros (删除 'e')
// 示例 2：

// 输入：word1 = "intention", word2 = "execution"
// 输出：5
// 解释：
// intention -> inention (删除 't')
// inention -> enention (将 'i' 替换为 'e')
// enention -> exention (将 'n' 替换为 'x')
// exention -> exection (将 'n' 替换为 'c')
// exection -> execution (插入 'u')
class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        // dp[i][j]表示将word1的前i个字符转换成word2的前j个字符所需的最少操作数
        // dp[i][j] = dp[i-1][j](word1的前i-1个字符)表示删除一个字符
        // dp[i][j] = dp[i][j-1](word2的前j-1个字符)表示插入一个字符
        // dp[i][j] = dp[i-1][j-1](word1的前i-1个字符和word2的前j-1个字符)表示替换一个字符
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
        for (int i = 0; i <= word1.size(); i++)
        {
            for (int j = 0; j <= word2.size(); j++)
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
        return dp[word1.size()][word2.size()];
    }
};

// 方法二：滚动数组，只和上、左、左上有关
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