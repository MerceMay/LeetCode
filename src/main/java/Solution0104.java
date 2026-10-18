import java.util.*;

//给定一个二叉树 root ，返回其最大深度。
//
//二叉树的 最大深度 是指从根节点到最远叶子节点的最长路径上的节点数。

public class Solution0104 {
    public int maxDepth(TreeNode root) {
        int depth = 0;
        if (root == null) {
            return 0;
        }
        Queue<TreeNode> queue = new ArrayDeque<>();
        queue.offer(root);
        while (!queue.isEmpty()) {
            int size = queue.size();
            while (size-- > 0) {
                TreeNode cur = queue.poll();
                if (cur.left != null) queue.offer(cur.left);
                if (cur.right != null) queue.offer(cur.right);
            }
            depth++;
        }
        return depth;
    }

    public int maxDepth2(TreeNode root) {
        int depth = 0;
        if (root == null) {
            return 0;
        }
        record NodeInfo(TreeNode treeNode, int depth) {
        }
        Deque<NodeInfo> stack = new LinkedList<>();
        stack.push(new NodeInfo(root, 1));
        while (!stack.isEmpty()) {
            NodeInfo nodeInfo = stack.pop();
            TreeNode cur = nodeInfo.treeNode();
            int curDepth = nodeInfo.depth();
            depth = Math.max(depth, curDepth);
            if (cur.left != null) {
                stack.push(new NodeInfo(cur.left, curDepth + 1));
            }
            if (cur.right != null) {
                stack.push(new NodeInfo(cur.right, curDepth + 1));
            }
        }
        return depth;
    }

    public int maxDepth3(TreeNode root) {
        if (root == null) {
            return 0;
        } else {
            return Math.max(maxDepth3(root.left), maxDepth3(root.right)) + 1;
        }
    }
}
