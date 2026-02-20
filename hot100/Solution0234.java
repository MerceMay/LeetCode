package hot100;

// 给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 
public class Solution0234 {
    private static class ListNode {
        int val;
        ListNode next;

        ListNode(int x) {
            val = x;
            next = null;
        }
    }

    public boolean isPalindrome(ListNode head) {
        if (head == null || head.next == null) {
            return true;
        }
        ListNode slow = head;
        ListNode fast = head.next;
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        ListNode secondHalfHead = slow.next;
        ListNode reversedSecondHalfHead = reverseList(secondHalfHead);
        ListNode temp = reversedSecondHalfHead;
        ListNode firstHalfHead = head;
        boolean isPalindrome = true;
        while (reversedSecondHalfHead != null) {
            if (firstHalfHead.val != reversedSecondHalfHead.val) {
                isPalindrome = false;
                break;
            }
            firstHalfHead = firstHalfHead.next;
            reversedSecondHalfHead = reversedSecondHalfHead.next;
        }
        slow.next = reverseList(temp);
        return isPalindrome;
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

    public boolean isPalindrome2(ListNode head) {
        frontNode = head;
        return recursivelyCheck(head);
    }

    private boolean recursivelyCheck(ListNode currentNode) {
        if (currentNode != null) {
            if (!recursivelyCheck(currentNode.next)) {
                return false;
            }
            if (currentNode.val != frontNode.val) { // 奇数递归时，currentNode和frontNode会指向同一个节点；偶数递归到这里，currentNode和frontNode会指向对半的两个节点，递归出栈后，分别向两边移动，直到相遇
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
        boolean result2 = solution.isPalindrome2(head);
        System.out.println("链表是否为回文链表(递归方法): " + result2);
    }

}
