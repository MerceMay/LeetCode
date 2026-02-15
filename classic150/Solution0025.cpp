#include <deque>
using namespace std;
// 给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。

// k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

// 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

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
        if (!head)
            return nullptr;
        ListNode *prev = head, *next = head->next;
        int count = 0;
        while (++count < k && next != nullptr) // 翻转k-1次
        {
            prev->next = next->next;
            next->next = head;
            head = next;
            next = prev->next;
        }
        if (count < k)
        {
            return reverseKGroup(head, count); // 如果不足k个，翻转回去
        }
        prev->next = reverseKGroup(next, k);
        return head;
    }
};

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
    deque<ListNode *> deque;

public:
    ListNode *reverseKGroup(ListNode *head, int k)
    {
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
                    if (prev == nullptr)
                    {
                        newHead = node;
                    }
                    else
                    {
                        prev->next = node;
                    }
                    prev = node;
                }
                prev->next = nullptr;
                count = 0;
            }
        }
        if (count < k)
        {
            while (!deque.empty())
            {
                ListNode *node = deque.front();
                deque.pop_front();
                if (prev == nullptr)
                {
                    newHead = node;
                }
                else
                {
                    prev->next = node;
                }
                prev = node;
            }
        }
        return newHead;
    }
};

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
        ListNode *dummy = new ListNode(0, head);
        ListNode *prev = dummy;// prev是前一个k组的尾节点
        while (prev->next)
        {
            ListNode *node = reverse(prev, k);
            if (node == nullptr)
            {
                reverse(prev, k); // 不足k个，翻转回去
                break;
            }
            else
            {
                prev = node;
            }
        }
        return dummy->next;
    }

private:
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
        return (count == k) ? current : nullptr;
    }
};