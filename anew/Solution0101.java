package anew;

import java.util.LinkedList;
import java.util.Deque;

// 给你一个二叉树的根节点 root ， 检查它是否轴对称。

public class Solution0101 {
    private static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int val) {
            this.val = val;
        }
    }

    public boolean isSymmetric(TreeNode root) {
        if (root == null) {
            return true;
        }
        return isMirror(root.left, root.right);
    }

    private boolean isMirror(TreeNode t1, TreeNode t2) {
        if (t1 == null && t2 == null) {
            return true;
        }
        if (t1 == null || t2 == null) {
            return false;
        }
        return (t1.val == t2.val)
                && isMirror(t1.left, t2.right)
                && isMirror(t1.right, t2.left);
    }

    public boolean isSymmetricIterative(TreeNode root) {
        if (root == null) {
            return true;
        }
        Deque<TreeNode> deque = new LinkedList<>();
        deque.offer(root.left);
        deque.offer(root.right);
        while (!deque.isEmpty()) {
            TreeNode t1 = deque.poll();
            TreeNode t2 = deque.poll();
            if (t1 == null && t2 == null) {
                continue;
            }
            if (t1 == null || t2 == null || t1.val != t2.val) {
                return false;
            }
            deque.offer(t1.left);
            deque.offer(t2.right);
            deque.offer(t1.right);
            deque.offer(t2.left);
        }
        return true;
    }

    public static void main(String[] args) {
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(2);
        root.left.left = new TreeNode(3);
        root.left.right = new TreeNode(4);
        root.right.left = new TreeNode(4);
        root.right.right = new TreeNode(3);

        Solution0101 solution = new Solution0101();
        System.out.println(solution.isSymmetric(root)); // 输出: true
        System.out.println(solution.isSymmetricIterative(root)); // 输出: true

    }
}
