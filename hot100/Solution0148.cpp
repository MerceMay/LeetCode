#include <queue>
#include <algorithm>
using namespace std;
// 给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

// 示例 1：

// 输入：head = [4,2,1,3]
// 输出：[1,2,3,4]
// 示例 2：

// 输入：head = [-1,5,3,4,0]
// 输出：[-1,0,3,4,5]
// 示例 3：

// 输入：head = []
// 输出：[]

// 提示：

// 链表中节点的数目在范围 [0, 5 * 104] 内
// -105 <= Node.val <= 105

// 进阶：你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？
// 方法一：小根堆，优先级队列
class Solution
{
private:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

public:
    ListNode *sortList(ListNode *head)
    {
        auto cmp = [](ListNode *a, ListNode *b)
        {
            return a->val > b->val;
        };
        priority_queue<ListNode *, vector<ListNode *>, decltype(cmp)> pq(cmp);
        for (ListNode *cur = head; cur != nullptr; cur = cur->next)
        {
            pq.push(cur);
        }
        ListNode *dummy = new ListNode(0);
        ListNode *tail = dummy;
        while (!pq.empty())
        {
            tail->next = pq.top();
            pq.pop();
            tail = tail->next;
        }
        tail->next = nullptr;
        return dummy->next;
    }
};

// 方法二：自顶向下的归并，空间复杂度是o(log n)
class Solution2
{
private:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

public:
    ListNode *sortList(ListNode *head)
    {
        return sort(head, nullptr);
    }

private:
    // 处理[head,tail)区间
    ListNode *sort(ListNode *head, ListNode *tail)
    {
        if (!head)
            return nullptr;
        if (head->next == tail)
        {
            head->next = nullptr;
            return head;
        }
        ListNode *slow = head, *fast = head;
        while (fast != tail && fast->next != tail)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *mid = slow;
        return merge(sort(head, mid), sort(mid, tail));
    }
    ListNode *merge(ListNode *head1, ListNode *head2)
    {
        ListNode *dummy_head = new ListNode(0);
        ListNode *dummy_tail = dummy_head;
        ListNode *pointer1 = head1, *pointer2 = head2;
        while (pointer1 != nullptr && pointer2 != nullptr)
        {
            if (pointer1->val > pointer2->val)
            {
                dummy_tail->next = pointer2;
                pointer2 = pointer2->next;
            }
            else
            {
                dummy_tail->next = pointer1;
                pointer1 = pointer1->next;
            }
            dummy_tail = dummy_tail->next;
        }
        dummy_tail->next = pointer1 != nullptr ? pointer1 : pointer2;
        return dummy_head->next;
    }
};

// 方法三：自底向上的归并，空间复杂度是O(1)
class Solution3
{
private:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

public:
    ListNode *sortList(ListNode *head)
    {
        if (!head || !head->next)
        {
            return head;
        }
        int length = 0;
        for (ListNode *i = head; head != nullptr; i = i->next)
        {
            length++;
        }
        ListNode *dummy = new ListNode(0, head);
        for (int size = 1; size < length; size *= 2)
        {
            ListNode *prev = dummy;       // 已经排好序的链表的末尾
            ListNode *curr = dummy->next; // 需要排序的链表的开头
            while (curr != nullptr)
            {
                ListNode *left = curr;
                ListNode *right = split(curr, size);
                curr = split(right, size);
                ListNode *mergerd = merge(left, right); // 归并后的链表的链头
                prev->next = mergerd;
                // 一直把prev移动到归并后的链表的链尾
                while (prev->next != nullptr)
                {
                    prev = prev->next;
                }
            }
        }
    }

private:
    // 返回开头过size后，截断，给出第二个链表的开头
    ListNode *split(ListNode *head, int size)
    {
        if (!head)
            return nullptr;
        ListNode *current = head;
        for (int i = 1; i < size && current != nullptr; i++)
        {
            current = current->next;
        }
        // 说明当前链条的长度小于size
        if (current == nullptr)
        {
            return nullptr;
        }
        ListNode *next_list_head = current->next;
        current->next = nullptr; // 断开链接
        return next_list_head;
    }
    // 两个链表，归并
    ListNode *merge(ListNode *left, ListNode *right)
    {
        ListNode *dummy = new ListNode(0);
        ListNode *prev = dummy;
        ListNode *pointer1 = left, *pointer2 = right;
        while (pointer1 != nullptr && pointer2 != nullptr)
        {
            if (pointer1->val > pointer2->val)
            {
                prev->next = pointer2;
                pointer2 = pointer2->next;
            }
            else
            {
                prev->next = pointer1;
                pointer1 = pointer1->next;
            }
            prev = prev->next;
        }
        prev->next = (pointer1 != nullptr) ? pointer1 : pointer2;
        return dummy->next;
    }
};
