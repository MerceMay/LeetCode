package anew;

import java.util.ArrayDeque;
import java.util.Deque;

public class Solution0025 {
    private static class ListNode {
        int val;
        ListNode next;

        public ListNode(int x) {
            val = x;
            next = null;
        }
    }

    public ListNode reverseKGroup(ListNode head, int k) {
        Deque<ListNode> deque = new ArrayDeque<>();
        ListNode dummy = new ListNode(0);
        ListNode current = dummy;
        ListNode node = head;
        while (node != null) {
            int count = 0;
            while (node != null && count < k) {
                deque.addLast(node);
                node = node.next;
                count++;
            }
            if (count == k) {
                while (!deque.isEmpty()) {
                    current.next = deque.pollLast();
                    current = current.next;
                }
                current.next = null;
            } else {
                while (!deque.isEmpty()) {
                    current.next = deque.pollFirst();
                    current = current.next;
                }
            }
        }
        return dummy.next;
    }

    public ListNode reverseKGroup2(ListNode head, int k) {
        if (head == null || k == 1)
            return head;
        // 三个指针：prev, curr, next
        ListNode prev = null;
        ListNode curr = head;
        int count = 0;
        while (curr != null && count < k) {
            ListNode next = curr.next;
            curr.next = prev;
            prev = curr; // prev 一直是当前翻转后的链表的头节点
            curr = next;
            count++;
        }
        if (count < k) {
            return reverseKGroup2(prev, count); // 如果不足 k 个节点，继续翻转回原来的顺序
        }
        head.next = reverseKGroup2(curr, k);
        return prev;
    }

    public ListNode reverseKGroup3(ListNode head, int k) {
        if (head == null || k == 1) {
            return head;
        }
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        ListNode prevGroupEnd = dummy;
        while (true) {
            ListNode groupStart = prevGroupEnd.next;
            ListNode node = groupStart;
            for (int i = 1; i < k && node != null; i++) {
                node = node.next;
            }
            if (node == null) {
                break;
            }
            ListNode nextGropuStart = node.next;
            ListNode prev = null;
            ListNode curr = groupStart;
            for (int i = 0; i < k; i++) {
                ListNode next = curr.next;
                curr.next = prev;
                prev = curr;
                curr = next;
            }
            prevGroupEnd.next = prev;
            groupStart.next = nextGropuStart;
            prevGroupEnd = groupStart;
        }
        return dummy.next;
    }

    public static void main(String[] args) {
        Solution0025 solution = new Solution0025();
        ListNode head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);

        int k = 3;
        ListNode newHead = solution.reverseKGroup3(head, k);
        System.out.print("翻转后的链表: ");
        while (newHead != null) {
            System.out.print(newHead.val + " ");
            newHead = newHead.next;
        }
    }
}
