package anew;

import java.util.Queue;
import java.util.ArrayDeque;

// 给定一个二叉树 root ，返回其最大深度。

// 二叉树的 最大深度 是指从根节点到最远叶子节点的最长路径上的节点数。

public class Solution0104 {
    private static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int val) {
            this.val = val;
        }
    }

    public int maxDepth(TreeNode root) {
        if (root == null) {
            return 0;
        }
        return 1 + Math.max(maxDepth(root.left), maxDepth(root.right));
    }

    public int maxDepthIterative(TreeNode root) {
        if (root == null) {
            return 0;
        }
        int depth = 0;
        Queue<TreeNode> deque = new ArrayDeque<>();
        deque.offer(root);
        while (!deque.isEmpty()) {
            int levelSize = deque.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode current = deque.poll();
                if (current.left != null) {
                    deque.offer(current.left);
                }
                if (current.right != null) {
                    deque.offer(current.right);
                }
            }
            depth++;
        }
        return depth;
    }

    public static void main(String[] args) {
        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(9);
        root.right = new TreeNode(20);
        root.right.left = new TreeNode(15);
        root.right.right = new TreeNode(7);
        Solution0104 solution = new Solution0104();
        System.out.println(solution.maxDepth(root)); // 输出: 3
        System.out.println(solution.maxDepthIterative(root)); // 输出: 3
    }
}
