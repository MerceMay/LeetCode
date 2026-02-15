#include <string>
using namespace std;
// 如果在将所有大写字符转换为小写字符、并移除所有非字母数字字符之后，短语正着读和反着读都一样。则可以认为该短语是一个 回文串 。

// 字母和数字都属于字母数字字符。

// 给你一个字符串 s，如果它是 回文串 ，返回 true ；否则，返回 false 。
class Solution
{
public:
    bool isPalindrome(string s)
    {
        int left = 0;
        int right = s.size() - 1;
        while (left < right)
        {
            // 移动左指针，直到找到字母或数字
            while (left < right && isAlphanumeric(s[left]) == -1)
                left++;
            // 移动右指针，直到找到字母或数字
            while (left < right && isAlphanumeric(s[right]) == -1)
                right--;
            // 比较字符
            if (left < right)
            {
                if (isAlphanumeric(s[left]) != isAlphanumeric(s[right]))
                    return false;
                left++;
                right--;
            }
        }
        return true;
    }

private:
    int isAlphanumeric(char c)
    {
        if (c >= 'A' && c <= 'Z')
            return c + 'a' - 'A'; // 转换为小写字母
        if (c >= 'a' && c <= 'z')
            return c;
        if (c >= '0' && c <= '9')
            return c;
        return -1; // 非字母数字字符
    }
};