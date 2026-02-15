#include <iostream>
#include <unordered_map>
#include <string>
#include <climits>
using namespace std;
// 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

// 注意：

// 对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
// 如果 s 中存在这样的子串，我们保证它是唯一的答案。

// 示例 1：

// 输入：s = "ADOBECODEBANC", t = "ABC"
// 输出："BANC"
// 解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。
// 示例 2：

// 输入：s = "a", t = "a"
// 输出："a"
// 解释：整个字符串 s 是最小覆盖子串。
// 示例 3:

// 输入: s = "a", t = "aa"
// 输出: ""
// 解释: t 中两个字符 'a' 均应包含在 s 的子串中，
// 因此没有符合条件的子字符串，返回空字符串。

// 提示：

// m == s.length
// n == t.length
// 1 <= m, n <= 105
// s 和 t 由英文字母组成

// 进阶：你能设计一个在 o(m+n) 时间内解决此问题的算法吗？
class Solution
{
public:
    string minWindow(string s, string t)
    {
        unordered_map<char, int> t_count;      // 记录t中每个字符的数量
        unordered_map<char, int> window_count; // 记录当前窗口中每个字符的数量
        int start_index = 0;                   // 记录最小子串的起始位置
        int min_len = INT_MAX;                 // 最小覆盖子串的长度
        for (char ch : t)
        {
            t_count[ch]++;
        }
        int characters = t_count.size(); // 需要匹配的字符种类数
        int match = 0;
        int left = 0, right = 0; // 左右指针
        // 先让右指针无限扩展
        while (right < s.size())
        {
            window_count[s[right]]++; // 扩展右指针，加入当前字符
            if (t_count.count(s[right]) && window_count[s[right]] == t_count[s[right]])
            {
                match++;
            }
            right++;
            while (match == characters)
            {
                if (right - left < min_len)
                {
                    start_index = left;
                    min_len = right - left;
                }
                window_count[s[left]]--; // 收缩左指针，移除当前字符
                if (t_count[s[left]] && window_count[s[left]] < t_count[s[left]])
                {
                    match--; // 如果当前字符的数量小于t中的数量，匹配失败
                }
                left++;
            }
        }
        return min_len == INT_MAX ? "" : s.substr(start_index, min_len);
    }
};

// 优化解
class Solution2
{
public:
    string minWindow(string s, string t)
    {
        int n = s.size();
        int count = t.size();
        int occur[128]{};
        for (char ch : t)
            occur[ch]++;
        int left = 0, right = 0;
        int minStart = 0, minSize = INT_MAX;
        while (right < n)
        {
            // 右扩
            while (right < n && count)
            {
                if (occur[s[right++]]-- > 0) // 将right指向的字符加入窗口，则occur需要减一，并且立马右移
                    count--;                 // 对于那些本来就不在t中的字符，occur会小于0，于是不会使得count减少
            }
            // 满足了，左缩
            while (!count)
            {
                if (right - left < minSize)
                {
                    minSize = right - left;
                    minStart = left;
                }
                if (++occur[s[left++]] > 0) // 左缩导致t中的字符移出窗口，需要将count++
                    count++;
            }
        }
        return minSize == INT_MAX ? "" : s.substr(minStart, minSize);
    }
};