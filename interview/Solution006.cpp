// 删除单向链表中的重复节点（注意，不是去重，而是删除所有重复节点）
#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        if (!head || !head->next)
        {
            return head;
        }
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *prev = dummy, *curr = head;
        while (curr)
        {
            while (curr->next && curr->val == curr->next->val)
            {
                curr = curr->next;
            }
            if (prev->next == curr)
            {
                prev = prev->next;
            }
            else
            {
                prev->next = curr->next;
            }
            curr = curr->next;
        }
        return dummy->next;
    }
};

int main()
{
    Solution s;
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(3);
    head->next->next->next->next = new ListNode(4);
    head->next->next->next->next->next = new ListNode(4);
    head->next->next->next->next->next->next = new ListNode(5);
    ListNode *res = s.deleteDuplicates(head);
    while (res)
    {
        cout << res->val << " ";
        res = res->next;
    }
    cout << endl;
    return 0;
}