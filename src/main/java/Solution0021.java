import java.util.*;

//将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

public class Solution0021 {

    public ListNode mergeTwoLists(ListNode list1, ListNode list2) {
        ListNode dummy = new ListNode();
        ListNode p1 = list1, p2 = list2;
        ListNode cur = dummy;
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

    public ListNode mergeTwoLists2(ListNode list1, ListNode list2) {
        if (list1 == null) {
            return list2;
        }
        if (list2 == null) {
            return list1;
        }
        ListNode cur;
        if (list1.val < list2.val) {
            cur = list1;
            cur.next = mergeTwoLists2(list1.next, list2);
        } else {
            cur = list2;
            cur.next = mergeTwoLists2(list1, list2.next);
        }
        return cur;
    }
}
