package hot100;

import java.util.Deque;
import java.util.ArrayDeque;

// 给你链表的头节点 head，每 k 个节点一组进行翻转，请你返回修改后的链表。

// k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

// 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

public class Solution0025 {
    private static class ListNode {
        int val;
        ListNode next;

        ListNode(int x) {
            val = x;
            next = null;
        }
    }

    public ListNode reverseKGroup(ListNode head, int k) {
        Deque<ListNode> stack = new ArrayDeque<>();
        ListNode dummy = new ListNode(0);
        ListNode current = dummy;
        ListNode node = head;

        while (node != null) {
            int count = 0;
            while (node != null && count < k) {
                stack.push(node);
                node = node.next;
                count++;
            }
            if (count == k) {
                while (!stack.isEmpty()) {
                    current.next = stack.pop();
                    current = current.next;
                }
            } else {
                while (!stack.isEmpty()) {
                    current.next = stack.removeLast(); // 保持剩余节点的顺序
                    current = current.next;
                }
                current.next = null; // 连接剩余部分
            }
        }
        return dummy.next;
    }

    public ListNode reverseKGroup2(ListNode head, int k) {
        if (head == null) {
            return null;
        }
        ListNode current = head;
        ListNode next = head.next;
        int count = 0;
        while (++count < k && next != null) {
            current.next = next.next;
            next.next = head;
            head = next;
            next = current.next;
        }
        if (count < k) {
            return reverseKGroup2(head, count); // 递归反转前 count 个节点
        }
        current.next = reverseKGroup2(current.next, k); // 递归反转剩余节点
        return head;
    }

    public static void main(String[] args) {
        Solution0025 solution = new Solution0025();
        ListNode head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);

        int k = 3;
        ListNode newHead = solution.reverseKGroup2(head, k);
        System.out.print("翻转后的链表: ");
        while (newHead != null) {
            System.out.print(newHead.val + " ");
            newHead = newHead.next;
        }
    }
}
