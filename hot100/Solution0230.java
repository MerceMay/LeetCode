package hot100;

import java.util.ArrayDeque;
import java.util.Deque;
// 给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 小的元素（k 从 1 开始计数）。

public class Solution0230 {
    private static class TreeNode {
        int val;
        int size; // 以当前节点为根的子树的节点总数
        TreeNode left;
        TreeNode right;

        TreeNode() {
        }

        TreeNode(int val) {
            this.val = val;
            this.size = 1; // 初始化size为1，表示当前节点本身
        }

        TreeNode(int val, TreeNode left, TreeNode right) {
            this.val = val;
            this.size = 1 + (left != null ? left.size : 0) + (right != null ? right.size : 0); // 计算size
            this.left = left;
            this.right = right;
        }
    }

    private int count = 0;
    private int result = 0;

    public int kthSmallest(TreeNode root, int k) {
        inorder(root, k);
        return result;
    }

    private void inorder(TreeNode node, int k) {
        if (node == null) {
            return;
        }
        inorder(node.left, k);
        count++;
        if (count == k) {
            result = node.val;
            return;
        }
        inorder(node.right, k);
    }

    private int kthSmallest2(TreeNode root, int k) {
        int count = 0;
        if (root == null) {
            return -1;
        }
        Deque<TreeNode> stack = new ArrayDeque<>();
        TreeNode current = root;
        while (current != null || !stack.isEmpty()) {
            while (current != null) {
                stack.push(current);
                current = current.left;
            }
            current = stack.pop();
            count++;
            if (count == k) {
                return current.val;
            }
            current = current.right;
        }
        return -1;
    }

    private int kthSmallest3(TreeNode root, int k) {
        int count = countNodes(root.left);
        if (k <= count) {
            return kthSmallest3(root.left, k);
        } else if (k > count + 1) {
            return kthSmallest3(root.right, k - count - 1);
        } else {
            return root.val;
        }
    }

    private int countNodes(TreeNode node) {
        if (node == null) {
            return 0;
        }
        return 1 + countNodes(node.left) + countNodes(node.right);
    }

    private int kthSmallest4(TreeNode root, int k) {
        if (root == null) {
            return -1;
        }
        int leftSize = root.left != null ? root.left.size : 0;
        if (k <= leftSize) {
            return kthSmallest4(root.left, k);
        } else if (k > leftSize + 1) {
            return kthSmallest4(root.right, k - leftSize - 1);
        } else {
            return root.val;
        }
    }

    public static void main(String[] args) {
        Solution0230 solution = new Solution0230();
        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(1);
        root.right = new TreeNode(4);
        root.left.right = new TreeNode(2);
        int k = 1;
        System.out.println(solution.kthSmallest3(root, k)); // 输出: 1
    }
}
