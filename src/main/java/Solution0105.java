import java.util.*;

//给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

public class Solution0105 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line1 = sc.nextLine();
        String line2 = sc.nextLine();
        int[] preorder = Arrays.stream(line1.substring(1, line1.length() - 1).split(","))
                .mapToInt(Integer::parseInt)
                .toArray();
        int[] inorder = Arrays.stream(line2.substring(1, line2.length() - 1).split(","))
                .mapToInt(Integer::parseInt)
                .toArray();
        TreeNode root = buildTree(preorder, inorder);
        printTree(root);
        root = buildTree2(preorder, inorder);
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

    private static final Map<Integer, Integer> nodeMap = new HashMap<>();

    public static TreeNode buildTree(int[] preorder, int[] inorder) {
        for (int i = 0; i < inorder.length; i++) {
            nodeMap.put(inorder[i], i);
        }
        return buildTree(preorder, 0, preorder.length - 1, inorder, 0, inorder.length - 1);
    }

    private static TreeNode buildTree(int[] preorder, int preLeft, int preRight, int[] inorder, int inLeft, int inRight) {
        if (preLeft > preRight || inLeft > inRight) {
            return null;
        }
        int rootVal = preorder[preLeft];
        TreeNode root = new TreeNode(rootVal);
        int rootIndexInInorder = nodeMap.get(rootVal);
        int leftTreeSize = rootIndexInInorder - inLeft;
        root.left = buildTree(preorder, preLeft + 1, preLeft + leftTreeSize, inorder, inLeft, rootIndexInInorder - 1);
        root.right = buildTree(preorder, preLeft + leftTreeSize + 1, preRight, inorder, rootIndexInInorder + 1, inRight);
        return root;
    }

    public static TreeNode buildTree2(int[] preorder, int[] inorder) {
        if (preorder == null || preorder.length == 0) {
            return null;
        }
        TreeNode root = new TreeNode(preorder[0]);
        Deque<TreeNode> stack = new LinkedList<>();
        stack.push(root);
        int inorderIndex = 0;
        for (int i = 1; i < preorder.length; i++) {
            int preOrderVal = preorder[i];
            TreeNode node = stack.peek();
            if (node.val != inorder[inorderIndex]) {
                node.left = new TreeNode(preOrderVal);
                stack.push(node.left);
            } else {
                while (!stack.isEmpty() && stack.peek().val == inorder[inorderIndex]) {
                    node = stack.pop();
                    inorderIndex++;
                }
                node.right = new TreeNode(preOrderVal);
                stack.push(node.right);
            }
        }
        return root;
    }
}
