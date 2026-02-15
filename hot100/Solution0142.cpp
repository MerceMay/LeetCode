using namespace std;
// 给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

// 如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。

// 不允许修改 链表。

// 示例 1：

// 输入：head = [3,2,0,-4], pos = 1
// 输出：返回索引为 1 的链表节点
// 解释：链表中有一个环，其尾部连接到第二个节点。
// 示例 2：

// 输入：head = [1,2], pos = 0
// 输出：返回索引为 0 的链表节点
// 解释：链表中有一个环，其尾部连接到第一个节点。
// 示例 3：

// 输入：head = [1], pos = -1
// 输出：返回 null
// 解释：链表中没有环。

// 提示：

// 链表中节点的数目范围在范围 [0, 104] 内
// -105 <= Node.val <= 105
// pos 的值为 -1 或者链表中的一个有效索引

// 进阶：你是否可以使用 O(1) 空间解决此题？
class Solution
{
private:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

public:
    // 记链头到入点长度为a，慢指针在圈内走过的距离为b，一个圈的大小为c
    // a + b + k*c = 2(a+b)
    // a = k*c - b = (k-1)*c + c-b
    // 因此，如果相遇了，从头开始走一个慢指针，相遇点再走c-b的距离，最终在入点相遇
    ListNode *detectCycle(ListNode *head)
    {
        if (!head || !head->next)
            return nullptr;
        // 使用快慢指针
        ListNode *slow = head, *fast = head;
        while (fast->next && fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
            {
                // 找到环的入口
                ListNode *entry = head;
                while (entry != slow)
                {
                    entry = entry->next;
                    slow = slow->next;
                }
                return entry;
            }
        }
        return nullptr;
    }
};