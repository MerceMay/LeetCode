#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;
// 给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。

// 示例 1：

// 输入：nums = [1,1,1,2,2,3], k = 2

// 输出：[1,2]

// 示例 2：

// 输入：nums = [1], k = 1

// 输出：[1]

// 示例 3：

// 输入：nums = [1,2,1,2,1,2,3,1,3,2], k = 2

// 输出：[1,2]

// 提示：

// 1 <= nums.length <= 105
// k 的取值范围是 [1, 数组中不相同的元素的个数]
// 题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的

// 进阶：你所设计算法的时间复杂度 必须 优于 O(n log n) ，其中 n 是数组大小。

// 方法一：小根堆或者大根堆：
// 小根堆：如果新数更大，进去，维持堆为k的大小，最后剩下的k个数就是最大的。因为小根堆每次进出复杂度为o(logk)
// 大根堆，全部进去，最后出来k个。但是每次进出复杂度为o(logn)
// 因此，小根堆更优
class Solution
{
private:
    struct cmp
    {
        bool operator()(const pair<int, int> &a, const pair<int, int> &b)
        {
            return a.second > b.second; // 小根堆，按频率升序排列
        }
    };

public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> freq; // 统计频率
        for (int num : nums)
        {
            freq[num]++;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> minHeap; // 小根堆，按频率升序排列
        for (const auto &f : freq)
        {
            if (minHeap.size() < k)
            {
                minHeap.push(f);
            }
            else if (f.second > minHeap.top().second)
            {
                minHeap.pop();
                minHeap.push(f);
            }
        }

        vector<int> result;
        while (!minHeap.empty())
        {
            result.push_back(minHeap.top().first);
            minHeap.pop();
        }
        return result;
    }
};

// 方法二：就地建大根堆，最后弹出前k个元素
class Solution2
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> freqMap;
        for (int num : nums)
            freqMap[num]++;
        vector<pair<int, int>> freqVec(freqMap.begin(), freqMap.end());
        // 开始建堆
        int n = freqVec.size();
        for (int i = n / 2 - 1; i >= 0; i--) // 从最后一个非叶子节点开始，因为叶子节点都是符合堆的性质
            siftdown(freqVec, i, n);

        vector<int> result;
        for (int i = 0; i < k; i++)
        {
            result.push_back(freqVec[i].first);
            std::swap(freqVec[0], freqVec[n - 1 - i]); // 把堆顶元素和最后一个元素交换
            siftdown(freqVec, 0, n - 1 - i);           // 重新调整堆，在逻辑上减小堆的大小
        }
        return result;
    }

private:
    void siftdown(vector<pair<int, int>> &heap, int index, int heapSize)
    {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int largest = index;

        if (left < heapSize && heap[left].second > heap[largest].second)
            largest = left;
        if (right < heapSize && heap[right].second > heap[largest].second)
            largest = right;

        if (largest != index)
        {
            std::swap(heap[index], heap[largest]);
            siftdown(heap, largest, heapSize);
        }
    }
};

// 方法三：快排
class Solution3
{
private:
    vector<int> result;

public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> freqMap;
        for (int num : nums)
            freqMap[num]++;
        vector<pair<int, int>> freqVec(freqMap.begin(), freqMap.end());
        quicksort(freqVec, 0, freqVec.size() - 1, k);
        return result;
    }

private:
    void quicksort(vector<pair<int, int>> &freqVec, int left, int right, int k)
    {
        if (left > right)
            return;
        int pivot = partition(freqVec, left, right);
        if (pivot == k - 1)
        {
            for (int i = 0; i <= pivot; i++)
                result.push_back(freqVec[i].first);
            return;
        }
        else if (pivot < k - 1)
            quicksort(freqVec, pivot + 1, right, k);
        else
            quicksort(freqVec, left, pivot - 1, k);
    }

    int partition(vector<pair<int, int>> &freqVec, int left, int right)
    {
        int pivot = freqVec[right].second;
        int i = left - 1;
        for (int j = left; j < right; j++)
        {
            if (freqVec[j].second > pivot)
            {
                i++;
                swap(freqVec[i], freqVec[j]);
            }
        }
        swap(freqVec[i + 1], freqVec[right]);
        return i + 1;
    }
};