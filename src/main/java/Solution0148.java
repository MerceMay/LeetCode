import java.util.*;

//给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

public class Solution0148 {

    public static ListNode sortList(ListNode head) {
        return sortList(head, null);
    }

    private static ListNode sortList(ListNode head, ListNode tail) { // [head, tail)
        if (head == null) {
            return head;
        }
        if (head.next == tail) {
            head.next = null;
            return head;
        }

        ListNode slow = head, fast = head;
        while (fast != tail && fast.next != tail) {
            slow = slow.next;
            fast = fast.next.next;
        }
        ListNode list1 = sortList(head, slow);
        ListNode list2 = sortList(slow, tail);
        return merge(list1, list2);
    }

    private static ListNode merge(ListNode list1, ListNode list2) {
        ListNode dummy = new ListNode(0);
        ListNode cur = dummy;
        ListNode p1 = list1, p2 = list2;
        while (p1 != null && p2 != null) {
            if (p1.val < p2.val) {
                cur.next = p1;
                p1 = p1.next;
            } else {
                cur.next = p2;
                p2 = p2.next;
            }
            cur = cur.next;
        }
        cur.next = p1 == null ? p2 : p1;
        return dummy.next;
    }

    public static ListNode sortList2(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }
        int length = 0;
        ListNode cur = head;
        while (cur != null) {
            length++;
            cur = cur.next;
        }

        ListNode dummy = new ListNode(0);
        dummy.next = head;
        for (int subLen = 1; subLen < length; subLen <<= 1) {
            ListNode tail = dummy;
            cur = tail.next;
            while (cur != null) {
                ListNode list1 = cur;
                for (int i = 1; i < subLen && cur.next != null; i++) {
                    cur = cur.next;
                }
                ListNode list2 = cur.next;
                cur.next = null;
                cur = list2; // list1刚好吃完，list2可能为null
                for (int i = 1; i < subLen && cur!=null && cur.next != null; i++) {
                    cur = cur.next;
                }
                ListNode next = null;
                if (cur != null) {
                    next = cur.next;
                    cur.next = null;
                }
                ListNode merged = merge(list1, list2);
                tail.next = merged;
                while (tail.next != null) {
                    tail = tail.next;
                }
                cur = next;
            }
        }
        return dummy.next;
    }
}
