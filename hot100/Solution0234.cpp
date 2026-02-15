using namespace std;
// 给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 。

// 示例 1：

// 输入：head = [1,2,2,1]
// 输出：true
// 示例 2：

// 输入：head = [1,2]
// 输出：false

// 提示：

// 链表中节点数目在范围[1, 105] 内
// 0 <= Node.val <= 9

// 进阶：你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？
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

    ListNode *reverseList(ListNode *head)
    {
        ListNode *prev = nullptr;
        ListNode *curr = head;
        while (curr)
        {
            ListNode *next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

public:
    bool isPalindrome(ListNode *head)
    {
        if (!head || !head->next)
            return true; // 空链表或单节点链表是回文
        ListNode *slow_pointer = head, *fast_pointer = head;
        while (fast_pointer->next && fast_pointer->next->next)
        {
            fast_pointer = fast_pointer->next->next;
            slow_pointer = slow_pointer->next;
        }
        // 如果链表长度是奇数，slow_pointer是中间节点，fast_pointer是最后一个节点
        // 如果链表长度是偶数，slow_pointer是前半部分最后一个节点，fast_pointer是倒数第二个节点
        // 因此无论是奇数还是偶数，slow_pointer的下一个节点就是后半部分的第一个节点
        ListNode *secondHalf = reverseList(slow_pointer->next);
        ListNode *secondHalfHead = secondHalf; // 保存用于恢复

        bool result = true;
        ListNode *firstHalf = head;
        while (secondHalf)
        {
            if (firstHalf->val != secondHalf->val)
            {
                result = false;
                break;
            }
            firstHalf = firstHalf->next;
            secondHalf = secondHalf->next;
        }
        slow_pointer->next = reverseList(secondHalfHead); // 恢复链表
        return result;
    }
};

// 方法二：递归。空间复杂度为O(n)
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
    ListNode *front_pointer;

    bool recursivelyCheck(ListNode *current)
    {
        if (current)
        {
            if (!recursivelyCheck(current->next))
            {
                return false;
            }
            if (current->val != front_pointer->val)
            {
                return false;
            }
            front_pointer = front_pointer->next;
        }
        return true;
    }

public:
    bool isPalindrome(ListNode *head)
    {
        front_pointer = head;
        return recursivelyCheck(head);
    }
};