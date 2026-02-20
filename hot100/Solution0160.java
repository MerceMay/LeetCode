package hot100;
// 给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null 。

// 图示两个链表在节点 c1 开始相交：
public class Solution0160 {
    private static class ListNode {
        int val;
        ListNode next;

        ListNode(int x) {
            val = x;
            next = null;
        }
    }

    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        if (headA == null || headB == null) {
            return null;
        }
        ListNode p1 = headA, p2 = headB;
        while (p1 != p2) {
            p1 = (p1 == null) ? headB : p1.next;
            p2 = (p2 == null) ? headA : p2.next;
        }
        return p1;
    }

    public static void main(String[] args) {
        Solution0160 solution = new Solution0160();
        ListNode headA = new ListNode(4);
        headA.next = new ListNode(1);
        ListNode c1 = new ListNode(8);
        headA.next.next = c1;
        c1.next = new ListNode(4);
        c1.next.next = new ListNode(5);

        ListNode headB = new ListNode(5);
        headB.next = new ListNode(6);
        headB.next.next = new ListNode(1);
        headB.next.next.next = c1;

        ListNode intersection = solution.getIntersectionNode(headA, headB);
        if (intersection != null) {
            System.out.println("相交节点的值: " + intersection.val);
        } else {
            System.out.println("两个链表没有相交节点");
        }
    }

}
