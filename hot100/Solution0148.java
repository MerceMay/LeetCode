package hot100;

// 给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

import java.util.PriorityQueue;

public class Solution0148 {
    private static class ListNode {
        int val;
        ListNode next;

        ListNode() {
        }

        ListNode(int val) {
            this.val = val;
        }

        ListNode(int val, ListNode next) {
            this.val = val;
            this.next = next;
        }
    }

    public ListNode sortList(ListNode head) {
        PriorityQueue<ListNode> minHeap = new PriorityQueue<>((a, b) -> Integer.compare(a.val, b.val));
        ListNode current = head;
        while (current != null) {
            minHeap.offer(current);
            current = current.next;
        }
        ListNode dummy = new ListNode(0);
        current = dummy;
        while (!minHeap.isEmpty()) {
            current.next = minHeap.poll();
            current = current.next;
        }
        current.next = null; // 断开最后一个节点的 next 指针，避免形成循环
        return dummy.next;
    }

    public ListNode sortList2(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }
        ListNode slow = head, fast = head.next;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        ListNode mid = slow.next;
        slow.next = null; // 断开链表，将链表分为两部分
        ListNode left = sortList2(head);
        ListNode right = sortList2(mid);
        return merge(left, right);
    }

    private ListNode merge(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode(0);
        ListNode current = dummy;
        while (l1 != null && l2 != null) {
            if (l1.val < l2.val) {
                current.next = l1;
                l1 = l1.next;
            } else {
                current.next = l2;
                l2 = l2.next;
            }
            current = current.next;
        }
        current.next = (l1 != null) ? l1 : l2;
        return dummy.next;
    }

    public ListNode sortList3(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }
        int length = 0;
        ListNode current = head;
        while (current != null) {
            length++;
            current = current.next;
        }
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        for (int step = 1; step < length; step *= 2) {
            ListNode prev = dummy, curr = dummy.next;
            while (curr != null) {
                ListNode left = curr;
                ListNode right = split(left, step);
                curr = split(right, step);
                prev.next = merge(left, right);
                while (prev.next != null) {
                    prev = prev.next;
                }
            }
        }
        return dummy.next;
    }

    private ListNode split(ListNode head, int step) {
        for (int i = 1; head != null && i < step; i++) {
            head = head.next;
        }
        if (head == null) {
            return null;
        }
        ListNode second = head.next;
        head.next = null; // 断开链表
        return second;
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
