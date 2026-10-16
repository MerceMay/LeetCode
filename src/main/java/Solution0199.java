import java.util.*;

//给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

public class Solution0199 {
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

        System.out.println(rightSideView(root));
        System.out.println(rightSideView2(root));
        System.out.println(rightSideView3(root));
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

    public static List<Integer> rightSideView(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            result.add(queue.peek().val);
            while (levelSize-- > 0) {
                root = queue.poll();
                if (root.right != null) {
                    queue.offer(root.right);
                }
                if (root.left != null) {
                    queue.offer((root.left));
                }
            }
        }
        return result;
    }

    public static List<Integer> rightSideView2(TreeNode root) {
        Map<Integer, Integer> levelFirstMeet = new HashMap<>();
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        record NodeDepth(TreeNode node, int depth) {
        }
        Deque<NodeDepth> stack = new LinkedList<>();
        stack.push(new NodeDepth(root, 0));
        while (!stack.isEmpty()) {
            NodeDepth nd = stack.poll();
            root = nd.node();
            int depth = nd.depth();
            levelFirstMeet.putIfAbsent(depth, root.val);
            if (root.left != null) {
                stack.push(new NodeDepth(root.left, depth + 1));
            }
            if (root.right != null) {
                stack.push(new NodeDepth(root.right, depth + 1));
            }
        }
        result = new ArrayList<>(levelFirstMeet.values());
        return result;
    }

    public static List<Integer> rightSideView3(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        record NodeDepth(TreeNode node, int depth) {
        }
        Deque<NodeDepth> stack = new LinkedList<>();
        stack.push(new NodeDepth(root, 0));
        while (!stack.isEmpty()) {
            NodeDepth nd = stack.poll();
            root = nd.node();
            int depth = nd.depth();
            if (depth == result.size()) {
                result.add(root.val);
            }
            if (root.left != null) {
                stack.push(new NodeDepth(root.left, depth + 1));
            }
            if (root.right != null) {
                stack.push(new NodeDepth(root.right, depth + 1));
            }
        }
        return result;
    }
}
