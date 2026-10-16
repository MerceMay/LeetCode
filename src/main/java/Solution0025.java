import java.util.*;

//给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
//
//k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
//
//你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

public class Solution0025 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int k = sc.nextInt();
        int[] list = Arrays.stream(line.substring(1, line.length() - 1).split(","))
                .mapToInt(Integer::parseInt)
                .toArray();
        ListNode head = new ListNode(list[0]);
        ListNode cur = head;
        for (int i = 1; i < list.length; i++) {
            cur.next = new ListNode(list[i]);
            cur = cur.next;
        }
        cur = reverseKGroup(head, k);
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

    public static ListNode reverseKGroup(ListNode head, int k) {
        if (head == null) {
            return null;
        }

        ListNode oldHead = head, cur = head.next;
        int count = 1;
        while (count < k && cur != null) {
            ListNode next = cur.next;
            oldHead.next = next;
            cur.next = head;
            head = cur;
            cur = next;
            count++;
        }
        if (count < k) {
            return reverseKGroup(head, count);
        }
        oldHead.next = reverseKGroup(cur, k);
        return head;
    }
}
