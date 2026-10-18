import java.util.*;

public class Solution0437 {
    public int pathSum(TreeNode root, int targetSum) {
        if (root == null) {
            return 0;
        }
        return recursive(root, targetSum) + pathSum(root.left, targetSum) + pathSum(root.right, targetSum);
    }

    private int recursive(TreeNode root, long targetSum) {
        if (root == null) {
            return 0;
        }
        return (root.val == targetSum ? 1 : 0) + recursive(root.left, targetSum - root.val) + recursive(root.right, targetSum - root.val);
    }

    public int pathSum2(TreeNode root, int targetSum) {
        Map<Long, Integer> prefix = new HashMap<>();
        prefix.put(0L, 1);
        return dfs(root, targetSum, prefix, 0);
    }

    private int dfs(TreeNode root, int targetSum, Map<Long, Integer> prefix, long curSum) {
        if (root == null) {
            return 0;
        }
        int count = 0;
        curSum += root.val;
        count += prefix.getOrDefault(curSum - targetSum, 0);
        prefix.put(curSum, prefix.getOrDefault(curSum, 0) + 1);
        count += dfs(root.left, targetSum, prefix, curSum);
        count += dfs(root.right, targetSum, prefix, curSum);
        prefix.put(curSum, prefix.getOrDefault(curSum, 0) - 1);
        return count;
    }
}
