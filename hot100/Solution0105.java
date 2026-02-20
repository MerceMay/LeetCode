package hot100;

import java.util.Deque;
import java.util.LinkedList;
import java.util.Map;
import java.util.HashMap;

// 给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

public class Solution0105 {
    private static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode() {
        }

        TreeNode(int val) {
            this.val = val;
        }

        TreeNode(int val, TreeNode left, TreeNode right) {
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }

    public TreeNode buildTree(int[] preorder, int[] inorder) {
        return buildTreeHelper(preorder, 0, preorder.length - 1, inorder, 0, inorder.length - 1);
    }

    private TreeNode buildTreeHelper(int[] preorder, int preStart, int preEnd, int[] inorder, int inStart, int inEnd) {
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
        root.left = buildTreeHelper(preorder, preStart + 1, preStart + leftTreeSize, inorder, inStart, inRootIndex - 1);
        root.right = buildTreeHelper(preorder, preStart + leftTreeSize + 1, preEnd, inorder, inRootIndex + 1, inEnd);
        return root;
    }

    private Map<Integer, Integer> inorderIndexMap = new HashMap<>();

    public TreeNode buildTree2(int[] preorder, int[] inorder) {
        for (int i = 0; i < inorder.length; i++) {
            inorderIndexMap.put(inorder[i], i);
        }
        return buildTreeHelper2(preorder, 0, preorder.length - 1, inorder, 0, inorder.length - 1);
    }

    private TreeNode buildTreeHelper2(int[] preorder, int preStart, int preEnd, int[] inorder, int inStart, int inEnd) {
        if (preStart > preEnd || inStart > inEnd) {
            return null;
        }
        int rootVal = preorder[preStart];
        TreeNode root = new TreeNode(rootVal);
        int inRootIndex = inorderIndexMap.get(rootVal);
        int leftTreeSize = inRootIndex - inStart;
        root.left = buildTreeHelper2(preorder, preStart + 1, preStart + leftTreeSize, inorder, inStart,
                inRootIndex - 1);
        root.right = buildTreeHelper2(preorder, preStart + leftTreeSize + 1, preEnd, inorder, inRootIndex + 1, inEnd);
        return root;
    }

    public TreeNode buildTree3(int[] preorder, int[] inorder) {
        if (preorder == null || inorder == null || preorder.length != inorder.length) {
            return null;
        }
        TreeNode root = new TreeNode(preorder[0]);
        Deque<TreeNode> stack = new LinkedList<>();
        stack.push(root);
        int inorderIndex = 0;
        for (int i = 1; i < preorder.length; i++) {
            TreeNode node = stack.peek();
            if (node.val != inorder[inorderIndex]) { // 说明当前栈顶节点的左子树还没有构建完成
                node.left = new TreeNode(preorder[i]); // 先序遍历的下一个节点是当前栈顶节点的左子树
                stack.push(node.left); // 将左子树节点入栈
            } else { // 说明当前栈顶节点的左子树已经构建完成，需要构建右子树
                while (!stack.isEmpty() && stack.peek().val == inorder[inorderIndex]) {
                    node = stack.pop(); // 弹出栈顶节点，继续检查下一个节点是否是当前栈顶节点的右子树
                    inorderIndex++; // 中序遍历索引向右移动
                }
                node.right = new TreeNode(preorder[i]); // 先序遍历的下一个节点是当前栈顶节点的右子树
                stack.push(node.right); // 将右子树节点入栈

            }
        }
        return root;
    }

    public static void main(String[] args) {
        int[] preorder = { 3, 9, 20, 15, 7 };
        int[] inorder = { 9, 3, 15, 20, 7 };
        Solution0105 solution = new Solution0105();
        TreeNode root = solution.buildTree(preorder, inorder);
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
