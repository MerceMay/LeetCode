import java.util.*;

//给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 小的元素（k 从 1 开始计数）。

public class Solution0230 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int k = sc.nextInt();
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

        System.out.println(kthSmallest(root, k));
        System.out.println(kthSmallest2(root, k));
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

    public static int kthSmallest(TreeNode root, int k) {
        int count = 0;
        int kthVal = 0;
        Deque<TreeNode> stack = new LinkedList<>();
        while (root != null || !stack.isEmpty()) {
            while (root != null) {
                stack.push(root);
                root = root.left;
            }
            root = stack.pop();
            if (++count == k) {
                kthVal = root.val;
            }
            root = root.right;
        }
        return kthVal;
    }


    public static int kthSmallest2(TreeNode root, int k) {
        Map<TreeNode, Integer> nodeNum = new HashMap<>();
        countNodeNum(root, nodeNum);

        while (root != null) {
            int left = nodeNum.getOrDefault(root.left, 0);
            if (left < k - 1) {
                root = root.right;
                k -= left + 1;
            } else if (left > k - 1) {
                root = root.left;
            } else {
                break;
            }
        }
        return root.val;
    }

    private static int countNodeNum(TreeNode root, Map<TreeNode, Integer> nodeNum) {
        if (root == null) {
            return 0;
        }
        nodeNum.put(root, 1 + countNodeNum(root.left, nodeNum) + countNodeNum(root.right, nodeNum));
        return nodeNum.get(root);
    }
}
