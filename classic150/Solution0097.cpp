#include <string>
#include <vector>
using namespace std;
// 给定三个字符串 s1、s2、s3，请你帮忙验证 s3 是否是由 s1 和 s2 交错 组成的。

// 两个字符串 s 和 t 交错 的定义与过程如下，其中每个字符串都会被分割成若干 非空 子字符串：

// s = s1 + s2 + ... + sn
// t = t1 + t2 + ... + tm
// |n - m| <= 1
// 交错 是 s1 + t1 + s2 + t2 + s3 + t3 + ... 或者 t1 + s1 + t2 + s2 + t3 + s3 + ...
// 注意：a + b 意味着字符串 a 和 b 连接。
// 示例 1：

// 输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
// 输出：true
// dp[i][j]表示s1的前i个字符和s2的前j个字符能否交错组成s3的前i+j个字符。
// dp[i][j] 为 true 即s3 的最后一个字符（也就是第 i+j 个字符）必须是 s1 的第 i 个字符，或者 s2 的第 j 个字符：
// s1 的第 i 个字符等于 s3 的第 i + j 个字符，且 dp[i - 1][j] 为 true
// s2 的第 j 个字符等于 s3 的第 i + j 个字符，且 dp[i][j - 1] 为 true
class Solution
{
public:
    bool isInterleave(string s1, string s2, string s3)
    {
        int n1 = s1.size();
        int n2 = s2.size();
        int n3 = s3.size();
        if (n1 + n2 != n3)
            return false;
        vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));
        dp[0][0] = true;
        for (int i = 0; i <= n1; i++)
        {
            for (int j = 0; j <= n2; j++)
            {
                if (i > 0)
                    dp[i][j] = dp[i][j] || (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]);
                if (j > 0)
                    dp[i][j] = dp[i][j] || (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }
        return dp[n1][n2];
    }
};

// 只和上和左有关，可以用一维数组滚动数组优化
class Solution2
{
public:
    bool isInterleave(string s1, string s2, string s3)
    {
        int n1 = s1.size();
        int n2 = s2.size();
        int n3 = s3.size();
        if (n1 + n2 != n3)
            return false;
        vector<bool> dp(n2 + 1, false);
        dp[0] = true;
        for (int i = 0; i <= n1; i++)
        {
            for (int j = 0; j <= n2; j++)
            {
                if (i > 0)
                    dp[j] = dp[j] && s1[i - 1] == s3[i + j - 1]; // 注意，这里不能让dp[j] || ... 因为dp[j]是上一次的结果，可能为true
                if (j > 0)
                    dp[j] = dp[j] || (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }
        return dp[n2];
    }
};