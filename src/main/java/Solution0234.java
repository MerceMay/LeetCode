import java.beans.PropertyEditorSupport;
import java.util.*;

//给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 。

public class Solution0234 {

    public boolean isPalindrome(ListNode head) {
        ListNode slow = head, fast = head;
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        ListNode temp = reverseList(slow.next);
        ListNode backHead = temp;
        ListNode frontHead = head;
        boolean flag = true;
        while (flag && backHead != null) {
            if (backHead.val != frontHead.val) {
                flag = false;
            }
            backHead = backHead.next;
            frontHead = frontHead.next;
        }
        slow.next = reverseList(temp);
        return flag;
    }

    private ListNode reverseList(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }
        ListNode cur = head, prev = null;
        while (cur != null) {
            ListNode next = cur.next;
            cur.next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }

    private ListNode curLeft;

    public boolean isPalindrome2(ListNode head) {
        curLeft = head;
        return recursiveCheck(head);
    }

    private boolean recursiveCheck(ListNode node) {
        if (node != null) {
            if (!recursiveCheck(node.next)) {
                return false;
            }
            if (node.val != curLeft.val) {
                return false;
            }
            curLeft = curLeft.next;
        }
        return true;
    }
}
