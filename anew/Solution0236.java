package anew;

import java.util.Map;
import java.util.HashMap;

// 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

// 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

public class Solution0236 {
    private static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        public TreeNode(int x) {
            val = x;
        }
    }

    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null) {
            return null;
        }
        if (root == p || root == q) {
            return root;
        }
        TreeNode left = lowestCommonAncestor(root.left, p, q);
        TreeNode right = lowestCommonAncestor(root.right, p, q);
        if (left != null && right != null) {
            return root;
        }
        return left != null ? left : right;
    }

    private Map<TreeNode, TreeNode> parentMap = new HashMap<>();
    private Map<TreeNode, Boolean> visited = new HashMap<>();

    public TreeNode lowestCommonAncestor2(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null) {
            return null;
        }
        dfs(root);
        while (p != null) {
            visited.put(p, true);
            p = parentMap.get(p);
        }

        while (q != null) {
            if (visited.getOrDefault(q, false)) {
                return q;
            }
            q = parentMap.get(q);
        }
        return null;
    }

    private void dfs(TreeNode node) {
        if (node.left != null) {
            parentMap.put(node.left, node);
            dfs(node.left);
        }
        if (node.right != null) {
            parentMap.put(node.right, node);
            dfs(node.right);
        }
    }

    public static void main(String[] args) {
        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(5);
        root.right = new TreeNode(1);
        root.left.left = new TreeNode(6);
        root.left.right = new TreeNode(2);
        root.right.left = new TreeNode(0);
        root.right.right = new TreeNode(8);
        root.left.right.left = new TreeNode(7);
        root.left.right.right = new TreeNode(4);
        TreeNode p = root.left; // 节点 5
        TreeNode q = root.right; // 节点 1
        Solution0236 solution = new Solution0236();
        TreeNode ancestor = solution.lowestCommonAncestor(root, p, q);
        System.out.println(ancestor.val); // 输出: 3
        TreeNode ancestor2 = solution.lowestCommonAncestor2(root, p, q);
        System.out.println(ancestor2.val); // 输出: 3
    }
}