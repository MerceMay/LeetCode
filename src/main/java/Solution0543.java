import java.util.*;

//给你一棵二叉树的根节点，返回该树的 直径 。
//
//二叉树的 直径 是指树中任意两个节点之间最长路径的 长度 。这条路径可能经过也可能不经过根节点 root 。
//
//两节点之间路径的 长度 由它们之间边数表示。

public class Solution0543 {
    private int diameter = 0;

    public int diameterOfBinaryTree(TreeNode root) {
        dfs(root);
        return diameter;
    }

    private int dfs(TreeNode node) {
        if (node == null) {
            return 0;
        }
        int leftDepth = dfs(node.left);
        int rightDepth = dfs(node.right);
        diameter = Math.max(diameter, leftDepth + rightDepth);
        return Math.max(leftDepth, rightDepth) + 1;
    }

    public int diameterOfBinaryTree2(TreeNode root) {
        if (root == null) {
            return 0;
        }
        int diameter = 0;
        record NodeInfo(TreeNode node, boolean visited) {
        }
        Deque<NodeInfo> stack = new LinkedList<>();
        Map<TreeNode, Integer> height = new HashMap<>();
        stack.push(new NodeInfo(root, false));
        while (!stack.isEmpty()) {
            NodeInfo nodeInfo = stack.pop();
            TreeNode node = nodeInfo.node();
            if (!nodeInfo.visited()) {
                stack.push(new NodeInfo(node, true));
                if (node.left != null) {
                    stack.push(new NodeInfo(node.left, false));
                }
                if (node.right != null) {
                    stack.push(new NodeInfo(node.right, false));
                }
            } else {
                int leftDepth = height.getOrDefault(node.left, 0);
                int rightDepth = height.getOrDefault(node.right, 0);
                diameter = Math.max(diameter, leftDepth + rightDepth);
                height.put(node, Math.max(leftDepth, rightDepth) + 1);
            }
        }
        return diameter;
    }
}
