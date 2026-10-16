import java.util.*;

//给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。
//
//有效 二叉搜索树定义如下：
//
//节点的左子树只包含 严格小于 当前节点的数。
//节点的右子树只包含 严格大于 当前节点的数。
//所有左子树和右子树自身必须也是二叉搜索树。

public class Solution0098 {
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

        System.out.println(isValidBST(root));
        System.out.println(isValidBST2(root));
        System.out.println(isValidBST3(root));
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

    public static boolean isValidBST(TreeNode root) {
        return recursiveCheck(root, Integer.MIN_VALUE, Integer.MAX_VALUE);
    }

    private static boolean recursiveCheck(TreeNode root, int min, int max) {
        if (root == null) {
            return true;
        }
        if (root.val <= min || root.val >= max) {
            return false;
        }
        return recursiveCheck(root.left, min, root.val) && recursiveCheck(root.right, root.val, max);
    }

    public static boolean isValidBST2(TreeNode root) {
        Deque<TreeNode> stack = new LinkedList<>();
        stack.push(root);
        while (!stack.isEmpty()) {
            TreeNode cur = stack.pop();
            int leftVal = cur.left == null ? Integer.MIN_VALUE : cur.left.val;
            int rightVal = cur.right == null ? Integer.MAX_VALUE : cur.right.val;
            if (cur.val <= leftVal || cur.val >= rightVal) {
                return false;
            }
            if (cur.left != null) {
                stack.push(cur.left);
            }
            if (cur.right != null) {
                stack.push(cur.right);
            }
        }
        return true;
    }

    public static boolean isValidBST3(TreeNode root) {
        Deque<TreeNode> stack = new LinkedList<>();
        long preVal = Long.MIN_VALUE;
        while (root != null || !stack.isEmpty()) {
            while (root != null) {
                stack.push(root);
                root = root.left;
            }
            root = stack.pop();
            if (root.val <= preVal) {
                return false;
            }
            preVal = root.val;
            root = root.right;
        }
        return true;
    }
}
