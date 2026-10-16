import java.util.*;

//给你一个整数数组 nums ，其中元素已经按 升序 排列，请你将其转换为一棵 平衡 二叉搜索树。

public class Solution0108 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int[] nums = Arrays.stream(line.substring(1, line.length() - 1).split(","))
                .mapToInt(Integer::parseInt)
                .toArray();
        TreeNode root = sortedArrayToBST(nums);
        printTree(root);

        root = sortedArrayToBST2(nums);
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

    public static TreeNode sortedArrayToBST(int[] nums) {
        if (nums == null || nums.length == 0) {
            return null;
        }
        return buildTree(nums, 0, nums.length - 1);
    }

    private static TreeNode buildTree(int[] nums, int left, int right) {
        if (left > right) {
            return null;
        }
        int mid = left + ((right - left) >> 1);
        TreeNode root = new TreeNode(nums[mid]);
        root.left = buildTree(nums, left, mid - 1);
        root.right = buildTree(nums, mid + 1, right);
        return root;
    }

    public static TreeNode sortedArrayToBST2(int[] nums) {
        if (nums == null || nums.length == 0) {
            return null;
        }
        record NodeIndex(TreeNode node, int left, int right) {
        }
        int rootIndex = (nums.length - 1) >> 1;
        TreeNode root = new TreeNode(nums[rootIndex]);

        Deque<NodeIndex> stack = new LinkedList<>();
        stack.push(new NodeIndex(root, 0, nums.length - 1));

        while (!stack.isEmpty()) {
            NodeIndex ni = stack.poll();
            TreeNode cur = ni.node();
            int left = ni.left();
            int right = ni.right();

            int mid = left + ((right - left) >> 1);

            if (left <= mid - 1) {
                int leftMid = left + ((mid - 1 - left) >> 1);
                cur.left = new TreeNode(nums[leftMid]);
                stack.push(new NodeIndex(cur.left, left, mid - 1));
            }

            if (mid + 1 <= right) {
                int rightMid = mid + 1 + ((right - (mid + 1)) >> 1);
                cur.right = new TreeNode(nums[rightMid]);
                stack.push(new NodeIndex(cur.right, mid + 1, right));
            }
        }
        return root;
    }
}
