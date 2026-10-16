import java.util.*;

//给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。

public class Solution0226 {
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

        queue.clear();
        TreeNode newRoot = invertTree(root);
        queue.offer(newRoot);
        System.out.print("[");
        while (!queue.isEmpty()) {
            newRoot = queue.poll();
            System.out.print(newRoot.val);
            if (newRoot.left != null) {
                queue.offer(newRoot.left);
            }
            if (newRoot.right != null) {
                queue.offer(newRoot.right);
            }
            if (!queue.isEmpty()) {
                System.out.print(",");
            }
        }
        System.out.println("]");

        newRoot = invertTree2(root);
        queue.offer(newRoot);
        System.out.print("[");
        while (!queue.isEmpty()) {
            newRoot = queue.poll();
            System.out.print(newRoot.val);
            if (newRoot.left != null) {
                queue.offer(newRoot.left);
            }
            if (newRoot.right != null) {
                queue.offer(newRoot.right);
            }
            if (!queue.isEmpty()) {
                System.out.print(",");
            }
        }
        System.out.println("]");

        newRoot = invertTree3(root);
        queue.offer(newRoot);
        System.out.print("[");
        while (!queue.isEmpty()) {
            newRoot = queue.poll();
            System.out.print(newRoot.val);
            if (newRoot.left != null) {
                queue.offer(newRoot.left);
            }
            if (newRoot.right != null) {
                queue.offer(newRoot.right);
            }
            if (!queue.isEmpty()) {
                System.out.print(",");
            }
        }
        System.out.println("]");
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

    public static TreeNode invertTree(TreeNode root) {
        if (root == null) {
            return null;
        }
        TreeNode temp = root.left;
        root.left = invertTree(root.right);
        root.right = invertTree(temp);
        return root;
    }

    public static TreeNode invertTree2(TreeNode root) {
        if (root == null) {
            return null;
        }
        Deque<TreeNode> stack = new LinkedList<>();
        stack.push(root);
        while (!stack.isEmpty()) {
            TreeNode cur = stack.pop();
            TreeNode temp = cur.left;
            cur.left = cur.right;
            cur.right = temp;
            if (cur.left != null) {
                stack.push(cur.left);
            }
            if (cur.right != null) {
                stack.push(cur.right);
            }
        }
        return root;
    }

    public static TreeNode invertTree3(TreeNode root) {
        if (root == null) {
            return null;
        }
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        while (!queue.isEmpty()) {
            TreeNode cur = queue.poll();
            TreeNode temp = cur.left;
            cur.left = cur.right;
            cur.right = temp;
            if (cur.left != null) {
                queue.offer(cur.left);
            }
            if (cur.right != null) {
                queue.offer(cur.right);
            }
        }
        return root;
    }
}
