#include <vector>
using namespace std;
// 给定一个表示 大整数 的整数数组 digits，其中 digits[i] 是整数的第 i 位数字。这些数字按从左到右，从最高位到最低位排列。这个大整数不包含任何前导 0。

// 将大整数加 1，并返回结果的数字数组。
class Solution
{
public:
    vector<int> plusOne(vector<int> &digits)
    {
        int n = digits.size();
        int carry = 1; // 初始进位为1
        for (int i = n - 1; i >= 0 && carry; --i)
        {
            int sum = digits[i] + carry;
            digits[i] = sum % 10; // 更新当前位
            carry = sum / 10;     // 更新进位
        }
        if (carry)
            digits.insert(digits.begin(), carry); // 如果最高位还有进位，插入到数组开头
        return digits;
    }
};

// 如果 digits 的末尾没有 9，例如 [1,2,3]，那么我们直接将末尾的数加一，得到 [1,2,4] 并返回；
// 如果 digits 的末尾有若干个 9，例如 [1,2,3,9,9]，那么我们只需要找出从末尾开始的第一个不为 9 的元素，即 3，将该元素加一，得到 [1,2,4,9,9]。随后将末尾的 9 全部置零，得到 [1,2,4,0,0] 并返回。
// 如果 digits 的所有元素都是 9，例如 [9,9,9,9,9]，那么答案为 [1,0,0,0,0,0]。我们只需要构造一个长度比 digits 多 1 的新数组，将首元素置为 1，其余元素置为 0 即可。
// 算法
// 们只需要对数组 digits 进行一次逆序遍历，找出第一个不为 9 的元素，将其加一并将后续所有元素置零即可。如果 digits 中所有的元素均为 9，那么对应着「思路」部分的第三种情况，我们需要返回一个新的数组。
class Solution2
{
public:
    vector<int> plusOne(vector<int> &digits)
    {
        int n = digits.size();
        for (int i = n - 1; i >= 0; i--)
        {
            if (digits[i] != 9)
            {
                digits[i]++;
                for (int j = i + 1; j < n; j++)
                    digits[j] = 0;
                return digits;
            }
        }
        vector<int> ans(n + 1, 0);
        ans[0] = 1;
        return ans;
    }
};