#include <iostream>
using namespace std;
// 给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。

// 示例 1：

// 输入：head = [1,2,3,4,5]
// 输出：[5,4,3,2,1]
// 示例 2：

// 输入：head = [1,2]
// 输出：[2,1]
// 示例 3：

// 输入：head = []
// 输出：[]

// 提示：

// 链表中节点的数目范围是 [0, 5000]
// -5000 <= Node.val <= 5000

// 进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
// 方法一：使用三指针
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
    ListNode *reverseList(ListNode *head)
    {
        ListNode *current = head, *previous = nullptr, *nextNode = nullptr;
        while (current)
        {
            nextNode = current->next; // 保存下一个节点
            current->next = previous; // 反转当前节点的指针
            previous = current;       // 移动前一个节点指针
            current = nextNode;       // 移动到下一个节点
        }
        return previous;
    }
};

// 方法二：使用递归。时间复杂度都是O(n),空间复杂度为O(n)。上一种为O(1)
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
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
        {
            return head; // 返回原链表的末尾节点
        }
        ListNode *newHead = reverseList(head->next); // 递归到最后一个节点
        head->next->next = head;
        head->next = nullptr; // 断开原来的链接
        return newHead; // 永远返回原链表的末尾节点
    }
};
