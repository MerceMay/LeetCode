#include <stack>
using namespace std;
// 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

// 示例 1：

// 输入：head = [1,2,3,4,5], n = 2
// 输出：[1,2,3,5]
// 示例 2：

// 输入：head = [1], n = 1
// 输出：[]
// 示例 3：

// 输入：head = [1,2], n = 1
// 输出：[1]

// 提示：

// 链表中结点的数目为 sz
// 1 <= sz <= 30
// 0 <= Node.val <= 100
// 1 <= n <= sz

// 进阶：你能尝试使用一趟扫描实现吗？
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
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        // 快慢指针：快指针先走n步。如果第n步时，fast_pointer.next == nullptr，说明删除的是头节点，返回head.next即可
        ListNode *fast_pointer = head, *slow_pointer = head;
        for (int i = 0; i < n; ++i)
        {
            fast_pointer = fast_pointer->next;
        }
        if (!fast_pointer)
            return head->next;
        while (fast_pointer->next != nullptr)
        {
            fast_pointer = fast_pointer->next;
            slow_pointer = slow_pointer->next;
        }
        slow_pointer->next = slow_pointer->next->next;
        return head;
    }
};

// 方法二：栈
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
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        stack<ListNode *> nodeStack;
        ListNode *dummy = new ListNode(0, head);
        ListNode *current = dummy;
        while (current != nullptr)
        {
            nodeStack.push(current);
            current = current->next;
        }
        for (int i = 0; i < n; ++i)
        {
            nodeStack.pop();
        }
        ListNode *prev = nodeStack.top();
        ListNode *toDelete = prev->next;
        prev->next = toDelete->next;
        delete toDelete;
        return dummy->next;
    }
};