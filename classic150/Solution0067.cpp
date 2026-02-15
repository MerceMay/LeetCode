#include <string>
#include <algorithm>
using namespace std;
// 给你两个二进制字符串 a 和 b ，以二进制字符串的形式返回它们的和。
class Solution
{
public:
    string addBinary(string a, string b)
    {
        int i = a.size() - 1, j = b.size() - 1;
        int carry = 0;
        string result;
        while (i >= 0 || j >= 0 || carry)
        {
            int sum = carry;
            if (i >= 0)
            {
                sum += a[i--] - '0';
            }
            if (j >= 0)
            {
                sum += b[j--] - '0';
            }
            result.push_back((sum % 2) + '0');
            carry = sum / 2;
        }
        reverse(result.begin(), result.end());
        return result;
    }
};