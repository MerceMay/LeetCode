#include <string>
#include <vector>
#include <stack>
using namespace std;
// 给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号 子串 的长度。

// 左右括号匹配，即每个左括号都有对应的右括号将其闭合的字符串是格式正确的，比如 "(()())"。

// 示例 1：

// 输入：s = "(()"
// 输出：2
// 解释：最长有效括号子串是 "()"
// 示例 2：

// 输入：s = ")()())"
// 输出：4
// 解释：最长有效括号子串是 "()()"
// 示例 3：

// 输入：s = ""
// 输出：0
// 方法一：动态规划
// dp[i]表示以i结尾的最长有效括号子串的长度
// 有效子串必须以')'结尾
class Solution
{
public:
    int longestValidParentheses(string s)
    {
        vector<int> dp(s.size(), 0);
        int maxLength = 0;
        for (int i = 1; i < s.size(); ++i)
        {
            if (s[i] != ')')
                continue;
            if (s[i - 1] == '(') // 形如...()
                dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
            else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(')                         // 形如(.))，需要满足((.))
                dp[i] = dp[i - 1] + 2 + ((i - dp[i - 1] - 1 > 0) ? dp[i - dp[i - 1] - 2] : 0); // 即左边的子串加上两头的括号，如果最左边的括号前面还有有效子串，则加上
            maxLength = max(maxLength, dp[i]);
        }
        return maxLength;
    }
};

// 方法二：栈
class Solution2
{
public:
    int longestValidParentheses(string s)
    {
        int maxLength = 0;
        stack<int> stk;
        stk.push(-1); // 哨兵
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
                stk.push(i);
            else
            {
                stk.pop();
                if (stk.empty())
                    stk.push(i); // 如果栈空了，说明当前的右括号没有匹配的左括号，因此将当前右括号的位置入栈作为新的哨兵
                else
                    maxLength = max(maxLength, i - stk.top()); // 否则计算当前有效子串的长度
            }
        }
        return maxLength;
    }
};

// 方法三：贪心算法。
// 先从左往右遍历，碰见一个左右括号就分别计数。
// 如果相等，则更新最大长度。如果出现右边大于左边的情况，重置计数，继续遍历。
// 对于(()的情况，需要从右往左重新遍历一次
class Solution3
{
public:
    int longestValidParentheses(string s)
    {
        int maxLength = 0;
        int left = 0, right = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
                left++;
            else
                right++;
            if (left == right)
                maxLength = max(maxLength, 2 * left);
            else if (right > left)
                left = right = 0;
        }
        left = right = 0;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            if (s[i] == ')')
                right++;
            else
                left++;
            if (left == right)
                maxLength = max(maxLength, 2 * right);
            else if (left > right)
                left = right = 0;
        }
        return maxLength;
    }
};