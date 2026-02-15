using namespace std;
// 给你一个链表的头节点 head ，旋转链表，将链表每个节点向右移动 k 个位置。

// 示例 1：

// 输入：head = [1,2,3,4,5], k = 2
// 输出：[4,5,1,2,3]
// 示例 2：

// 输入：head = [0,1,2], k = 4
// 输出：[2,0,1]

// 提示：

// 链表中节点的数目在范围 [0, 500] 内
// -100 <= Node.val <= 100
// 0 <= k <= 2 * 109
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
    // 本质就是将倒数k个节点移动到链表的头部
    ListNode *rotateRight(ListNode *head, int k)
    {
        if (!head || k == 0)
            return head;

        // 计算链表长度
        ListNode *current = head;
        int len = 1;
        while (current->next != nullptr)
        {
            current = current->next;
            len++;
        }

        k = k % len;
        int step = len - k;
        current->next = head; // 形成环
        ListNode *newTail = current;
        while (step > 0)
        {
            newTail = newTail->next;
            step--;
        }
        // 断开环
        ListNode *newHead = newTail->next;
        newTail->next = nullptr;
        return newHead;
    }
};