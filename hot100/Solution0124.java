package hot100;

// 二叉树中的 路径 被定义为一条节点串行，串行中每对相邻节点之间都存在一条边。同一个节点在一条路径串行中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。

// 路径和 是路径中各节点值的总和。

// 给你一个二叉树的根节点 root ，返回其 最大路径和 。

public class Solution0124 {
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

    private int maxSum = Integer.MIN_VALUE;

    public int maxPathSum(TreeNode root) {
        dfs(root);
        return maxSum;
    }

    private int dfs(TreeNode node) {
        if (node == null) {
            return 0;
        }
        int leftMax = Math.max(0, dfs(node.left)); // 左子树的最大贡献值，如果为负数则不贡献
        int rightMax = Math.max(0, dfs(node.right)); // 右子树的最大贡献值，如果为负数则不贡献
        int currentMax = node.val + leftMax + rightMax; // 当前节点作为路径头的最大路径和
        maxSum = Math.max(maxSum, currentMax); // 更新全局最大路径和
        return node.val + Math.max(leftMax, rightMax); // 返回当前节点作为路径中间点的最大贡献值
    }

    public static void main(String[] args) {
        TreeNode root = new TreeNode(-10);
        root.left = new TreeNode(9);
        root.right = new TreeNode(20);
        root.right.left = new TreeNode(15);
        root.right.right = new TreeNode(7);
        Solution0124 solution = new Solution0124();
        int result = solution.maxPathSum(root);
        System.out.println(result); // 输出: 42
    }
}
