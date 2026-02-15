#include <stack>
using namespace std;
// 给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。

// 示例 1：

// 输入：head = [1,2,3,4]
// 输出：[2,1,4,3]
// 示例 2：

// 输入：head = []
// 输出：[]
// 示例 3：

// 输入：head = [1]
// 输出：[1]

// 提示：

// 链表中节点的数目在范围 [0, 100] 内
// 0 <= Node.val <= 100
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
    // 使用递归栈。处理前两个元素后，让栈处理剩下的内容
    ListNode *swapPairs(ListNode *head)
    {
        if (!head || !head->next)
            return head;

        ListNode *newHead = head->next;
        head->next = swapPairs(newHead->next);
        newHead->next = head;

        return newHead;
    }
};

// 递归栈改手动栈。存在问题，难搞
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
    ListNode *swapPairs(ListNode *head)
    {
        if (!head || !head->next)
            return head;
        stack<ListNode *> stack;
        ListNode *current = head;
        ListNode *newHead = nullptr;
        ListNode *prev = nullptr;

        // 将节点压入栈
        while (current != nullptr && current->next != nullptr)
        {
            stack.push(current);
            stack.push(current->next);
            current = current->next->next;
        }
        // 处理剩余的节点
        if (current != nullptr)
        {
            stack.push(current);
        }

        // 从栈中取出并连接
        while (!stack.empty())
        {
            ListNode *node1 = stack.top();
            stack.pop();
            // 非空，形成一对
            if (!stack.empty())
            {
                ListNode *node2 = stack.top();
                stack.pop();
                // 连成一对
                node1->next = node2;
                if (prev != nullptr)
                {
                    prev->next = node1;
                }
                else // 说明这是原链表中最末尾的一对，因此，应该
                {
                    newHead = node1;
                    node2->next = nullptr; // 断开连接
                }
                prev = node2;
            }
            else
            {
                if (prev)
                {
                    prev->next = node1;
                }
                else
                {
                    newHead = node1;
                }
                node1->next = nullptr;
            }
        }
        return newHead;
    }
};

// 方法三，迭代
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
    ListNode *swapPairs(ListNode *head)
    {
        if (!head || !head->next)
            return head;
        ListNode *dummy = new ListNode(0, head);
        ListNode *current = dummy;
        while (current->next && current->next->next)
        {
            ListNode *first = current->next;
            ListNode *second = current->next->next;
            first->next = second->next;
            current->next = second;
            current->next->next = first;
            current = current->next->next;
        }
        return dummy->next;
    }
};