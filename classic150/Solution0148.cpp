#include <queue>
#include <functional>
using namespace std;
// 给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。
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
    ListNode *sortList(ListNode *head)
    {
        priority_queue<ListNode *, vector<ListNode *>, function<bool(ListNode *, ListNode *)>> pq([](ListNode *a, ListNode *b)
                                                                                                  { return a->val > b->val; });
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
    ListNode *sortList(ListNode *head)
    {
        return sortListHelper(head, nullptr);
    }

private:
    ListNode *sortListHelper(ListNode *head, ListNode *nextHead)
    {
        if (head == nullptr)
            return nullptr;
        if (head->next == nextHead)
        {
            head->next = nullptr;
            return head;
        }
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast != nextHead && fast->next != nextHead)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *mid = slow;
        return merge(sortListHelper(head, mid), sortListHelper(mid, nextHead));
    }

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
    ListNode *sortList(ListNode *head)
    {
        if (!head)
            return nullptr;
        int length = 0;
        ListNode *current = head;
        while (current)
        {
            length++;
            current = current->next;
        }
        ListNode *dummy = new ListNode(0, head);
        for (int size = 1; size < length; size *= 2)
        {
            ListNode *prev = dummy;      // 已经排好序的链表的尾部
            ListNode *cur = dummy->next; // 待排序的链表头部
            while (cur)                  // 遍历链表
            {
                ListNode *left = cur;
                for (int i = 1; i < size && cur->next; i++)
                    cur = cur->next;         // 找到left的尾部
                ListNode *right = cur->next; // left尾部下一个就是right
                cur->next = nullptr;         // 断开left尾部
                cur = right;
                for (int i = 1; i < size && cur && cur->next; i++)
                    cur = cur->next;
                ListNode *next = nullptr; // 用来记录排序left和right后的下一个待排序头部
                if (cur)                  // 如果遍历到right的尾部还没有出链表
                {
                    next = cur->next;    // 记录下一次的开始
                    cur->next = nullptr; // 断开right的尾部
                }
                ListNode *merged = merge(left, right);
                prev->next = merged; // 把之前的连上left和right排序好的
                while (prev->next)
                    prev = prev->next;
                cur = next;
            }
        }
        ListNode* temp = dummy;
        dummy = dummy->next;
        delete temp;
        return dummy;
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