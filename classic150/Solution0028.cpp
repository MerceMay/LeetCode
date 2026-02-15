#include <string>
#include <vector>
using namespace std;
// 给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。如果 needle 不是 haystack 的一部分，则返回  -1 。

// 示例 1：

// 输入：haystack = "sadbutsad", needle = "sad"
// 输出：0
// 解释："sad" 在下标 0 和 6 处匹配。
// 第一个匹配项的下标是 0 ，所以返回 0 。
// 示例 2：

// 输入：haystack = "leetcode", needle = "leeto"
// 输出：-1
// 解释："leeto" 没有在 "leetcode" 中出现，所以返回 -1 。

// 提示：

// 1 <= haystack.length, needle.length <= 104
// haystack 和 needle 仅由小写英文字符组成
class Solution
{
public:
    int strStr(string haystack, string needle)
    {
        if (needle.empty())
            return 0;
        int n = haystack.size(), m = needle.size();
        if (n < m)
            return -1;
        vector<int> lps = getLPS(needle);
        for (int i = 0, j = 0; i < n;)
        {
            if (haystack[i] == needle[j])
            {
                i++;
                j++;
            }
            else if (j)
                j = lps[j - 1];
            else
                i++;

            if (j == m)
                return i - m;
        }
        return -1;
    }

private:
    vector<int> getLPS(const string &pattern)
    {
        int m = pattern.size();
        vector<int> lps(m, 0);
        int len = 0; // 前缀长度
        int i = 1;
        while (i < m) // 遍历
        {
            if (pattern[i] == pattern[len]) // 如果当前字符与前缀匹配，前缀长度++，更新lps
                lps[i++] = ++len;
            else if (len) // 如果不匹配，回退前缀长度，直到匹配
                len = lps[len - 1];
            else // 如果前缀长度为0，直接更新lps
                lps[i++] = 0;
        }
        return lps;
    }

    vector<int> KMP(const string &text, const string &pattern)
    {
        if (pattern.empty())
            return {};
        int n = text.size(), m = pattern.size();
        if (n < m)
            return {};
        vector<int> lps = getLPS(pattern);
        vector<int> result;
        int i = 0, j = 0; // i遍历text，j遍历pattern
        while (i < n)
        {
            if (text[i] == pattern[j]) // 如果匹配，继续
            {
                i++;
                j++;
            }
            else if (j) // 如果不匹配，回退pattern：lps保证了i不需要回退
                j = lps[j - 1];
            else // 如果j为0，直接移动i
                i++;

            if (j == m) // 找到一个匹配
            {
                result.push_back(i - m);
                j = lps[j - 1]; // 相当于pattern[m]必不可能等于text[i]，回退pattern
            }
        }
        return result;
    }
};