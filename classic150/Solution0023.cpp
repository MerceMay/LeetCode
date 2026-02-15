#include <vector>
#include <queue>
using namespace std;
// 给你一个链表数组，每个链表都已经按升序排列。

// 请你将所有链表合并到一个升序链表中，返回合并后的链表。

// 示例 1：

// 输入：lists = [[1,4,5],[1,3,4],[2,6]]
// 输出：[1,1,2,3,4,4,5,6]
// 解释：链表数组如下：
// [
//   1->4->5,
//   1->3->4,
//   2->6
// ]
// 将它们合并到一个有序链表中得到。
// 1->1->2->3->4->4->5->6
// 示例 2：

// 输入：lists = []
// 输出：[]
// 示例 3：

// 输入：lists = [[]]
// 输出：[]

// 提示：

// k == lists.length
// 0 <= k <= 10^4
// 0 <= lists[i].length <= 500
// -10^4 <= lists[i][j] <= 10^4
// lists[i] 按 升序 排列
// lists[i].length 的总和不超过 10^4

// 方法一：顺序合并：ans = merge(ans, lists[i])
// 方法二：分治合并：两两合并
class Solution
{
private:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        if (lists.empty())
            return nullptr;
        return helper(lists, 0, lists.size() - 1);
    }

private:
    ListNode *helper(vector<ListNode *> &lists, int left, int right)
    {
        if (left > right)
        {
            return nullptr;
        }
        if (left == right)
        {
            return lists[left];
        }
        int mid = left + (right - left) / 2;
        ListNode *l1 = helper(lists, left, mid);
        ListNode *l2 = helper(lists, mid + 1, right);
        return merge(l1, l2);
    }

private:
    ListNode *merge(ListNode *l1, ListNode *l2)
    {
        ListNode *dummy = new ListNode();
        ListNode *tail = dummy;
        while (l1 != nullptr && l2 != nullptr)
        {
            if (l1->val < l2->val)
            {
                tail->next = l1;
                l1 = l1->next;
            }
            else
            {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = (l1 != nullptr) ? l1 : l2;
        ListNode *temp = dummy;
        dummy = dummy->next;
        delete temp;
        return dummy;
    }
};

// 方法三：优先队列
class Solution2
{
private:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        auto cmp = [](ListNode *a, ListNode *b) { return a->val > b->val; };
        priority_queue<ListNode *, vector<ListNode *>, decltype(cmp)> pq(cmp); // 小顶堆
        for (auto list : lists)
            if (list != nullptr)
                pq.push(list);

        ListNode *dummy = new ListNode();
        ListNode *tail = dummy;
        while (!pq.empty())
        {
            ListNode *node = pq.top();
            pq.pop();
            tail->next = node;
            tail = tail->next;
            if (node->next != nullptr)
            {
                pq.push(node->next);
            }
        }
        ListNode *temp = dummy;
        dummy = dummy->next;
        delete temp;
        return dummy;
    }
};
