#include <iostream>
#include <vector>
#include <array>
using namespace std;
// 给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

// 示例 1:

// 输入: s = "cbaebabacd", p = "abc"
// 输出: [0,6]
// 解释:
// 起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
// 起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。
//  示例 2:

// 输入: s = "abab", p = "ab"
// 输出: [0,1,2]
// 解释:
// 起始索引等于 0 的子串是 "ab", 它是 "ab" 的异位词。
// 起始索引等于 1 的子串是 "ba", 它是 "ab" 的异位词。
// 起始索引等于 2 的子串是 "ab", 它是 "ab" 的异位词。

// 提示:

// 1 <= s.length, p.length <= 3 * 104
// s 和 p 仅包含小写字母
class Solution
{
public:
    vector<int> findAnagrams(string s, string p)
    {
        vector<int> result;
        if (s.size() < p.size())
            return result;
        array<int, 26> p_count = {0};
        array<int, 26> s_count = {0};
        for (char ch : p)
        {
            p_count[ch - 'a']++;
        }
        for (int i = 0; i < p.size(); i++)
        {
            s_count[s[i] - 'a']++;
        }
        if (s_count == p_count)
            result.push_back(0);
        for (int i = p.size(); i < s.size(); i++)
        {
            s_count[s[i] - 'a']++;
            s_count[s[i - p.size()] - 'a']--;
            if (s_count == p_count)
                result.push_back(i - p.size() + 1);
        }
        return result;
    }
};

class Solution2
{
public:
    vector<int> findAnagrams(string s, string p)
    {
        if (s.size() < p.size())
            return vector<int>();
        vector<int> result;
        array<int, 26> count = {0};
        for (int i = 0; i < p.size(); i++)
        {
            count[s[i] - 'a']++;
            count[p[i] - 'a']--;
        }
        int differ = 0;
        for (int i = 0; i < 26; i++)
        {
            if (count[i] != 0)
                differ++;
        }
        if (differ == 0)
            result.push_back(0);
        for (int left = 0; left < s.size() - p.size(); left++)
        {
            // 先判断s[left]，即窗口左端是不是p中也有
            // 如果p中没有，即count[s[left] - 'a'] == 1，则左移的时候，differ--；
            // 如果p中有，即count[s[left] - 'a'] == 0，则左移的时候，differ++；
            if (count[s[left] - 'a'] == 1)
                differ--;
            else if (count[s[left] - 'a'] == 0)
                differ++;
            count[s[left] - 'a']--; // 把窗口向左移

            count[s[left + p.size()] - 'a']++; // 把窗口向右移
            // 再判断窗口右端是不是p中也有，
            // 如果p中没有，即count[s[left + p.size()] - 'a'] == 1，则右移的时候，differ++；
            // 如果p中有，即count[s[left + p.size()] - 'a'] == 0，则右移的时候，differ--；
            if (count[s[left + p.size()] - 'a'] == 1)
                differ++;
            else if (count[s[left + p.size()] - 'a'] == 0)
                differ--;
            if (differ == 0)
                result.push_back(left + 1); // 注意这里是left + 1，因为窗口左端已经向右移了
        }
        return result;
    }
};