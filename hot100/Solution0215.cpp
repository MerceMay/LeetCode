#include <vector>
#include <queue>
using namespace std;
// 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。

// 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

// 你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。

// 示例 1:

// 输入: [3,2,1,5,6,4], k = 2
// 输出: 5
// 示例 2:

// 输入: [3,2,3,1,2,4,5,5,6], k = 4
// 输出: 4

// 提示：

// 1 <= k <= nums.length <= 105
// -104 <= nums[i] <= 104
// 方法一：使用容器。时间复杂度O(NlogK)
class Solution1
{
public:
    int findKthLargest(vector<int> &nums, int k)
    {
        priority_queue<int, vector<int>, greater<int>> minHeap; // 小顶堆
        for (int num : nums)
        {
            if (minHeap.size() < k)
            {
                minHeap.push(num);
            }
            else if (num > minHeap.top())
            {
                minHeap.pop();
                minHeap.push(num);
            }
        }
        return minHeap.top();
    }
};

// 方法二：自定义小根堆：时间复杂度O(NlogK)
class Solution2
{
private:
    template <typename T, typename Compare = std::less<T>>
    class Heap
    {
    private:
        std::vector<T> data;
        Compare comp;

    public:
        Heap() = default;
        Heap(Compare c) : comp(c) {}

        void push(const T &value)
        {
            data.push_back(value);
            sift_up(data.size() - 1);
        }

        void pop()
        {
            if (empty())
                return;
            std::swap(data.front(), data.back());
            data.pop_back();
            if (!empty())
                sift_down(0);
        }

        const T &top() const
        {
            if (empty())
                throw std::out_of_range("Heap is empty");
            return data.front();
        }

        bool empty() const
        {
            return data.empty();
        }

        size_t size() const
        {
            return data.size();
        }

    private:
        void sift_up(size_t index)
        {
            while (index > 0)
            {
                size_t parent = (index - 1) / 2;
                if (!comp(data[parent], data[index]))
                    break;
                std::swap(data[parent], data[index]);
                index = parent;
            }
        }

        void sift_down(size_t index)
        {
            while (index < data.size())
            {
                size_t left = index * 2 + 1;
                size_t right = index * 2 + 2;
                size_t smallest = index;

                if (left < data.size() && comp(data[smallest], data[left]))
                    smallest = left;
                if (right < data.size() && comp(data[smallest], data[right]))
                    smallest = right;
                if (smallest == index)
                    break;

                std::swap(data[index], data[smallest]);
                index = smallest;
            }
        }
    };

public:
    int findKthLargest(vector<int> &nums, int k)
    {
        Heap<int, std::greater<int>> minHeap; // 小顶堆
        for (int num : nums)
        {
            if (minHeap.size() < k)
            {
                minHeap.push(num);
            }
            else if (num > minHeap.top())
            {
                minHeap.pop();
                minHeap.push(num);
            }
        }
        return minHeap.top();
    }
};

// 方法三：使用自定义大根堆：时间复杂度O(n+klogn)
class Solution3
{
private:
    void buildMaxHeap(vector<int> &nums, int heapSize)
    {
        for (int i = heapSize / 2 - 1; i >= 0; i--)
            maxHeapify(nums, i, heapSize);
    }

    void maxHeapify(vector<int> &nums, int index, int heapSize)
    {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int largest = index;

        if (left < heapSize && nums[left] > nums[largest])
            largest = left;
        if (right < heapSize && nums[right] > nums[largest])
            largest = right;

        if (largest != index)
        {
            std::swap(nums[index], nums[largest]);
            maxHeapify(nums, largest, heapSize);
        }
    }

public:
    int findKthLargest(vector<int> &nums, int k)
    {
        int heapSize = nums.size();
        buildMaxHeap(nums, heapSize);
        for (int i = nums.size() - 1; i >= nums.size() - k + 1; i--)
        {
            std::swap(nums[0], nums[i]);
            heapSize--;
            maxHeapify(nums, 0, heapSize);
        }
        return nums[0];
    }
};

// 问题转换成找排序后n-k下标的元素。快排非常适合（pivot左边是小于它的数，右边是大于它的数）
class Solution4
{
private:
    int quickselect(vector<int> &nums, int left, int right, int k_smallest)
    {
        if (left == right) // 找到了，直接返回
            return nums[left];
        int pivot = nums[left];
        int i = left - 1, j = right + 1;
        while (i < j)
        {
            do
                i++;
            while (nums[i] < pivot); // 从左向右找到第一个大于等于基准值的元素
            do
                j--;
            while (nums[j] > pivot); // 从右向左找到第一个小于等于基准值的元素
            if (i < j)
                std::swap(nums[i], nums[j]); // 如果指针没有交叉，即还有在pivot两边的元素不在正确位置，交换
        }
        if (k_smallest <= j)
            return quickselect(nums, left, j, k_smallest); // 要找的元素在左边
        return quickselect(nums, j + 1, right, k_smallest); // 要找的元素在右边
    }

public:
    int findKthLargest(vector<int> &nums, int k)
    {
        int n = nums.size();
        return quickselect(nums, 0, n - 1, n - k);
    }
};