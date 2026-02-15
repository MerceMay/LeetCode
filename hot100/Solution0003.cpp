#include <iostream>
#include <unordered_set>
#include <array>
using namespace std;
// 给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。

// 示例 1:

// 输入: s = "abcabcbb"
// 输出: 3
// 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
// 示例 2:

// 输入: s = "bbbbb"
// 输出: 1
// 解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
// 示例 3:

// 输入: s = "pwwkew"
// 输出: 3
// 解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
//      请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

// 提示：

// 0 <= s.length <= 5 * 104
// s 由英文字母、数字、符号和空格组成
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        unordered_set<char> charSet; // 用于存储当前子串中的字符
        int left = 0;
        int max_len = 0;
        for (int right = 0; right < s.size(); right++)
        {
            while (charSet.count(s[right]))
            {
                charSet.erase(s[left]);
                left++;
            }
            charSet.insert(s[right]); // 将当前字符添加到集合中
            max_len = max(max_len, right - left + 1);
        }
        return max_len;
    }
};

class Solution2
{
public:
    int lengthOfLongestSubstring(string s)
    {
        array<int, 128> charIndex; // 下标是char，存储的数据是字符最后出现的位置+1（方便left直接跳过right重复的地方）
        int left = 0;
        int max_len = 0;
        for (int right = 0; right < s.size(); right++)
        {
            char ch = s[right];
            left = max(left, charIndex[ch]);
            max_len = max(max_len, right - left + 1);
            charIndex[ch] = right + 1; // 更新字符最后出现的位置+1
        }
        return max_len;
    }
};