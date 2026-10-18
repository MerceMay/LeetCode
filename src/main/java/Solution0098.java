import java.util.*;

//给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。
//
//有效 二叉搜索树定义如下：
//
//节点的左子树只包含 严格小于 当前节点的数。
//节点的右子树只包含 严格大于 当前节点的数。
//所有左子树和右子树自身必须也是二叉搜索树。

public class Solution0098 {
    public boolean isValidBST(TreeNode root) {
        return recursive(root, Integer.MIN_VALUE, Integer.MAX_VALUE);
    }

    private boolean recursive(TreeNode root, int min, int max) {
        if (root == null) {
            return true;
        }
        if (root.val <= min || root.val >= max) {
            return false;
        }
        return recursive(root.left, min, root.val) && recursive(root.right, root.val, max);
    }

    public boolean isValidBST2(TreeNode root) {
        Deque<TreeNode> stack = new ArrayDeque<>();
        TreeNode cur = root;
        long prev = Long.MIN_VALUE;
        while (cur != null || !stack.isEmpty()) {
            while (cur != null) {
                stack.push(cur);
                cur = cur.left;
            }
            cur = stack.pop();
            if (cur.val <= prev) {
                return false;
            }
            prev = cur.val;
            cur = cur.right;
        }
        return true;
    }
}
