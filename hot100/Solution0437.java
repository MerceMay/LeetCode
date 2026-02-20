package hot100;

import java.util.HashMap;
import java.util.Map;
// 给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。

// 路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

public class Solution0437 {
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

    public int pathSum(TreeNode root, int targetSum) {
        if (root == null) {
            return 0;
        }
        return pathSumFrom(root, (long) targetSum) + pathSum(root.left, targetSum) + pathSum(root.right, targetSum);
    }

    public int pathSumFrom(TreeNode node, long targetSum) {
        if (node == null) {
            return 0;
        }
        int count = 0;
        if (node.val == targetSum) {
            count++;
        }
        count += pathSumFrom(node.left, targetSum - node.val); // 从左子节点开始的路径数
        count += pathSumFrom(node.right, targetSum - node.val); // 从右子节点开始的路径数
        return count;
    }

    private int count2 = 0;
    private long target;

    public int pathSum2(TreeNode root, int targetSum) {
        if (root == null) {
            return 0;
        }
        target = targetSum;
        dfs2(root);
        return count2;
    }

    private void dfs2(TreeNode node) {
        if (node == null) {
            return;
        }
        addToPath(node, 0);
        dfs2(node.left);
        dfs2(node.right);
    }

    private void addToPath(TreeNode node, long currentSum) {
        if (node == null) {
            return;
        }
        currentSum += node.val;
        if (currentSum == target) {
            count2++;
        }
        addToPath(node.left, currentSum);
        addToPath(node.right, currentSum);
    }

    private int count3 = 0;

    public int pathSum3(TreeNode root, int targetSum) {
        if (root == null) {
            return 0;
        }
        dfs3(root, (long) targetSum);
        pathSum3(root.left, targetSum);
        pathSum3(root.right, targetSum);
        return count3;
    }

    private void dfs3(TreeNode node, long targetSum) { // 以当前节点为路径头的路径数
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
        dfs4(root, 0L, (long) targetSum);
        return count4;
    }

    private void dfs4(TreeNode node, long currentSum, long targetSum) {
        if (node == null) {
            return;
        }
        currentSum += node.val;
        count4 += prefixSumCount.getOrDefault(currentSum - targetSum, 0);
        prefixSumCount.put(currentSum, prefixSumCount.getOrDefault(currentSum, 0) + 1); // 将当前前缀和加入哈希表
        dfs4(node.left, currentSum, targetSum);
        dfs4(node.right, currentSum, targetSum);
        prefixSumCount.put(currentSum, prefixSumCount.get(currentSum) - 1); // 递归结束后是下一个节点的前缀和，当前前缀和不再需要，减少计数
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
