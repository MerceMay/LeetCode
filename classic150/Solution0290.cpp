#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;
// 给定一种规律 pattern 和一个字符串 s ，判断 s 是否遵循相同的规律。

// 这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 s 中的每个非空单词之间存在着双向连接的对应规律。

// 示例1:

// 输入: pattern = "abba", s = "dog cat cat dog"
// 输出: true
// 示例 2:

// 输入:pattern = "abba", s = "dog cat cat fish"
// 输出: false
// 示例 3:

// 输入: pattern = "aaaa", s = "dog cat cat dog"
// 输出: false

// 提示:

// 1 <= pattern.length <= 300
// pattern 只包含小写英文字母
// 1 <= s.length <= 3000
// s 只包含小写英文字母和 ' '
// s 不包含 任何前导或尾随对空格
// s 中每个单词都被 单个空格 分隔

// 双向映射
class Solution
{
public:
    bool wordPattern(string pattern, string s)
    {
        stringstream ss(s);
        string word;
        unordered_map<char, string> charToWord;
        unordered_map<string, char> wordToChar;
        int i = 0;
        while (ss >> word)
        {
            if (i == pattern.size())
                return false;
            char c = pattern[i];
            if (charToWord.count(c) == 0 && wordToChar.count(word) == 0)
            {
                charToWord[c] = word;
                wordToChar[word] = c;
            }
            else if (charToWord[c] != word || wordToChar[word] != c)
            {
                return false;
            }
            i++;
        }
        return i == pattern.size();
    }
};