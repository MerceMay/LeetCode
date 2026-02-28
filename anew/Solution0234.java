package anew;

import java.util.Stack;

// 给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 。

public class Solution0234 {
    private static class ListNode {
        int val;
        ListNode next;

        public ListNode(int x) {
            val = x;
            next = null;
        }
    }

    public boolean isPalindrome(ListNode head) {
        ListNode slow = head;
        ListNode fast = head;
        while (fast != null && fast.next != null) {
            fast = fast.next.next;
            slow = slow.next;
        }
        Stack<ListNode> stack = new Stack<>();
        while (slow != null) {
            stack.push(slow);
            slow = slow.next;
        }
        ListNode current = head;
        while (!stack.isEmpty()) {
            if (current.val != stack.pop().val) {
                return false;
            }
            current = current.next;
        }
        return true;
    }

    public boolean isPalindrome2(ListNode head) {
        Stack<ListNode> stack = new Stack<>();
        ListNode current = head;
        while (current != null) {
            stack.push(current);
            current = current.next;
        }
        current = head;
        while (!stack.isEmpty()) {
            if (current.val != stack.pop().val) {
                return false;
            }
            current = current.next;
        }
        return true;
    }

    public boolean isPalindrome3(ListNode head) {
        if (head == null || head.next == null) {
            return true;
        }
        ListNode slow = head; // slow最终停在左半部分的最后一个节点
        ListNode fast = head.next;
        while (fast != null && fast.next != null) {
            fast = fast.next.next;
            slow = slow.next;
        }
        ListNode second = reverseList(slow.next);
        slow.next = null; // 将左半部分和右半部分断开
        ListNode first = head;
        while (second != null) {
            if (first.val != second.val) {
                return false;
            }
            first = first.next;
            second = second.next;
        }
        return true;
    }

    private ListNode reverseList(ListNode head) {
        ListNode prev = null;
        ListNode curr = head;
        while (curr != null) {
            ListNode next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    private ListNode frontNode = null;

    public boolean isPalindrome4(ListNode head) {
        frontNode = head;
        return recursivelyCheck(head);
    }

    private boolean recursivelyCheck(ListNode currListNode) {
        if (currListNode != null) {
            if (!recursivelyCheck(currListNode.next)) {
                return false;
            }
            if (currListNode.val != frontNode.val) {
                return false;
            }
            frontNode = frontNode.next;
        }
        return true;
    }

    public static void main(String[] args) {
        Solution0234 solution = new Solution0234();
        ListNode head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(2);
        head.next.next.next = new ListNode(1);

        boolean result = solution.isPalindrome(head);
        System.out.println("链表是否为回文链表: " + result);

        result = solution.isPalindrome2(head);
        System.out.println("链表是否为回文链表: " + result);

        result = solution.isPalindrome4(head);
        System.out.println("链表是否为回文链表: " + result);

        result = solution.isPalindrome3(head);
        System.out.println("链表是否为回文链表: " + result);
    }

}
