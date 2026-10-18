import com.sun.source.tree.Tree;

import java.util.*;

//给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。

public class Solution0094 {
    public static List<Integer> preorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        Deque<TreeNode> stack = new LinkedList<>();
        stack.push(root);
        while (!stack.isEmpty()) {
            root = stack.pop();
            result.add(root.val);
            if (root.right != null) {
                stack.push(root.right);
            }
            if (root.left != null) {
                stack.push(root.left);
            }
        }
        return result;
    }

    public static List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        Deque<TreeNode> stack = new LinkedList<>();
        while (root != null || !stack.isEmpty()) {
            while (root != null) {
                stack.push(root);
                root = root.left;
            }
            root = stack.pop();
            result.add(root.val);
            root = root.right;
        }
        return result;
    }

    public static List<Integer> postorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        Deque<TreeNode> stack1 = new LinkedList<>();
        Deque<TreeNode> stack2 = new LinkedList<>();
        stack1.push(root);
        while (!stack1.isEmpty()) {
            root = stack1.pop();
            stack2.push(root);
            if (root.left != null) {
                stack1.push(root.left);
            }
            if (root.right != null) {
                stack1.push(root.right);
            }
        }
        while (!stack2.isEmpty()) {
            result.add(stack2.pop().val);
        }
        return result;
    }

    public static List<Integer> levelOrderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        if (root == null) {
            return result;
        }
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        while (!queue.isEmpty()) {
            root = queue.poll();
            result.add(root.val);
            if (root.left != null) {
                queue.offer(root.left);
            }
            if (root.right != null) {
                queue.offer(root.right);
            }
        }
        return result;
    }


    public static List<Integer> recursivePreorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        recursivePreorderTraversal(root, result);
        return result;
    }

    private static void recursivePreorderTraversal(TreeNode root, List<Integer> result) {
        if (root == null) {
            return;
        }
        result.add(root.val);
        recursivePreorderTraversal(root.left, result);
        recursivePreorderTraversal(root.right, result);
    }

    public static List<Integer> recursiveInorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        recursiveInorderTraversal(root, result);
        return result;
    }

    private static void recursiveInorderTraversal(TreeNode root, List<Integer> result) {
        if (root == null) {
            return;
        }
        recursiveInorderTraversal(root.left, result);
        result.add(root.val);
        recursiveInorderTraversal(root.right, result);
    }

    public static List<Integer> recursivePostorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        recursivePostorderTraversal(root, result);
        return result;
    }

    private static void recursivePostorderTraversal(TreeNode root, List<Integer> result) {
        if (root == null) {
            return;
        }
        recursivePostorderTraversal(root.left, result);
        recursivePostorderTraversal(root.right, result);
        result.add(root.val);
    }

    public static List<Integer> recursiveLevelOrderTraversal(TreeNode root) {
        List<List<Integer>> levels = new ArrayList<>();
        recursiveLevelOrderTraversal(root, 0, levels);
        List<Integer> result = new ArrayList<>();
        for (List<Integer> level : levels) {
            result.addAll(level);
        }
        return result;
    }

    private static void recursiveLevelOrderTraversal(TreeNode root, int depth, List<List<Integer>> levels) {
        if (root == null) {
            return;
        }
        if (levels.size() == depth) {
            levels.add(new ArrayList<>());
        }
        levels.get(depth).add(root.val);
        recursiveLevelOrderTraversal(root.left, depth + 1, levels);
        recursiveLevelOrderTraversal(root.right, depth + 1, levels);
    }

    public static List<Integer> morrisPreorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        TreeNode cur = root;
        while (cur != null) {
            if (cur.left == null) { // 没有左子树，只会被访问一次
                result.add(cur.val);
                cur = cur.right;
            } else {
                TreeNode predecessor = cur.left;
                while (predecessor.right != null && predecessor.right != cur) {
                    predecessor = predecessor.right;
                }
                if (predecessor.right == null) { // 第一次访问
                    predecessor.right = cur;
                    result.add(cur.val);
                    cur = cur.left;
                } else { // 第二次访问
                    predecessor.right = null;
                    cur = cur.right;
                }
            }
        }
        return result;
    }


    public static List<Integer> morrisInorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        TreeNode cur = root;
        while (cur != null) {
            if (cur.left == null) {
                result.add(cur.val);
                cur = cur.right;
            } else {
                TreeNode predecessor = cur.left;
                while (predecessor.right != null && predecessor.right != cur) {
                    predecessor = predecessor.right;
                }
                if (predecessor.right == null) {
                    predecessor.right = cur;
                    cur = cur.left;
                } else {
                    predecessor.right = null;
                    result.add(cur.val);
                    cur = cur.right;
                }
            }
        }
        return result;
    }

    public static List<Integer> morrisPostorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        TreeNode cur = root;
        while (cur != null) {
            if (cur.left == null) {
                cur = cur.right;
            } else {
                TreeNode predecessor = cur.left;
                while (predecessor.right != null && predecessor.right != cur) {
                    predecessor = predecessor.right;
                }
                if (predecessor.right == null) {
                    predecessor.right = cur;
                    cur = cur.left;
                } else {
                    predecessor.right = null;
                    printRightBoundary(cur.left, result);
                    cur = cur.right;
                }
            }
        }
        // 也可以在一开始使用dummy来节省一次打印最右边界
        // TreeNode dummy = new TreeNode(0);
        // dummy.left = root;
        printRightBoundary(root, result);
        return result;
    }

    private static void printRightBoundary(TreeNode root, List<Integer> result) {
        TreeNode tail = reverseEdge(root);
        TreeNode cur = tail;
        while (cur != null) {
            result.add(cur.val);
            cur = cur.right;
        }
        reverseEdge(tail);
    }

    private static TreeNode reverseEdge(TreeNode root) {
        TreeNode pre = null, next = null;
        while (root != null) {
            next = root.right;
            root.right = pre;
            pre = root;
            root = next;
        }
        return pre;
    }

}
