#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
// 假设 力扣（LeetCode）即将开始 IPO 。为了以更高的价格将股票卖给风险投资公司，力扣 希望在 IPO 之前开展一些项目以增加其资本。 由于资源有限，它只能在 IPO 之前完成最多 k 个不同的项目。帮助 力扣 设计完成最多 k 个不同项目后得到最大总资本的方式。

// 给你 n 个项目。对于每个项目 i ，它都有一个纯利润 profits[i] ，和启动该项目需要的最小资本 capital[i] 。

// 最初，你的资本为 w 。当你完成一个项目时，你将获得纯利润，且利润将被添加到你的总资本中。

// 总而言之，从给定项目中选择 最多 k 个不同项目的列表，以 最大化最终资本 ，并输出最终可获得的最多资本。

// 答案保证在 32 位有符号整数范围内。
// 示例 1：

// 输入：k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
// 输出：4
// 解释：
// 由于你的初始资本为 0，你仅可以从 0 号项目开始。
// 在完成后，你将获得 1 的利润，你的总资本将变为 1。
// 此时你可以选择开始 1 号或 2 号项目。
// 由于你最多可以选择两个项目，所以你需要完成 2 号项目以获得最大的资本。
// 因此，输出最后最大化的资本，为 0 + 1 + 3 = 4。
// 示例 2：

// 输入：k = 3, w = 0, profits = [1,2,3], capital = [0,1,2]
// 输出：6
class Solution
{
public:
    // 想法：每次都选择当前资本范围内，利润最大的项目
    // 使用cap记录当前资本
    // 将profits放入大顶堆，一直弹出堆顶，直到cap>=capital[i]，
    // 在vector<bool> done中记录已经完成的项目，然后把弹出来的没有完成的项目放入大顶堆
    int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital)
    {
        int n = profits.size();
        vector<pair<int, int>> cap_pro(n);
        for (int i = 0; i < n; i++)
            cap_pro[i] = {capital[i], profits[i]};
        // 把数组按照资本_利润大小排序，然后放入大根堆，放入的是否判断cap是否小于w，这样堆顶就是利润最大的。
        // 同时，由于w在完成一个项目后会增加，前面的项目已经在w更新前贪心获得了局部最优解，w更多更没必要去做那些项目，
        // 因此，只需要考虑后续项目即可
        sort(cap_pro.begin(), cap_pro.end());
        priority_queue<int> pq;
        int project_index = 0; //
        for (int i = 0; i < k; i++)
        {
            while (project_index < n && cap_pro[project_index].first <= w)
                pq.push(cap_pro[project_index++].second);
            if (pq.empty())
                break;
            w += pq.top();
            pq.pop();
        }
        return w;
    }
};