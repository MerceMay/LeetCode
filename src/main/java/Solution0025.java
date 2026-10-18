import java.util.*;

//给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
//
//k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
//
//你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

public class Solution0025 {
    public ListNode reverseKGroup(ListNode head, int k) {
        if (head == null) {
            return null;
        }
        ListNode oldHead = head, cur = head.next;
        int count = 1;
        while (count < k && cur != null) {
            ListNode next = cur.next;
            oldHead.next = next;
            cur.next = head;
            head = cur;
            cur = next;
            count++;
        }
        if (count < k) {
            return reverseKGroup(head, count);
        }
        oldHead.next = reverseKGroup(cur, k);
        return head;
    }
}
