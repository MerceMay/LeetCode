import java.util.*;

//给你二叉树的根结点 root ，请你将它展开为一个单链表：
//
//展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
//展开后的单链表应该与二叉树 先序遍历 顺序相同。

public class Solution0114 {
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

        flatten(root);
        printTree(root);
    }

    private static void printTree(TreeNode root) {
        Queue<TreeNode> queue = new LinkedList<>();
        List<String> result = new ArrayList<>();
        queue.offer(root);
        while (!queue.isEmpty()) {
            TreeNode cur = queue.poll();
            if (cur == null) {
                result.add("null");
            } else {
                result.add(String.valueOf(cur.val));
                queue.offer(cur.left);
                queue.offer(cur.right);
            }
        }
        while (!result.isEmpty() && result.get(result.size() - 1).equals("null")) {
            result.remove(result.size() - 1);
        }
        System.out.println("[" + String.join(",", result) + "]");
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

    public static void flatten(TreeNode root) {
        while (root != null) {
            if (root.left == null) {
                root = root.right;
            } else {
                TreeNode predecessor = root.left;
                while (predecessor.right != null) {
                    predecessor = predecessor.right;
                }
                predecessor.right = root.right;
                root.right = root.left;
                root.left = null;
            }
        }
    }

    // 前序：中左右，pre记录左，这样遍历到自己的时候左树不会再影响自己
    public static void flatten2(TreeNode root) {
        Deque<TreeNode> stack = new LinkedList<>();
        stack.push(root);
        TreeNode pre = null;
        while (!stack.isEmpty()) {
            root = stack.pop();
            if (pre != null) {
                pre.right = root;
                pre.left = null;
            }
            if (root.right != null) {
                stack.push(root.right);
            }
            if (root.left != null) {
                stack.push(root.left);
            }
            pre = root;
        }
    }
}
