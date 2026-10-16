import java.util.*;

//给定一个二叉树 root ，返回其最大深度。
//
//二叉树的 最大深度 是指从根节点到最远叶子节点的最长路径上的节点数。

public class Solution0104 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        String[] nodes = line.substring(1, line.length() - 1).split(",");

        TreeNode root = new TreeNode(Integer.parseInt(nodes[0]));

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        int i = 1;
        while (i < nodes.length) {
            TreeNode cur = queue.poll();
            if (i < nodes.length && !nodes[i].equals("null")) {
                cur.left = new TreeNode(Integer.parseInt(nodes[i]));
                queue.offer(cur.left);
            }
            i++;
            if (i < nodes.length && !nodes[i].equals("null")) {
                cur.right = new TreeNode(Integer.parseInt(nodes[i]));
                queue.offer(cur.right);
            }
            i++;
        }
        System.out.println(maxDepth(root));
        System.out.println(maxDepth2(root));
        System.out.println(maxDepth3(root));
    }

    public static class TreeNode {
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

    public static int maxDepth(TreeNode root) {
        int depth = 0;
        if (root == null) {
            return depth;
        }
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        while (!queue.isEmpty()) {
            int size = queue.size();
            while (size > 0) {
                TreeNode cur = queue.poll();
                if (cur.left != null) queue.offer(cur.left);
                if (cur.right != null) queue.offer(cur.right);
                size--;
            }
            depth++;
        }
        return depth;
    }


    public static int maxDepth2(TreeNode root) {
        int depth = 0;
        if (root == null) {
            return depth;
        }
        record NodeDepth(TreeNode node, int depth) {}
        Deque<NodeDepth> stack = new LinkedList<>();
        stack.push(new NodeDepth(root, 1));
        while (!stack.isEmpty()) {
            NodeDepth pair = stack.pop();
            TreeNode cur = pair.node();
            int curDepth = pair.depth();
            depth = Math.max(depth, curDepth);
            if (cur.left != null) {
                stack.push(new NodeDepth(cur.left, curDepth + 1));
            }
            if (cur.right != null) {
                stack.push(new NodeDepth(cur.right, curDepth + 1));
            }
        }
        return depth;
    }

    public static int maxDepth3(TreeNode root) {
        if (root == null) {
            return 0;
        } else {
            return Math.max(maxDepth3(root.left), maxDepth3(root.right)) + 1;
        }
    }
}
