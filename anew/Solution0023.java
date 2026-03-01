package anew;

import java.util.Comparator;
import java.util.PriorityQueue;

// 给你一个链表数组，每个链表都已经按升序排列。

// 请你将所有链表合并到一个升序链表中，返回合并后的链表。

public class Solution0023 {
    private static class ListNode {
        int val;
        ListNode next;

        public ListNode(int x) {
            val = x;
            next = null;
        }

        public ListNode(int x, ListNode node) {
            val = x;
            next = node;
        }
    }

    public ListNode mergeKLists(ListNode[] lists) {
        if (lists == null || lists.length == 0) {
            return null;
        }
        ListNode result = null;
        for (ListNode list : lists) {
            result = mergeTwoLists(result, list);
        }
        return result;
    }

    private ListNode mergeTwoLists(ListNode l1, ListNode l2) {
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

    public ListNode mergeKLists2(ListNode[] lists) {
        if (lists == null || lists.length == 0) {
            return null;
        }
        return mergeKListsHelper(lists, 0, lists.length - 1);
    }

    private ListNode mergeKListsHelper(ListNode[] lists, int start, int end) {
        if (start == end) {
            return lists[start];
        }
        int mid = start + (end - start) / 2;
        ListNode left = mergeKListsHelper(lists, start, mid);
        ListNode right = mergeKListsHelper(lists, mid + 1, end);
        return mergeTwoLists(left, right);
    }

    private ListNode mergeKLists3(ListNode[] lists) {
        if (lists == null || lists.length == 0) {
            return null;
        }
        PriorityQueue<ListNode> minHeap = new PriorityQueue<>(Comparator.comparingInt(node -> node.val));
        for (ListNode list : lists) {
            if (list != null) {
                minHeap.offer(list);
            }
        }
        ListNode dummy = new ListNode(0);
        ListNode current = dummy;
        while (!minHeap.isEmpty()) {
            ListNode node = minHeap.poll();
            current.next = node;
            current = current.next;
            if (node.next != null) {
                minHeap.offer(node.next);
            }
        }
        return dummy.next;
    }

    public static void main(String[] args) {
        Solution0023 solution = new Solution0023();
        ListNode[] lists = new ListNode[3];
        lists[0] = new ListNode(1, new ListNode(4, new ListNode(5)));
        lists[1] = new ListNode(1, new ListNode(3, new ListNode(4)));
        lists[2] = new ListNode(2, new ListNode(6));
        ListNode mergedHead = solution.mergeKLists3(lists);
        // 打印合并后的链表
        ListNode current = mergedHead;
        while (current != null) {
            System.out.print(current.val + " ");
            current = current.next;
        }
    }
}
