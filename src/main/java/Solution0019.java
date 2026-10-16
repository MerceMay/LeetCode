import java.util.*;

//给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

public class Solution0019 {
    public ListNode removeNthFromEnd(ListNode head, int n) {
        ListNode dummy = new ListNode(0, head);
        ListNode fast = head;
        for (int i = 0; i < n; i++) {
            fast = fast.next;
        }
        ListNode slow = dummy;
        while (fast != null) {
            slow = slow.next;
            fast = fast.next;
        }
        slow.next = slow.next.next;
        return dummy.next;
    }
}
