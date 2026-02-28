package anew;

// 给你一个链表的头节点 head ，判断链表中是否有环。

// 如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。注意：pos 不作为参数进行传递 。仅仅是为了标识链表的实际情况。

// 如果链表中存在环 ，则返回 true 。 否则，返回 false 。

public class Solution0141 {
    private static class ListNode {
        ListNode next;

        public ListNode() {
            next = null;
        }
    }

    public boolean hasCycle(ListNode head) {
        if (head == null) {
            return false;
        }
        ListNode slow = head;
        ListNode fast = head;
        while (fast != null && fast.next != null) {
            fast = fast.next.next;
            slow = slow.next;
            if (fast == slow) {
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        ListNode head = new ListNode();
        ListNode node2 = new ListNode();
        ListNode node0 = new ListNode();
        ListNode node4 = new ListNode();

        head.next = node2;
        node2.next = node0;
        node0.next = node4;
        node4.next = node2; // 创建环

        Solution0141 solution = new Solution0141();
        boolean hasCycle = solution.hasCycle(head);
        System.out.println("链表中是否有环: " + hasCycle);
    }

}
