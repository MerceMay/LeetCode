#include <vector>
using namespace std;
// 给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和 n），可知至少存在一个重复的整数。

// 假设 nums 只有 一个重复的整数 ，返回 这个重复的数 。

// 你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1) 的额外空间。

// nums 中 只有一个整数 出现 两次或多次 ，其余整数均只出现 一次
// 如何证明 nums 中至少存在一个重复的数字?反证法
// 你可以设计一个线性级时间复杂度 O(n) 的解决方案吗？
class Solution
{
public:
    int findDuplicate(vector<int> &nums)
    {
        // 必定存在一个重复的数字，把问题转换成链表问题
        // 把每个数字当作指针指向下一个数字
        // 一共n+1个节点，节点值为1到n，存在环。因此快慢指针第一次相遇，然后快指针从头开始和慢指针一起走，最终相遇的点就是重复的数字
        int slow = nums[0];
        int fast = nums[0];
        do
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);
        fast = nums[0];
        while (fast != slow)
        {
            fast = nums[fast];
            slow = nums[slow];
        }
        return fast;
    }
};

// 方法二：使用二分查找：时间复杂度O(nlogn)，空间复杂度O(1)
class Solution2
{
    public:
    int findDuplicate(vector<int> &nums)
    {
        int left = 1;
        int right = nums.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            int count = 0;
            for (int i = 0; i < nums.size(); i++)
            {
                if (nums[i] <= mid)
                    count++;
            }
            if (count > mid) // 即在[left, mid]中大于一半，存在重复
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
};
