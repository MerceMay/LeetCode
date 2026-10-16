import java.util.*;

//给你一棵二叉树的根节点，返回该树的 直径 。
//
//二叉树的 直径 是指树中任意两个节点之间最长路径的 长度 。这条路径可能经过也可能不经过根节点 root 。
//
//两节点之间路径的 长度 由它们之间边数表示。

public class Solution0543 {
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

        System.out.println(diameterOfBinaryTree(root));
        System.out.println(diameterOfBinaryTree2(root));

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

    private static int diameter = 0;

    public static int diameterOfBinaryTree(TreeNode root) {
        dfs(root);
        return diameter;
    }

    // 记录以节点为端点的边数，注意，官方的是点数，+1-1的问题
    private static int dfs(TreeNode root) {
        if (root == null) {
            return 0;
        }
        int leftDepth = dfs(root.left);
        int rightDepth = dfs(root.right);
        diameter = Math.max(diameter, leftDepth + rightDepth);
        return Math.max(leftDepth, rightDepth) + 1;
    }

    // 需要先获得左右子节点的信息，所以是后序
    public static int diameterOfBinaryTree2(TreeNode root) {
        int diameter = 0;
        Map<TreeNode, Integer> depth = new HashMap<>();
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
            int leftDepth = cur.left == null ? 0 : depth.get(cur.left);
            int rightDepth = cur.right == null ? 0 : depth.get(cur.right);

            diameter = Math.max(diameter, leftDepth + rightDepth);

            depth.put(cur, Math.max(leftDepth, rightDepth) + 1);
        }
        return diameter;
    }
}
