#include <vector>
using namespace std;
// 给定一个包含红色、白色和蓝色、共 n 个元素的数组 nums ，原地 对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

// 我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

// 必须在不使用库内置的 sort 函数的情况下解决这个问题。

// 你能想出一个仅使用常数空间的一趟扫描算法吗？
// 方法一：三指针
class Solution
{
public:
    void sortColors(vector<int> &nums)
    {
        int red = 0, white = 0, blue = nums.size() - 1;
        while (white <= blue)
        {
            if (nums[white] == 0)
            {
                swap(nums[red], nums[white]);
                red++;
                white++;
            }
            else if (nums[white] == 1)
            {
                white++;
            }
            else
            {
                swap(nums[white], nums[blue]);
                blue--; // 这里white不能++，因为还需要和过来的数进行对比
            }
        }
    }
};

// 方法二：单指针，遍历两次
class Solution
{
public:
    void sortColors(vector<int> &nums)
    {
        int ptr = 0;
        for (int i = 0; i < nums.size(); i++) // 找出所有红
        {
            if (nums[i] == 0)
            {
                swap(nums[i], nums[ptr]);
                ptr++;
            }
        }
        for(int i = ptr; i < nums.size(); i++) // 找出所有白，放在红背后
        {
            if (nums[i] == 1)
            {
                swap(nums[i], nums[ptr]);
                ptr++;
            }
        }
    }
};

// 方法三：双指针
class Solution
{
public:
    void sortColors(vector<int> &nums)
    {
        // [0,p0)为0，[p0, p1)为1，[p1,n)为2
        int p0 = 0, p1 = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == 0)
            {
                swap(nums[i], nums[p0]);
                p0++;
                p1++;
            }
            else if (nums[i] == 1)
            {
                swap(nums[i], nums[p1]);
                p1++;
            }
        }
    }
};