#include <cstdint>
using namespace std;
// 颠倒给定的 32 位无符号整数的二进制位。
class Solution
{
public:
    // 题目明确了n是正偶数，因此，两侧都是0，n进行右移，符号位置依然是0
    int reverseBits(int n)
    {
        int result = 0;
        for (int i = 0; i < 32; i++)
        {
            int bit = n & 1; // 获取n的最低位
            result <<= 1;    // result左移一位，为最低位腾出位置
            result |= bit;   // 将bit放入result的最低位
            n >>= 1;         // n右移一位，处理下一位
        }
        return result;
    }
};

// 颠倒可以理解为整体交换，因此可以使用归并，先两两交换，再四四交换，依次类推
class Solution2
{
private:
    const unsigned int M1 = 0x55555555; // 01010101010101010101010101010101
    const unsigned int M2 = 0x33333333; // 00110011001100110011001100110011
    const unsigned int M4 = 0x0f0f0f0f; // 00001111000011110000111100001111
    const unsigned int M8 = 0x00ff00ff; // 00000000111111110000000011111111
public:
    uint32_t reverseBits(uint32_t n)
    {
        n = ((n >> 1) & M1) | ((n & M1) << 1); // 两两交换
        n = ((n >> 2) & M2) | ((n & M2) << 2); // 四四交换
        n = ((n >> 4) & M4) | ((n & M4) << 4); // 八八交换
        n = ((n >> 8) & M8) | ((n & M8) << 8); // 十六十六交换
        n = (n >> 16) | (n << 16);             // 十六位交换
        return n;
    }
};