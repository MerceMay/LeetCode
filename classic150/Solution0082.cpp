using namespace std;
// 给定一个已排序的链表的头 head ， 删除原始链表中所有重复数字的节点，只留下不同的数字 。返回 已排序的链表 。

// 示例 1：

// 输入：head = [1,2,3,3,4,4,5]
// 输出：[1,2,5]
// 示例 2：

// 输入：head = [1,1,1,2,3]
// 输出：[2,3]

// 提示：

// 链表中节点数目在范围 [0, 300] 内
// -100 <= Node.val <= 100
// 题目数据保证链表已经按升序 排列
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
    ListNode *deleteDuplicates(ListNode *head)
    {
        if (!head)
            return nullptr;
        ListNode *dummy = new ListNode(0, head);
        ListNode *cur = dummy;
        while (cur->next != nullptr && cur->next->next != nullptr)
        {
            if (cur->next->val == cur->next->next->val)
            {
                ListNode *next = cur->next;
                int nextVal = cur->next->val;
                while (next != nullptr && next->val == nextVal)
                {
                    ListNode *temp = next;
                    next = next->next;
                    delete temp;
                }
                cur->next = next;
            }
            else
            {
                cur = cur->next;
            }
        }
        return dummy->next;
    }
};