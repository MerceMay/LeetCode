import java.util.*;

public class Solution0437 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int targetSum = sc.nextInt();
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

        System.out.println(pathSum(root, targetSum));
        System.out.println(pathSum2(root, targetSum));
        System.out.println(pathSum3(root, targetSum));
        System.out.println(pathSum4(root, targetSum));
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

    public static int pathSum(TreeNode root, int targetSum) {
        if (root == null) {
            return 0;
        }
        return recursive(root, targetSum) + pathSum(root.left, targetSum) + pathSum(root.right, targetSum);
    }

    private static int recursive(TreeNode node, int targetSum) {
        if (node == null) {
            return 0;
        }
        int result = 0;
        result += node.val == targetSum ? 1 : 0;
        result += recursive(node.left, targetSum - node.val);
        result += recursive(node.right, targetSum - node.val);
        return result;
    }

    public static int pathSum2(TreeNode root, int targetSum) {
        int result = 0;
        Deque<TreeNode> stack = new LinkedList<>();
        stack.push(root);
        record NodeInfo(TreeNode node, long leftoverSum) {
        }
        while (!stack.isEmpty()) {
            TreeNode start = stack.pop();
            Deque<NodeInfo> pathStack = new LinkedList<>();
            pathStack.push(new NodeInfo(start, targetSum));
            while (!pathStack.isEmpty()) {
                NodeInfo ni = pathStack.pop();
                TreeNode cur = ni.node();
                long leftoverSum = ni.leftoverSum();
                if (leftoverSum == cur.val) {
                    result++;
                }
                if (cur.left != null) {
                    pathStack.push(new NodeInfo(cur.left, leftoverSum - cur.val));
                }
                if (cur.right != null) {
                    pathStack.push(new NodeInfo(cur.right, leftoverSum - cur.val));
                }
            }
            if (start.left != null) {
                stack.push(start.left);
            }
            if (start.right != null) {
                stack.push(start.right);
            }
        }
        return result;
    }

    public static int pathSum3(TreeNode root, int targetSum) {
        Map<Long, Integer> prefix = new HashMap<>();
        prefix.put(0L, 1);
        return dfs(root, targetSum, prefix, 0);
    }

    private static int dfs(TreeNode node, int targetSum, Map<Long, Integer> prefix, long currentSum) {
        if (node == null) {
            return 0;
        }
        int result = 0;
        currentSum += node.val;
        result += prefix.getOrDefault(currentSum - targetSum, 0);
        prefix.put(currentSum, prefix.getOrDefault(currentSum, 0) + 1);
        result += dfs(node.left, targetSum, prefix, currentSum);
        result += dfs(node.right, targetSum, prefix, currentSum);
        prefix.put(currentSum, prefix.getOrDefault(currentSum, 0) - 1);
        return result;
    }

    public static int pathSum4(TreeNode root, int targetSum) {
        Map<Long, Integer> prefix = new HashMap<>();
        prefix.put(0L, 1);
        record NodeCurSum(TreeNode node, long currentSum, boolean exit) {
        }
        Deque<NodeCurSum> stack = new LinkedList<>();
        stack.push(new NodeCurSum(root, 0L, false));
        int result = 0;
        while (!stack.isEmpty()) {
            NodeCurSum ncs = stack.pop();
            TreeNode cur = ncs.node();
            long currentSum = ncs.currentSum();
            boolean exit = ncs.exit();
            if (exit == true) {
                prefix.put(currentSum, prefix.getOrDefault(currentSum, 0) - 1);
                continue;
            }
            currentSum += cur.val;
            result += prefix.getOrDefault(currentSum - targetSum, 0);
            prefix.put(currentSum, prefix.getOrDefault(currentSum, 0) + 1);
            // 左 右 出
            stack.push(new NodeCurSum(cur, currentSum, true));
            if (cur.right != null) {
                stack.push(new NodeCurSum(cur.right, currentSum, false));
            }
            if (cur.left != null) {
                stack.push(new NodeCurSum(cur.left, currentSum, false));
            }
        }
        return result;
    }
}
