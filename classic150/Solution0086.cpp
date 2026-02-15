using namespace std;
// 给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。

// 你应当 保留 两个分区中每个节点的初始相对位置。

// 示例 1：

// 输入：head = [1,4,3,2,5,2], x = 3
// 输出：[1,2,2,4,3,5]
// 示例 2：

// 输入：head = [2,1], x = 2
// 输出：[1,2]

// 提示：

// 链表中节点的数目在范围 [0, 200] 内
// -100 <= Node.val <= 100
// -200 <= x <= 200
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
    // 创建两个链表，分别是小于和大于等于的，最后把两个链表的尾部处理好后，连接起来
    ListNode *partition(ListNode *head, int x)
    {
        ListNode *lessHead = new ListNode(0);
        ListNode *greaterHead = new ListNode(0);
        ListNode *lessTail = lessHead;
        ListNode *greaterTail = greaterHead;
        ListNode* current = head;
        while (current)
        {
            if (current->val < x)
            {
                lessTail->next = current;
                lessTail = lessTail->next;
            }
            else
            {
                greaterTail->next = current;
                greaterTail = greaterTail->next;
            }
            current = current->next;
        }
        greaterTail->next = nullptr; // Important: avoid cycle in linked list
        lessTail->next = greaterHead->next;
        return lessHead->next;
    }
};