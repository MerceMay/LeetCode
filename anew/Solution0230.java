package anew;

import java.util.Stack;

// 给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 小的元素（k 从 1 开始计数）。

public class Solution0230 {
    private static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int val) {
            this.val = val;
        }
    }

    private int count1 = 0;
    private int result1 = 0;

    public int kthSmallest(TreeNode root, int k) {
        inorder(root, k);
        return result1;
    }

    private void inorder(TreeNode node, int k) {
        if (node == null) {
            return;
        }
        inorder(node.left, k);
        count1++;
        if (count1 == k) {
            result1 = node.val;
            return;
        }
        inorder(node.right, k);
    }

    public int kthSmallest2(TreeNode root, int k) {
        int count2 = 0;
        if (root == null) {
            return -1;
        }
        Stack<TreeNode> stack = new Stack<>();
        TreeNode current = root;
        while (!stack.isEmpty() || current != null) {
            while (current != null) {
                stack.push(current);
                current = current.left;
            }
            current = stack.pop();
            count2++;
            if (count2 == k) {
                return current.val;
            }
            current = current.right;
        }
        return -1;
    }

    public int kthSmallest3(TreeNode root, int k) {
        if (root == null) {
            return -1;
        }
        int leftCount = countNodes(root.left);
        if (leftCount >= k) {
            return kthSmallest3(root.left, k);
        } else if (leftCount == k - 1) {
            return root.val;
        } else {
            return kthSmallest3(root.right, k - leftCount - 1);
        }
    }

    private int countNodes(TreeNode node) {
        if (node == null) {
            return 0;
        }
        return 1 + countNodes(node.left) + countNodes(node.right);
    }

    public static void main(String[] args) {
        Solution0230 solution = new Solution0230();
        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(1);
        root.right = new TreeNode(4);
        root.left.right = new TreeNode(2);
        int k = 1;
        System.out.println(solution.kthSmallest2(root, k)); // 输出: 1
        System.out.println(solution.kthSmallest3(root, k)); // 输出: 1
    }
}
