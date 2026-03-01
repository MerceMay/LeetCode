package anew;

import java.util.ArrayDeque;
import java.util.Deque;

public class Solution0108 {
    private static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int val) {
            this.val = val;
        }
    }

    public TreeNode sortedArrayToBST(int[] nums) {
        return buildBST(nums, 0, nums.length - 1);
    }

    private TreeNode buildBST(int[] nums, int left, int right) {
        if (left > right) {
            return null;
        }
        int mid = left + (right - left) / 2;
        TreeNode node = new TreeNode(nums[mid]);
        node.left = buildBST(nums, left, mid - 1);
        node.right = buildBST(nums, mid + 1, right);
        return node;
    }

    public static void main(String[] args) {
        Solution0108 solution = new Solution0108();
        int[] nums = { -10, -3, 0, 5, 9 };
        TreeNode root = solution.sortedArrayToBST(nums);
        Deque<TreeNode> deque = new ArrayDeque<>();
        deque.offer(root);
        while (!deque.isEmpty()) {
            TreeNode current = deque.poll();
            System.out.print(current.val + " ");
            if (current.left != null) {
                deque.offer(current.left);
            }
            if (current.right != null) {
                deque.offer(current.right);
            }
        }
    }
}
