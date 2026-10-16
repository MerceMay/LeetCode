import java.util.*;

//给你一个二叉树的根节点 root ， 检查它是否轴对称。

public class Solution0101 {
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

        System.out.println(isSymmetric(root));
        System.out.println(isSymmetric2(root));
        System.out.println(isSymmetric3(root));
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

    public static boolean isSymmetric(TreeNode root) {
        return recursiveCompareTwoChild(root.left, root.right);
    }

    private static boolean recursiveCompareTwoChild(TreeNode left, TreeNode right) {
        if (left == null && right == null) {
            return true;
        }
        if (left == null || right == null) {
            return false;
        }
        return left.val == right.val && recursiveCompareTwoChild(left.left, right.right) && recursiveCompareTwoChild(left.right, right.left);
    }

    public static boolean isSymmetric2(TreeNode root) {
        return isMirrorDFS(root, root);
    }

    private static boolean isMirrorDFS(TreeNode left, TreeNode right) {
        Deque<TreeNode> stack = new LinkedList<>();
        stack.push(left);
        stack.push(right);
        while (!stack.isEmpty()) {
            right = stack.pop();
            left = stack.pop();
            if (right == null && left == null)
                continue;
            if ((right == null || left == null) || (right.val != left.val))
                return false;
            stack.push(left.left);
            stack.push(right.right);
            stack.push(left.right);
            stack.push(right.left);
        }
        return true;
    }

    public static boolean isSymmetric3(TreeNode root) {
        return isMirrorBFS(root, root);
    }

    private static boolean isMirrorBFS(TreeNode left, TreeNode right) {
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(left);
        queue.offer(right);
        while (!queue.isEmpty()) {
            left = queue.poll();
            right = queue.poll();
            if (right == null && left == null)
                continue;
            if ((right == null || left == null) || (right.val != left.val))
                return false;
            queue.offer(left.left);
            queue.offer(right.right);
            queue.offer(left.right);
            queue.offer(right.left);
        }
        return true;
    }
}
