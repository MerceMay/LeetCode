package anew;

import java.util.List;
import java.util.ArrayList;
import java.util.Queue;
import java.util.Stack;
import java.util.LinkedList;

// 给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

public class Solution0199 {
    private static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int val) {
            this.val = val;
        }
    }

    public List<Integer> rightSideView(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode currentNode = queue.poll();
                if (i == levelSize - 1) { // 每层的最后一个节点就是右侧视图中的节点
                    result.add(currentNode.val);
                }
                if (currentNode.left != null) {
                    queue.offer(currentNode.left);
                }
                if (currentNode.right != null) {
                    queue.offer(currentNode.right);
                }
            }
        }
        return result;
    }

    private record NodeWithLevel(TreeNode node, int level) {
    }

    public List<Integer> rightSideView2(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        Queue<NodeWithLevel> queue = new LinkedList<>();
        queue.offer(new NodeWithLevel(root, 0));
        while (!queue.isEmpty()) {
            NodeWithLevel current = queue.poll();
            TreeNode currentNode = current.node();
            int currentLevel = current.level();
            if (currentLevel == result.size()) { // 每层的第一个节点就是右侧视图中的节点
                result.add(currentNode.val);
            }
            if (currentNode.right != null) {
                queue.offer(new NodeWithLevel(currentNode.right, currentLevel + 1));
            }
            if (currentNode.left != null) {
                queue.offer(new NodeWithLevel(currentNode.left, currentLevel + 1));
            }
        }
        return result;
    }

    public List<Integer> rightSideView3(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        Stack<NodeWithLevel> stack = new Stack<>();
        stack.push(new NodeWithLevel(root, 0));
        while (!stack.isEmpty()) {
            NodeWithLevel current = stack.pop();
            TreeNode currentNode = current.node();
            int currentLevel = current.level();
            if (currentLevel == result.size()) { // 每层的第一个节点就是右侧视图中的节点
                result.add(currentNode.val);
            }
            if (currentNode.left != null) {
                stack.push(new NodeWithLevel(currentNode.left, currentLevel + 1));
            }
            if (currentNode.right != null) {
                stack.push(new NodeWithLevel(currentNode.right, currentLevel + 1));
            }
        }

        return result;
    }

    public List<Integer> rightSideView4(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        dfs(root, 0, result);
        return result;
    }

    private void dfs(TreeNode node, int level, List<Integer> result) {
        if (node == null) {
            return;
        }
        if (level == result.size()) { // 每层的第一个节点就是右侧视图中的节点
            result.add(node.val);
        }
        // 先右后左遍历，这样每层的第一个节点就是右侧视图中的节点
        dfs(node.right, level + 1, result);
        dfs(node.left, level + 1, result);
    }

    public static void main(String[] args) {
        Solution0199 solution = new Solution0199();
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.right = new TreeNode(5);
        root.right.right = new TreeNode(4);
        System.out.println(solution.rightSideView(root)); // 输出: [1, 3, 4]
        System.out.println(solution.rightSideView2(root)); // 输出: [1, 3, 4]
        System.out.println(solution.rightSideView3(root)); // 输出: [1, 3, 4]
        System.out.println(solution.rightSideView4(root)); // 输出: [1, 3, 4]
    }

}
