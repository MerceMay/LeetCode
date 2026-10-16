import java.util.*;

//二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。
//
//路径和 是路径中各节点值的总和。
//
//给你一个二叉树的根节点 root ，返回其 最大路径和 。

public class Solution0124 {
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

        System.out.println(maxPathSum(root));
        System.out.println(maxPathSum2(root));
        System.out.println(maxPathSum3(root));
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

    private static int maxSum = Integer.MIN_VALUE;

    public static int maxPathSum(TreeNode root) {
        dfs(root);
        return maxSum;
    }

    private static int dfs(TreeNode node) {
        if (node == null) {
            return 0;
        }
        int leftMaxSum = Math.max(dfs(node.left), 0);
        int rightMaxSum = Math.max(dfs(node.right), 0);
        int nodeMaxSum = node.val + leftMaxSum + rightMaxSum;
        maxSum = Math.max(maxSum, nodeMaxSum);
        return node.val + Math.max(leftMaxSum, rightMaxSum);
    }

    public static int maxPathSum2(TreeNode root) {
        if (root == null) {
            return 0;
        }
        int result = Integer.MIN_VALUE;
        Map<TreeNode, Integer> maxSum = new HashMap<>();
        Deque<TreeNode> stack1 = new LinkedList<>();
        Deque<TreeNode> stack2 = new LinkedList<>();
        stack1.push(root);
        while (!stack1.isEmpty()) {
            TreeNode cur = stack1.pop();
            stack2.push(cur);
            if (cur.left != null) {
                stack1.push(cur.left);
            }
            if (cur.right != null) {
                stack1.push(cur.right);
            }
        }
        while (!stack2.isEmpty()) {
            TreeNode cur = stack2.pop();
            int leftMaxSum = Math.max(cur.left == null ? 0 : maxSum.get(cur.left), 0);
            int rightMaxSum = Math.max(cur.right == null ? 0 : maxSum.get(cur.right), 0);
            int nodeMaxSum = cur.val + leftMaxSum + rightMaxSum;
            result = Math.max(result, nodeMaxSum);
            maxSum.put(cur, cur.val + Math.max(leftMaxSum, rightMaxSum));
        }
        return result;
    }

    public static int maxPathSum3(TreeNode root) {
        if (root == null) {
            return 0;
        }
        int result = Integer.MIN_VALUE;
        Map<TreeNode, Integer> maxSum = new HashMap<>();
        record NodeInfo(TreeNode node, boolean visited) {
        }
        Deque<NodeInfo> stack = new LinkedList<>();
        stack.push(new NodeInfo(root, false));
        while (!stack.isEmpty()) {
            NodeInfo ni = stack.pop();
            TreeNode node = ni.node();
            boolean visited = ni.visited();
            if (!visited) {
                stack.push(new NodeInfo(node, true));
                if (node.right != null) {
                    stack.push(new NodeInfo(node.right, false));
                }
                if (node.left != null) {
                    stack.push(new NodeInfo(node.left, false));
                }
            } else {
                int leftMaxSum = Math.max(node.left == null ? 0 : maxSum.get(node.left), 0);
                int rightMaxSum = Math.max(node.right == null ? 0 : maxSum.get(node.right), 0);
                int nodeMaxSum = node.val + leftMaxSum + rightMaxSum;
                result = Math.max(result, nodeMaxSum);
                maxSum.put(node, node.val + Math.max(leftMaxSum, rightMaxSum));
            }
        }
        return result;
    }
}
