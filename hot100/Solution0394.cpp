#include <string>
#include <stack>
using namespace std;
// 给定一个经过编码的字符串，返回它解码后的字符串。

// 编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

// 你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

// 此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

// 测试用例保证输出的长度不会超过 105。

// 示例 1：

// 输入：s = "3[a]2[bc]"
// 输出："aaabcbc"
// 示例 2：

// 输入：s = "3[a2[c]]"
// 输出："accaccacc"
// 示例 3：

// 输入：s = "2[abc]3[cd]ef"
// 输出："abcabccdcdcdef"
// 示例 4：

// 输入：s = "abc3[cd]xyz"
// 输出："abccdcdcdxyz"

// 提示：

// 1 <= s.length <= 30
// s 由小写英文字母、数字和方括号 '[]' 组成
// s 保证是一个 有效 的输入。
// s 中所有整数的取值范围为 [1, 300]
class Solution
{
public:
    string decodeString(string s)
    {
        string result = "";
        stack<string> stk;
        for (int i = 0; i < s.length(); i++)
        {
            char c = s[i];
            if (isdigit(c))
            {
                string num_str = "";
                while (i < s.length() && isdigit(s[i]))
                {
                    num_str += s[i];
                    i++;
                }
                stk.push(num_str);
                i--; // 回退一步
            }
            else if (isalpha(c) || c == '[')
                stk.push(string(1, c));
            else // ']'
            {
                string sub_str = "";
                while (!stk.empty() && stk.top() != "[")
                {
                    sub_str = stk.top() + sub_str;
                    stk.pop();
                }
                stk.pop(); // 弹出"["
                int mul = 1;
                if (!stk.empty() && isdigit(stk.top()[0]))
                {
                    mul = stoi(stk.top());
                    stk.pop();
                }
                string repeated_str = "";
                for (int j = 0; j < mul; j++)
                    repeated_str += sub_str;
                stk.push(repeated_str);
            }
        }
        while (!stk.empty())
        {
            result = stk.top() + result;
            stk.pop();
        }
        return result;
    }
};

// 方法二：双栈法：
class Solution
{
public:
    string decodeString(string s)
    {
        stack<string> str_stack;
        stack<int> num_stack;
        string current_str = "";
        int current_num = 0;
        for (char c : s)
        {
            if (isdigit(c))
                current_num = current_num * 10 + (c - '0');
            else if (c == '[')
            {
                num_stack.push(current_num); // current_num 是]与[之间的数字
                str_stack.push(current_str); // current_str 是上一个[]之前的字符串
                current_num = 0;
                current_str = "";
            }
            else if (c == ']')
            {
                int repeat_times = num_stack.top();
                num_stack.pop();
                string previous_str = str_stack.top();
                str_stack.pop();
                string temp_str = "";
                for (int i = 0; i < repeat_times; i++)
                    temp_str += current_str;
                current_str = previous_str + temp_str;
            }
            else
                current_str += c;
        }
        return current_str;
    }
};