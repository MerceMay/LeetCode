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

// 示例 1：

// 输入
// ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
// [[], [1], [2], [], [3], []]
// 输出
// [null, null, null, 1.5, null, 2.0]

// 解释
// MedianFinder medianFinder = new MedianFinder();
// medianFinder.addNum(1);    // arr = [1]
// medianFinder.addNum(2);    // arr = [1, 2]
// medianFinder.findMedian(); // 返回 1.5 ((1 + 2) / 2)
// medianFinder.addNum(3);    // arr[1, 2, 3]
// medianFinder.findMedian(); // return 2.0
// 提示:

// -105 <= num <= 105
// 在调用 findMedian 之前，数据结构中至少有一个元素
// 最多 5 * 104 次调用 addNum 和 findMedian
// 保证maxHeap.size()不超过minHeap.size()的1个元素
class MedianFinder
{
private:
    priority_queue<int, vector<int>, less<int>> maxHeap;    // 大顶堆，存储较小的一半元素
    priority_queue<int, vector<int>, greater<int>> minHeap; // 小顶堆，存储较大的一半元素
public:
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        // 默认存储到大顶堆，如果新数小于大顶堆堆顶，则弹出大顶堆堆顶，插入新数，把弹出的堆顶插入小顶堆
        if (maxHeap.empty() || num <= maxHeap.top())
        {
            maxHeap.push(num);
            if (maxHeap.size() > minHeap.size() + 1)
            {
                minHeap.push(maxHeap.top());
                maxHeap.pop();
            }
        }
        else
        {
            minHeap.push(num);
            if (minHeap.size() > maxHeap.size())
            {
                maxHeap.push(minHeap.top());
                minHeap.pop();
            }
        }
    }

    double findMedian()
    {
        if (maxHeap.size() > minHeap.size())
        {
            return maxHeap.top();
        }
        else
        {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
    }
};

class MedianFinder2
{
private:
    multiset<int> data;
    multiset<int>::iterator left, right;

public:
    MedianFinder2()
    {
        left = right = data.end();
    }

    void addNum(int num)
    {
        const int n = data.size();
        data.insert(num);
        if (n == 0)
        {
            left = right = data.begin();
        }
        else if (n & 1) // n is odd
        {
            if (num < *left)
            {
                --left;
            }
            else
            {
                left++;
            }
        }
        else // n is even
        {
            if (num >= *left && num < *right)
            {
                left++;
                right--;
            }
            else if (num >= *right)
            {
                right++;
            }
            else
            {
                left--;
            }
        }
    }

    double findMedian()
    {
        return (*left + *right) / 2.0;
    }
};