#include <vector>
#include <queue>
using namespace std;
// 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。

// 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

// 你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。
class Solution
{
public:
    int findKthLargest(vector<int> &nums, int k)
    {
        priority_queue<int, vector<int>, greater<int>> pq; // 小顶堆
        for (int i = 0; i < nums.size(); i++)
        {
            pq.push(nums[i]);
        }
        while (pq.size() > k)
        {
            pq.pop();
        }
        return pq.top();
    }
};

class Solution2
{
public:
    int findKthLargest(vector<int> &nums, int k)
    {
        priority_queue<int, vector<int>, greater<int>> pq; // 小顶堆
        for (int i = 0; i < nums.size(); i++)
        {
            if (pq.size() < k)
                pq.push(nums[i]);
            else if (nums[i] > pq.top())
            {
                pq.pop();
                pq.push(nums[i]);
            }
        }
        return pq.top();
    }
};