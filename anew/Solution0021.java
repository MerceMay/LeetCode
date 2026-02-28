package anew;

// 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

public class Solution0021 {
    private static class ListNode {
        int val;
        ListNode next;

        ListNode(int x) {
            val = x;
            next = null;
        }
    }

    public ListNode mergeTwoLists(ListNode list1, ListNode list2) {
        if (list1 == null) {
            return list2;
        }
        if (list2 == null) {
            return list1;
        }
        ListNode dummy = new ListNode(0);
        ListNode current = dummy;
        while (list1 != null && list2 != null) {
            if (list1.val < list2.val) {
                current.next = list1;
                list1 = list1.next;
            } else {
                current.next = list2;
                list2 = list2.next;
            }
            current = current.next;
        }
        if (list1 != null) {
            current.next = list1;
        } else {
            current.next = list2;
        }
        return dummy.next;
    }

    public ListNode mergeTwoLists2(ListNode list1, ListNode list2) {
        if (list1 == null) {
            return list2;
        }
        if (list2 == null) {
            return list1;
        }
        if (list1.val < list2.val) {
            list1.next = mergeTwoLists2(list1.next, list2);
            return list1;
        } else {
            list2.next = mergeTwoLists2(list1, list2.next);
            return list2;
        }
    }

    public static void main(String[] args) {
        Solution0021 solution = new Solution0021();
        ListNode l1 = new ListNode(1);
        l1.next = new ListNode(2);
        l1.next.next = new ListNode(4);

        ListNode l2 = new ListNode(1);
        l2.next = new ListNode(3);
        l2.next.next = new ListNode(4);

        ListNode mergedHead = solution.mergeTwoLists(l1, l2);
        System.out.print("合并后的链表: ");
        while (mergedHead != null) {
            System.out.print(mergedHead.val + " ");
            mergedHead = mergedHead.next;
        }

        ListNode l3 = new ListNode(1);
        l3.next = new ListNode(2);
        l3.next.next = new ListNode(4);

        ListNode l4 = new ListNode(1);
        l4.next = new ListNode(3);
        l4.next.next = new ListNode(4);

        ListNode mergedHead2 = solution.mergeTwoLists2(l3, l4);
        System.out.print("\n合并后的链表（递归）: ");
        while (mergedHead2 != null) {
            System.out.print(mergedHead2.val + " ");
            mergedHead2 = mergedHead2.next;
        }
    }
}
