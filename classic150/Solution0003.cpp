#include <string>
#include <array>
using namespace std;
// 给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        array<int, 256> charIndex; // charIndex[i] = j 表示字符 i 上一次出现的位置是 j
        charIndex.fill(-1);        // 初始化为 -1，表示字符未出现过
        int maxLength = 0;
        int left = 0;
        for (int right = 0; right < s.size(); right++)
        {
            char ch = s[right];
            if (charIndex[ch] != -1)
            {
                left = max(left, charIndex[ch] + 1); // 更新左指针位置
            }
            charIndex[ch] = right;                  // 更新字符最后出现的位置
            maxLength = max(maxLength, right - left + 1); // 更新最大长度
        }
        return maxLength;
    }
};
