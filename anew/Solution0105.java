package anew;

import java.util.Deque;
import java.util.LinkedList;
import java.util.Map;
import java.util.Stack;
import java.util.HashMap;

// 给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

public class Solution0105 {
    private static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int val) {
            this.val = val;
        }
    }

    public TreeNode buildTree(int[] preorder, int[] inorder) {
        return builTreeHelper(preorder, 0, preorder.length - 1, inorder, 0, inorder.length - 1);
    }

    private TreeNode builTreeHelper(int[] preorder, int preStart, int preEnd, int[] inorder, int inStart, int inEnd) {
        if (preStart > preEnd || inStart > inEnd) {
            return null;
        }
        int rootVal = preorder[preStart];
        TreeNode root = new TreeNode(rootVal);
        int inRootIndex = inStart;
        while (inRootIndex <= inEnd && inorder[inRootIndex] != rootVal) {
            inRootIndex++;
        }
        int leftTreeSize = inRootIndex - inStart;
        root.left = builTreeHelper(preorder, preStart + 1, preStart + leftTreeSize, inorder, inStart, inRootIndex - 1);
        root.right = builTreeHelper(preorder, preStart + leftTreeSize + 1, preEnd, inorder, inRootIndex + 1, inEnd);
        return root;
    }

    private Map<Integer, Integer> inorderIndexMap = new HashMap<>();

    public TreeNode buildTree2(int[] preorder, int[] inorder) {
        for (int i = 0; i < inorder.length; i++) {
            inorderIndexMap.put(inorder[i], i);
        }
        return builTreeHelper2(preorder, 0, preorder.length - 1, inorder, 0, inorder.length - 1);
    }

    private TreeNode builTreeHelper2(int[] preorder, int preStart, int preEnd, int[] inorder, int inStart, int inEnd) {
        if (preStart > preEnd || inStart > inEnd) {
            return null;
        }
        int rootVal = preorder[preStart];
        TreeNode root = new TreeNode(rootVal);
        int inRootIndex = inorderIndexMap.get(rootVal);
        int leftTreeSize = inRootIndex - inStart;
        root.left = builTreeHelper2(preorder, preStart + 1, preStart + leftTreeSize, inorder, inStart, inRootIndex - 1);
        root.right = builTreeHelper2(preorder, preStart + leftTreeSize + 1, preEnd, inorder, inRootIndex + 1, inEnd);
        return root;
    }

    public TreeNode buildTree3(int[] preorder, int[] inorder) {
        if (preorder == null || inorder == null || preorder.length != inorder.length) {
            return null;
        }
        TreeNode root = new TreeNode(preorder[0]);
        Stack<TreeNode> stack = new Stack<>();
        stack.push(root);
        int inIndex = 0;
        for (int preIndex = 1; preIndex < preorder.length; preIndex++) {
            TreeNode node = stack.peek();
            if (node.val != inorder[inIndex]) {
                node.left = new TreeNode(preorder[preIndex]);
                stack.push(node.left);
            } else {
                while (!stack.isEmpty() && stack.peek().val == inorder[inIndex]) {
                    node = stack.pop();
                    inIndex++;
                }
                node.right = new TreeNode(preorder[preIndex]);
                stack.push(node.right);
            }
        }
        return root;
    }

    public static void main(String[] args) {
        int[] preorder = { 3, 9, 20, 15, 7 };
        int[] inorder = { 9, 3, 15, 20, 7 };
        Solution0105 solution = new Solution0105();
        TreeNode root = solution.buildTree2(preorder, inorder);
        Deque<TreeNode> deque = new LinkedList<>();
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
