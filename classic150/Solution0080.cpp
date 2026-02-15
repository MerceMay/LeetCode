using namespace std;
#include <vector>
// 给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使得出现次数超过两次的元素只出现两次 ，返回删除后数组的新长度。

// 不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

// 慢指针表示已经排序好的数组,p[0, slow-1]都是排序好了的数组
// 快指针一开始是和慢指针一个位置，直到，出现了第三个重复的元素，此时需要慢指针不动，快指针继续动
class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        if (nums.size() <= 2)
            return nums.size();
        int slow = 2;
        int fast = 2;
        while (fast < nums.size())
        {
            if (nums[slow - 2] != nums[fast]) // slow如果出现了第三个重复的元素，nums[slow-2] == nums[fast]，则不++slow，否则++
                nums[slow++] = nums[fast];
            fast++;
        }
        return slow;
    }
};