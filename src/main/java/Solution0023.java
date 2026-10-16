import java.util.*;

//给你一个链表数组，每个链表都已经按升序排列。
//
//请你将所有链表合并到一个升序链表中，返回合并后的链表。

public class Solution0023 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int[][] nums = Arrays.stream(line.substring(2, line.length() - 2).split("],\\["))
                .map(s -> Arrays.stream(s.split(","))
                        .mapToInt(Integer::parseInt)
                        .toArray())
                .toArray(int[][]::new);
        ListNode[] lists = new ListNode[nums.length];
        for (int i = 0; i < nums.length; i++) {
            int[] list = nums[i];
            ListNode dummy = new ListNode(0);
            ListNode cur = dummy;
            for (int node : list) {
                cur.next = new ListNode(node);
                cur = cur.next;
            }
            lists[i] = dummy.next;
        }
        ListNode cur = mergeKLists2(lists);
        while (cur != null) {
            System.out.println(cur.val);
            cur = cur.next;
        }
    }

    public static class ListNode {
        public int val;
        public ListNode next;

        public ListNode(int x) {
            val = x;
            next = null;
        }
    }

    public static ListNode mergeKLists(ListNode[] lists) {
        return merge(lists, 0, lists.length - 1);
    }

    private static ListNode merge(ListNode[] lists, int left, int right) {
        if (left == right) {
            return lists[left];
        }
        if (left > right) {
            return null;
        }
        int mid = left + ((right - left) >> 1);
        return merge(merge(lists, left, mid), merge(lists, mid + 1, right));
    }

    private static ListNode merge(ListNode list1, ListNode list2) {
        if (list1 == null || list2 == null) {
            return list1 == null ? list2 : list1;
        }
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
        cur.next = (p1 == null) ? p2 : p1;
        return dummy.next;
    }


    public static ListNode mergeKLists2(ListNode[] lists) {
        PriorityQueue<ListNode> pq = new PriorityQueue<>((a, b) -> Integer.compare(a.val, b.val));
        for (ListNode list : lists) {
            if (list != null) {
                pq.offer(list);
            }
        }
        ListNode dummy = new ListNode(0);
        ListNode cur = dummy;
        while (!pq.isEmpty()) {
            ListNode node = pq.poll();
            cur.next = node;
            cur = cur.next;
            if (node.next != null) {
                pq.offer(node.next);
            }
        }
        return dummy.next;
    }
}
