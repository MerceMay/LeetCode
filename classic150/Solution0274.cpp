#include <vector>
#include <algorithm>
using namespace std;
// 给你一个整数数组 citations ，其中 citations[i] 表示研究者的第 i 篇论文被引用的次数。计算并返回该研究者的 h 指数。

// 根据维基百科上 h 指数的定义：h 代表“高引用次数” ，一名科研人员的 h 指数 是指他（她）至少发表了 h 篇论文，并且 至少 有 h 篇论文被引用次数大于等于 h 。如果 h 有多种可能的值，h 指数 是其中最大的那个。
// 方法一：排序
class Solution
{
public:
    int hIndex(vector<int> &citations)
    {
        sort(citations.begin(), citations.end(), greater<int>());
        for (int i = 0; i < citations.size(); i++)
        {
            if (citations[i] < i + 1) // 第i+1篇论文的引用次数小于i+1，说明h指数为i
                return i;
        }
        return citations.size();
    }
};
// 方法二：计数排序
class Solution2
{
public:
    int hIndex(vector<int> &citations)
    {
        // h最大只可能是citations.size()
        vector<int> count(citations.size() + 1, 0);
        for (int i = 0; i < citations.size(); i++)
        {
            if (citations[i] >= citations.size()) // 如果引用次数大于等于h的最大值，计入最后一个位置
                count[citations.size()]++;
            else
                count[citations[i]]++;
        }
        int total = 0;
        for (int h = citations.size(); h >= 0; h--) // h从后往前遍历，依次减小
        {
            total += count[h]; // 统计总数
            if (total >= h)    // 如果总数大于等于h，说明找到了合适的h值
                return h;
        }
        return 0;
    }
};