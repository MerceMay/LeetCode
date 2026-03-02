package anew;

import java.util.Map;
import java.util.HashMap;

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
        if (root == null) {
            return 0;
        }
        return pathSumFrom(root, targetSum) + pathSum(root.left, targetSum) + pathSum(root.right, targetSum);
    }

    private int pathSumFrom(TreeNode node, long targetSum) {
        if (node == null) {
            return 0;
        }
        int count = 0;
        if (node.val == targetSum) {
            count++;
        }
        count += pathSumFrom(node.left, targetSum - node.val);
        count += pathSumFrom(node.right, targetSum - node.val);
        return count;
    }

    private int target;
    private int count = 0;

    public int pathSum2(TreeNode root, int targetSum) {
        if (root == null) {
            return 0;
        }
        target = targetSum;
        dfs(root);
        return count;
    }

    private void dfs(TreeNode root) {
        if (root == null) {
            return;
        }
        path2(root, 0);
        dfs(root.left);
        dfs(root.right);
    }

    private void path2(TreeNode node, int currentSum) {
        if (node == null) {
            return;
        }
        currentSum += node.val;
        if (currentSum == target) {
            count++;
        }
        path2(node.left, currentSum);
        path2(node.right, currentSum);
    }

    private int count3 = 0;

    private int pathSum3(TreeNode root, int targetSum) {
        if (root == null) {
            return 0;
        }
        dfs3(root, (long) targetSum);
        pathSum3(root.left, targetSum);
        pathSum3(root.right, targetSum);
        return count3;
    }

    private void dfs3(TreeNode node, long targetSum) {
        if (node == null) {
            return;
        }
        if (node.val == targetSum) {
            count3++;
        }
        dfs3(node.left, targetSum - node.val);
        dfs3(node.right, targetSum - node.val);
    }

    private Map<Long, Integer> prefixSumCount = new HashMap<>();
    private int count4 = 0;

    public int pathSum4(TreeNode root, int targetSum) {
        prefixSumCount.put(0L, 1);
        dfs4(root, 0L, targetSum);
        return count4;
    }

    private void dfs4(TreeNode node, long currentSum, int targetSum) {
        if (node == null) {
            return;
        }
        currentSum += node.val;
        count4 += prefixSumCount.getOrDefault(currentSum - targetSum, 0);
        prefixSumCount.put(currentSum, prefixSumCount.getOrDefault(currentSum, 0) + 1);
        dfs4(node.left, currentSum, targetSum);
        dfs4(node.right, currentSum, targetSum);
        prefixSumCount.put(currentSum, prefixSumCount.get(currentSum) - 1);
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
