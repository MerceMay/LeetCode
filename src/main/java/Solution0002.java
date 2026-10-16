import java.util.*;

//给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
//
//请你将两个数相加，并以相同形式返回一个表示和的链表。
//
//你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

public class Solution0002 {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode();
        ListNode p1 = l1, p2 = l2;
        int rest = 0;
        ListNode cur = dummy;
        while (p1 != null || p2 != null) {
            int num1 = p1 == null ? 0 : p1.val;
            int num2 = p2 == null ? 0 : p2.val;
            int sum = num1 + num2 + rest;
            rest = sum / 10;
            cur.next = new ListNode(sum % 10);
            cur = cur.next;
            if (p1 != null) {
                p1 = p1.next;
            }
            if (p2 != null) {
                p2 = p2.next;
            }
        }
        if (rest > 0) {
            cur.next = new ListNode(rest);
        }
        return dummy.next;
    }
}
