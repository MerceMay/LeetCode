package hot100;

import java.util.ArrayList;
import java.util.List;
import java.util.Deque;
import java.util.ArrayDeque;

// 给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
public class Solution0199 {
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

    public List<Integer> rightSideView(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        Deque<TreeNode> deque = new ArrayDeque<>();
        deque.offer(root);
        while (!deque.isEmpty()) {
            int levelSize = deque.size();
            for (int i = 0; i < levelSize; i++) {
                TreeNode currentNode = deque.poll();
                if (i == 0) { // 每层的第一个节点就是右侧视图中的节点
                    result.add(currentNode.val);
                }
                // 先右后左入队，这样每层的第一个节点就是右侧视图中的节点
                if (currentNode.right != null) {
                    deque.offer(currentNode.right);
                }
                if (currentNode.left != null) {
                    deque.offer(currentNode.left);
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
        Deque<NodeWithLevel> deque = new ArrayDeque<>();
        deque.offer(new NodeWithLevel(root, 0));
        while (!deque.isEmpty()) {
            NodeWithLevel current = deque.poll();
            TreeNode currentNode = current.node;
            int level = current.level;
            if (level == result.size()) { // 每层的第一个节点就是右侧视图中的节点
                result.add(currentNode.val);
            }
            if (currentNode.right != null) {
                deque.offer(new NodeWithLevel(currentNode.right, level + 1));
            }
            if (currentNode.left != null) {
                deque.offer(new NodeWithLevel(currentNode.left, level + 1));
            }
        }
        return result;
    }

    public List<Integer> rightSideView3(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        dfs(root, result, 0);
        return result;
    }

    private void dfs(TreeNode node, List<Integer> result, int level) {
        if (node == null) {
            return;
        }
        if (level == result.size()) { // 每层的第一个节点就是右侧
            result.add(node.val);
        }
        dfs(node.right, result, level + 1); // 先右后左遍历，这样每层的第一个节点就是右侧视图中的节点
        dfs(node.left, result, level + 1);
    }

    public List<Integer> rightSideView4(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        Deque<NodeWithLevel> stack = new ArrayDeque<>();
        stack.push(new NodeWithLevel(root, 0));
        while (!stack.isEmpty()) {
            NodeWithLevel current = stack.pop();
            TreeNode currentNode = current.node;
            int level = current.level;
            if (level == result.size()) {
                result.add(currentNode.val);
            }
            if (currentNode.left != null) {
                stack.push(new NodeWithLevel(currentNode.left, level + 1));
            }
            if (currentNode.right != null) {
                stack.push(new NodeWithLevel(currentNode.right, level + 1));
            }
        }
        return result;
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
