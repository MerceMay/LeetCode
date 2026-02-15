#include <deque>
using namespace std;
// 给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。

// k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

// 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

// 示例 1：

// 输入：head = [1,2,3,4,5], k = 2
// 输出：[2,1,4,3,5]
// 示例 2：

// 输入：head = [1,2,3,4,5], k = 3
// 输出：[3,2,1,4,5]

// 提示：
// 链表中的节点数目为 n
// 1 <= k <= n <= 5000
// 0 <= Node.val <= 1000

// 进阶：你可以设计一个只用 O(1) 额外内存空间的算法解决此问题吗？
// 方法一：栈(队列)
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
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        std::deque<ListNode *> deque;
        ListNode *current = head;
        ListNode *newHead = nullptr, *prev = nullptr;
        int count = 0;
        while (current != nullptr)
        {
            deque.push_back(current);
            current = current->next;
            count++;
            if (count == k)
            {
                while (!deque.empty())
                {
                    ListNode *node = deque.back();
                    deque.pop_back();
                    if (prev != nullptr)
                    {
                        prev->next = node;
                    }
                    else
                    {
                        newHead = node;
                    }
                    prev = node;
                }
                prev->next = nullptr; // 断开连接
                count = 0;
            }
        }
        // 可能存在某位不足k个的情况，这些不需要反转，保持原有顺序。因此，从deque的队前出来
        if (count < k)
        {
            while (!deque.empty())
            {
                ListNode *node = deque.front();
                deque.pop_front();
                if (prev != nullptr)
                {
                    prev->next = node;
                }
                else
                {
                    newHead = node;
                }
                prev = node;
            }
        }
        return newHead;
    }
};

// 方法二：递归
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
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        if (!head)
            return nullptr;
        ListNode *prev = head, *index = head->next;
        int count = 0;
        while (++count < k && index != nullptr)
        {
            prev->next = index->next;
            index->next = head;
            head = index;
            index = prev->next;
        }
        if (count < k)
        {
            // 如果不足，翻转回去
            return reverseKGroup(head, count);
        }
        prev->next = reverseKGroup(index, k);
        return head;
    }
};

// 方法三：递推
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
    ListNode *reverse(ListNode *prev, int k)
    {
        ListNode *current = prev->next;
        int count = 1;
        for (; count < k && current != nullptr && current->next != nullptr; count++)
        {
            ListNode *next = current->next;
            current->next = next->next;
            next->next = prev->next;
            prev->next = next;
        }
        return count == k ? current : nullptr; // 如果不足k个，返回nullptr
    }

    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *dummy = new ListNode(0, head);
        ListNode *prev = dummy;
        while (prev->next != nullptr)
        {
            ListNode *post = reverse(prev, k);
            if (post == nullptr) // 不足k个，翻转回去
            {
                reverse(prev, k);
                break;
            }
            else
            {
                prev = post;
            }
        }
        return dummy->next;
    }
};