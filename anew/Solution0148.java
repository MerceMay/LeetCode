package anew;

import java.util.PriorityQueue;

// 给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

public class Solution0148 {
    private static class ListNode {
        int val;
        ListNode next;

        public ListNode(int x) {
            val = x;
            next = null;
        }

        public ListNode(int x, ListNode next) {
            this.val = x;
            this.next = next;
        }
    }

    public ListNode sortList(ListNode head) {
        PriorityQueue<ListNode> minHeap = new PriorityQueue<>((a, b) -> Integer.compare(a.val, b.val));
        ListNode node = head;
        while (node != null) {
            minHeap.offer(node);
            node = node.next;
        }
        ListNode dummy = new ListNode(0);
        ListNode current = dummy;
        while (!minHeap.isEmpty()) {
            current.next = minHeap.poll();
            current = current.next;
        }
        current.next = null;
        return dummy.next;
    }

    public ListNode sortList2(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }
        ListNode slow = head;
        ListNode fast = head.next;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        ListNode second = slow.next;
        slow.next = null;
        ListNode left = sortList2(head);
        ListNode right = sortList2(second);
        return merge(left, right);
    }

    private ListNode merge(ListNode left, ListNode right) {
        ListNode dummy = new ListNode(0);
        ListNode current = dummy;
        while (left != null && right != null) {
            if (left.val < right.val) {
                current.next = left;
                left = left.next;
            } else {
                current.next = right;
                right = right.next;
            }
            current = current.next;
        }
        current.next = (left != null) ? left : right;
        return dummy.next;
    }

    public ListNode sortList3(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }
        ListNode node = head;
        int length = 0;
        while (node != null) {
            length++;
            node = node.next;
        }
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        for (int size = 1; size < length; size *= 2) {
            ListNode prev = dummy, curr = dummy.next;
            while (curr != null) {
                ListNode left = curr;
                ListNode right = split(left, size);
                curr = split(right, size);
                prev.next = merge(left, right);
                while (prev.next != null) {
                    prev = prev.next;
                }
            }
        }
        return dummy.next;
    }

    private ListNode split(ListNode curr, int size) {
        for (int i = 1; i < size && curr != null; i++) {
            curr = curr.next;
        }
        if (curr == null) {
            return null;
        }
        ListNode node = curr.next;
        curr.next = null;
        return node;
    }

    public static void main(String[] args) {
        Solution0148 solution = new Solution0148();
        ListNode head = new ListNode(4, new ListNode(2, new ListNode(1, new ListNode(3))));
        ListNode sortedHead = solution.sortList3(head);
        while (sortedHead != null) {
            System.out.print(sortedHead.val + " ");
            sortedHead = sortedHead.next;
        }
    }
}