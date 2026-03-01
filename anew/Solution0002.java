package anew;

// 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。

// 请你将两个数相加，并以相同形式返回一个表示和的链表。

// 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

public class Solution0002 {
    private static class ListNode {
        int val;
        ListNode next;

        public ListNode(int x) {
            val = x;
            next = null;
        }
    }

    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode(0);
        ListNode p1 = l1, p2 = l2, current = dummy;
        int carry = 0;
        while (p1 != null || p2 != null || carry != 0) {
            int x = (p1 == null) ? 0 : p1.val;
            int y = (p2 == null) ? 0 : p2.val;
            int sum = carry + x + y;
            current.next = new ListNode(sum % 10);
            carry = sum / 10;
            current = current.next;
            if (p1 != null) {
                p1 = p1.next;
            }
            if (p2 != null) {
                p2 = p2.next;
            }
        }
        return dummy.next;
    }

    public static void main(String[] args) {
        Solution0002 solution = new Solution0002();
        ListNode l1 = new ListNode(2);
        l1.next = new ListNode(4);
        l1.next.next = new ListNode(3);

        ListNode l2 = new ListNode(5);
        l2.next = new ListNode(6);
        l2.next.next = new ListNode(4);

        ListNode result = solution.addTwoNumbers(l1, l2);
        System.out.print("相加后的链表: ");
        while (result != null) {
            System.out.print(result.val + " ");
            result = result.next;
        }
    }
}
