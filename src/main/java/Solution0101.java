import java.util.*;

//给你一个二叉树的根节点 root ， 检查它是否轴对称。

public class Solution0101 {
    public boolean isSymmetric(TreeNode root) {
        return recursiveCheck(root.left, root.right);
    }

    public boolean recursiveCheck(TreeNode left, TreeNode right) {
        if (left == null && right == null) {
            return true;
        }
        if (left == null || right == null) {
            return false;
        }
        return left.val == right.val && recursiveCheck(left.left, right.right) && recursiveCheck(left.right, right.left);
    }

    public boolean isSymmetric2(TreeNode root) {
        return bfs(root, root);
    }

    private boolean bfs(TreeNode left, TreeNode right) {
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(left);
        queue.offer(right);
        while (!queue.isEmpty()) {
            left = queue.poll();
            right = queue.poll();
            if (left == null && right == null) {
                continue;
            }
            if ((left == null || right == null) || (right.val != left.val)) {
                return false;
            }
            queue.offer(left.left);
            queue.offer(right.right);
            queue.offer(left.right);
            queue.offer(right.left);
        }
        return true;
    }

    public boolean isSymmetric3(TreeNode root) {
        return dfs(root, root);
    }

    private boolean dfs(TreeNode left, TreeNode right) {
        Deque<TreeNode> deque = new LinkedList<>();
        deque.offer(left);
        deque.offer(right);
        while (!deque.isEmpty()) {
            left = deque.poll();
            right = deque.poll();
            if (left == null && right == null) {
                continue;
            }
            if ((left == null || right == null) || (right.val != left.val)) {
                return false;
            }
            deque.offer(left.left);
            deque.offer(right.right);
            deque.offer(left.right);
            deque.offer(right.left);
        }
        return true;
    }
}
