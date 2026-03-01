package anew;

import java.util.Stack;

// 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

public class Solution0019 {
    private static class ListNode {
        int val;
        ListNode next;

        public ListNode(int x) {
            val = x;
            next = null;
        }
    }

    public ListNode removeNthFromEnd(ListNode head, int n) {
        ListNode slow = head;
        ListNode fast = head;
        for (int i = 0; i < n; i++) {
            fast = fast.next;
        }
        if (fast == null) {
            return head.next;
        }
        while (fast.next != null) {
            slow = slow.next;
            fast = fast.next;
        }
        slow.next = slow.next.next;
        return head;
    }

    public ListNode removeNthFromEnd2(ListNode head, int n) {
        Stack<ListNode> stack = new Stack<>();
        ListNode current = head;
        while (current != null) {
            stack.push(current);
            current = current.next;
        }
        for (int i = 0; i < n; i++) {
            stack.pop();
        }
        if (stack.isEmpty()) {
            return head.next;
        }
        ListNode prev = stack.peek();
        prev.next = prev.next.next;
        return head;
    }

    public static void main(String[] args) {
        Solution0019 solution = new Solution0019();
        ListNode head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);

        int n = 2;
        ListNode result = solution.removeNthFromEnd(head, n);
        System.out.print("删除倒数第 " + n + " 个节点后的链表: ");
        while (result != null) {
            System.out.print(result.val + " ");
            result = result.next;
        }
    }
}
