#include <vector>
#include <queue>
#include <functional>
using namespace std;
// 给定两个以 非递减顺序排列 的整数数组 nums1 和 nums2 , 以及一个整数 k 。

// 定义一对值 (u,v)，其中第一个元素来自 nums1，第二个元素来自 nums2 。

// 请找到和最小的 k 个数对 (u1,v1),  (u2,v2)  ...  (uk,vk) 。
class Solution
{
public:
    vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k)
    {
        int n1 = nums1.size();
        int n2 = nums2.size();
        vector<vector<int>> res;
        auto cmp = [&](const tuple<int, int, int> &a, const tuple<int, int, int> &b)
        {
            return get<0>(a) > get<0>(b);
        };
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(cmp)> pq(cmp);
        for (int i = 0; i < n1 && i < k; i++)
            pq.push({nums1[i] + nums2[0], i, 0}); // 把[1,0],[2,0],[3,0]放入堆中
        while (k-- > 0 && !pq.empty())
        {
            auto [sum, i, j] = pq.top();
            pq.pop();
            res.push_back({nums1[i], nums2[j]});
            if (j + 1 < n2) // 把(i, j+1)放入堆中
                pq.push({nums1[i] + nums2[j + 1], i, j + 1});
        }
        return res;
    }
};

class Solution
{
public:
    vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k)
    {
        int n1 = nums1.size();
        int n2 = nums2.size();

        auto count = [&](int x)
        {
            long long cnt = 0;
            int point_1 = 0, point_2 = n2 - 1;
            while (point_1 < n1 && point_2 >= 0)
            {
                if (nums1[point_1] + nums2[point_2] <= x) // 如果满足条件，则nums1[point_1] + nums2[0...point_2]都满足条件
                {
                    cnt += point_2 + 1; // nums2中前point_2+1个元素都满足条件
                    point_1++;          // point_1右移
                }
                else
                    point_2--; // nums[point_2]太大，point_2左移
            }
            return cnt;
        };

        // 找到第k小的和
        int left = nums1[0] + nums2[0], right = nums1[n1 - 1] + nums2[n2 - 1];
        int kth_sum = right;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (count(mid) >= k) // mid太大，右边界左移
            {
                kth_sum = mid;
                right = mid - 1;
            }
            else
                left = mid + 1; // mid太小，左边界右移
        }

        vector<vector<int>> res;
        // 找到所有小于kth_sum的数对
        int point_1 = 0, point_2 = n2 - 1;
        while (point_1 < n1 && point_2 >= 0)
        {
            if (nums1[point_1] + nums2[point_2] < kth_sum) // 如果满足条件，则nums1[point_1] + nums2[0...point_2]都满足条件
            {
                for (int j = 0; j <= point_2; j++)
                {
                    res.push_back({nums1[point_1], nums2[j]});
                    if (res.size() == k)
                        return res;
                }
                point_1++; // point_1右移
            }
            else
                point_2--; // nums[point_2]太大，point_2左移
        }

        // 找到所有等于kth_sum的数对
        int point_2 = n2 - 1;
        for (int point_1 = 0; point_1 < n1 && k > 0; point_1++)
        {
            int start1 = point_1;
            while (point_1 < n2 - 1 && nums1[point_1] == nums1[point_1 + 1])
            {
                point_1++;
            }
            while (point_2 >= 0 && nums1[point_1] + nums2[point_2] > kth_sum)
            {
                point_2--;
            }
            if (nums1[point_1] + nums2[point_2] != kth_sum)
            {
                continue;
            }
            int start2 = point_2;
            while (point_2 > 0 && nums2[point_2] == nums2[point_2 - 1])
            {
                point_2--;
            }
            int count = (int)min((long)k, (long)(point_1 - start1 + 1) * (start2 - point_2 + 1));
            for (int j = 0; j < count && k > 0; j++, k--)
            {
                res.push_back({nums1[point_1], nums2[point_2]});
            }
        }
        return res;
    }
};