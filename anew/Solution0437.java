package anew;

// 给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。

// 路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

public class Solution0437 {
    private static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int val) {
            this.val = val;
        }
    }

    public int pathSum(TreeNode root, int targetSum) {

    }

    public static void main(String[] args) {
        Solution0437 solution = new Solution0437();
        TreeNode root = new TreeNode(10);
        root.left = new TreeNode(5);
        root.right = new TreeNode(-3);
        root.left.left = new TreeNode(3);
        root.left.right = new TreeNode(2);
        root.right.right = new TreeNode(11);
        root.left.left.left = new TreeNode(3);
        root.left.left.right = new TreeNode(-2);
        root.left.right.right = new TreeNode(1);
        int targetSum = 8;
        int result = solution.pathSum(root, targetSum);
        System.out.println(result); // 输出: 3

        int result2 = solution.pathSum2(root, targetSum);
        System.out.println(result2); // 输出: 3

        int result3 = solution.pathSum3(root, targetSum);
        System.out.println(result3); // 输出: 3

        int result4 = solution.pathSum4(root, targetSum);
        System.out.println(result4); // 输出: 3
    }
}
