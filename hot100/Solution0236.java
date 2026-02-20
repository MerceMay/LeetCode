package hot100;

import java.util.HashMap;
import java.util.Map;

// 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

// 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

public class Solution0236 {
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

    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        return dfs(root, p, q);
    }

    private TreeNode dfs(TreeNode node, TreeNode p, TreeNode q) {
        if (node == null) {
            return null;
        }
        if (node == p || node == q) {
            return node;
        }
        TreeNode left = dfs(node.left, p, q);
        TreeNode right = dfs(node.right, p, q);
        if (left != null && right != null) {
            return node; // 当前节点是最近公共祖先
        }
        return left != null ? left : right; // 返回非空的子树结果
    }

    Map<TreeNode, TreeNode> parentMap = new HashMap<>();
    Map<TreeNode, Boolean> visited = new HashMap<>();

    public TreeNode lowestCommonAncestor2(TreeNode root, TreeNode p, TreeNode q) {
        parentMap.put(root, null);
        dfs2(root);
        while (p != null) {
            visited.put(p, true);
            p = parentMap.get(p);
        }
        while (q != null) {
            if (visited.getOrDefault(q, false)) {
                return q; // q 的祖先中第一个在 p 的祖先集合中的节点就是最近公共祖先
            }
            q = parentMap.get(q);
        }
        return null;
    }

    private void dfs2(TreeNode node) {
        if (node.left != null) {
            parentMap.put(node.left, node);
            dfs2(node.left);
        }
        if (node.right != null) {
            parentMap.put(node.right, node);
            dfs2(node.right);
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
