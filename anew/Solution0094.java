package anew;
// 给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;
import java.util.Queue;
import java.util.LinkedList;

public class Solution0094 {
    private static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int val) {
            this.val = val;
        }
    }

    public List<Integer> preorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        preorderTraversal(root, result);
        return result;
    }

    private void preorderTraversal(TreeNode node, List<Integer> result) {
        if (node == null) {
            return;
        }
        result.add(node.val);
        preorderTraversal(node.left, result);
        preorderTraversal(node.right, result);
    }

    public List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        inorderTraversal(root, result);
        return result;
    }

    private void inorderTraversal(TreeNode node, List<Integer> result) {
        if (node == null) {
            return;
        }
        inorderTraversal(node.left, result);
        result.add(node.val);
        inorderTraversal(node.right, result);
    }

    public List<Integer> postorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        postorderTraversal(root, result);
        return result;
    }

    private void postorderTraversal(TreeNode node, List<Integer> result) {
        if (node == null) {
            return;
        }
        postorderTraversal(node.left, result);
        postorderTraversal(node.right, result);
        result.add(node.val);
    }

    public List<Integer> preorderTraversalIterative(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        Stack<TreeNode> stack = new Stack<>();
        stack.push(root);
        while (!stack.isEmpty()) {
            TreeNode node = stack.pop();
            result.add(node.val);
            if (node.right != null) {
                stack.push(node.right);
            }
            if (node.left != null) {
                stack.push(node.left);
            }
        }
        return result;
    }

    public List<Integer> inorderTraversalIterative(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        Stack<TreeNode> stack = new Stack<>();
        TreeNode current = root;
        while (current != null || !stack.isEmpty()) {
            while (current != null) {
                stack.add(current);
                current = current.left;
            }
            current = stack.pop();
            result.add(current.val);
            current = current.right;
        }
        return result;
    }

    public List<Integer> postorderTraversalIterative(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        Stack<TreeNode> stack1 = new Stack<>();
        Stack<TreeNode> stack2 = new Stack<>();
        stack1.push(root);
        while (!stack1.isEmpty()) {
            TreeNode node = stack1.pop();
            stack2.push(node);
            if (node.right != null) {
                stack1.push(node.right);
            }
            if (node.left != null) {
                stack1.push(node.left);
            }
        }
        while (!stack2.isEmpty()) {
            result.add(stack2.pop().val);
        }
        return result;
    }

    public List<Integer> levelorderTraversalIterative(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        while (!queue.isEmpty()) {
            TreeNode node = queue.poll();
            result.add(node.val);
            if (node.left != null) {
                queue.offer(node.left);
            }
            if (node.right != null) {
                queue.offer(node.right);
            }
        }
        return result;
    }

    public static void main(String[] args) {
        TreeNode root = new TreeNode(1);
        root.right = new TreeNode(2);
        root.right.left = new TreeNode(3);

        Solution0094 solution = new Solution0094();
        System.out.println(solution.preorderTraversal(root)); // 输出: [1, 2, 3]
        System.out.println(solution.inorderTraversal(root)); // 输出: [1, 3, 2]
        System.out.println(solution.postorderTraversal(root)); // 输出: [3, 2, 1]
        System.out.println(solution.preorderTraversalIterative(root)); // 输出: [1, 2, 3]
        System.out.println(solution.inorderTraversalIterative(root)); // 输出: [1, 3, 2]
        System.out.println(solution.postorderTraversalIterative(root)); // 输出: [3, 2, 1]
        System.out.println(solution.levelorderTraversalIterative(root)); // 输出: [1, 2, 3]
    }

}