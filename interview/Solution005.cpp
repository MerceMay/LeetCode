// 反转字符串中的所有单词。要求尝试使用O（1）的额外空间复杂度原地解法，O（N）解法的也额外给出。
#include <vector>
#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

class Solution1
{
public:
    void reverseWords(string &s)
    {
        istringstream ss(s);
        std::vector<string> words;
        string word;
        while (ss >> word)
            words.push_back(word);
        reverse(words.begin(), words.end());
        s.clear();
        for (int i = 0; i < words.size(); i++)
        {
            s += words[i];
            if (i != words.size() - 1)
                s += " ";
        }
    }
};

class Solution2
{
public:
    void reverseWords(string &s)
    {
        std::reverse(s.begin(), s.end());
        int n = s.size(), start = 0;
        for (int i = 0; i <= n; i++)
        {
            if (i == n || s[i] == ' ')
            {
                std::reverse(s.begin() + start, s.begin() + i);
                start = i + 1;
            }
        }
    }
};