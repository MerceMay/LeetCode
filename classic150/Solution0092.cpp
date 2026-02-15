using namespace std;
// 给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。

// 示例 1：

// 输入：head = [1,2,3,4,5], left = 2, right = 4
// 输出：[1,4,3,2,5]
// 示例 2：

// 输入：head = [5], left = 1, right = 1
// 输出：[5]

// 提示：

// 链表中节点数目为 n
// 1 <= n <= 500
// -500 <= Node.val <= 500
// 1 <= left <= right <= n

// 进阶： 你可以使用一趟扫描完成反转吗？
// 普通方法，找到left和right两侧，然后翻转left到right，再连接
// 进阶方法：使用pre记录left-1，然后依次遍历，反转链表，每次遍历都使得pre指向当前节点，直到遍历到right
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
    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;
        ListNode *pre = dummy; // 使用dummy防止head在left中

        // 移动pre到left-1
        for (int i = 0; i < left - 1; i++)
            pre = pre->next;

        ListNode *cur = pre->next; // cur为left
        ListNode *next = nullptr;

        // 将cur从left移动到right，现在是left，移动right - left到right
        // cur一直是翻转好的区间中的右端点，
        // next每次翻转是，变成pre的下一个（pre是不动的）
        for (int i = 0; i < right - left; i++)
        {
            next = cur->next;
            cur->next = next->next; // next在这轮要到最左边去，因此，要保存好cur->为next的下一个
            next->next = pre->next; // 将next插进pre之后
            pre->next = next;
        }
        return dummy->next;
    }
};