import java.util.*;

//给你二叉树的根节点 root ，返回其节点值的 层序遍历 。 （即逐层地，从左到右访问所有节点）。

public class Solution0102 {
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

        System.out.println(levelOrder(root));
        System.out.println(levelOrder2(root));
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

    public static List<List<Integer>> levelOrder(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        bfs(root, 0, result);
        return result;
    }

    private static void bfs(TreeNode root, int depth, List<List<Integer>> result) {
        if (root == null) {
            return;
        }
        if (result.size() == depth) {
            result.add(new ArrayList<>());
        }
        result.get(depth).add(root.val);
        bfs(root.left, depth + 1, result);
        bfs(root.right, depth + 1, result);
    }

    public static List<List<Integer>> levelOrder2(TreeNode root) {
        List<List<Integer>> result = new LinkedList<>();
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        while (!queue.isEmpty()) {
            int size = queue.size();
            result.add(new ArrayList<>());
            while (size > 0) {
                TreeNode cur = queue.poll();
                result.get(result.size() - 1).add(cur.val);
                if (cur.left != null) queue.offer(cur.left);
                if (cur.right != null) queue.offer(cur.right);
                size--;
            }
        }
        return result;
    }
}
