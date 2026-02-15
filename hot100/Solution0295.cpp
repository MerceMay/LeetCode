#include <queue>
#include <set>
using namespace std;
// 中位数是有序整数列表中的中间值。如果列表的大小是偶数，则没有中间值，中位数是两个中间值的平均值。

// 例如 arr = [2,3,4] 的中位数是 3 。
// 例如 arr = [2,3] 的中位数是 (2 + 3) / 2 = 2.5 。
// 实现 MedianFinder 类:

// MedianFinder() 初始化 MedianFinder 对象。

// void addNum(int num) 将数据流中的整数 num 添加到数据结构中。

// double findMedian() 返回到目前为止所有元素的中位数。与实际答案相差 10-5 以内的答案将被接受。
class MedianFinder
{
private:
    priority_queue<int, vector<int>, less<int>> maxHeap;    // 存储较小的一半
    priority_queue<int, vector<int>, greater<int>> minHeap; // 存储较大的一半
public:
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        // 默认进大根堆
        if (maxHeap.empty() || num < maxHeap.top())
            maxHeap.push(num);
        else
            minHeap.push(num);

        // 调节平衡，两个堆最多只会相差一个元素
        if (maxHeap.size() > minHeap.size() + 1)
        {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if (minHeap.size() > maxHeap.size())
        {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian()
    {
        if (maxHeap.size() == minHeap.size())
            return (maxHeap.top() + minHeap.top()) / 2.0;
        else
            return maxHeap.top();
    }
};

// 方法二：使用已排序的数组+双指针
class MedianFinder
{
private:
    multiset<int> nums;
    multiset<int>::iterator left, right;

public:
    MedianFinder()
    {
        left = right = nums.end();
    }
    void addNum(int num)
    {
        const size_t n = nums.size();
        nums.insert(num);
        if (!n)
        {
            left = right = nums.begin();
        }
        else if (n & 1)
        {
            if (num < *left)
            {
                left--;
            }
            else
            {
                right++;
            }
        }
        else
        {
            if (num > *left && num < *right)
            {
                left++;
                right--;
            }
            else if (num >= *right)
            {
                left++;
            }
            else
            {
                right--;
                left = right;
            }
        }
    }

    double findMedian() { return (*left + *right) / 2.0; }
};