import java.util.*;

//给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 小的元素（k 从 1 开始计数）。

public class Solution0230 {
    public int kthSmallest(TreeNode root, int k) {
        int count = 0;
        int kthVal = 0;
        Deque<TreeNode> stack = new ArrayDeque<>();
        while (root != null || !stack.isEmpty()) {
            while (root != null) {
                stack.push(root);
                root = root.left;
            }
            root = stack.pop();
            if (++count == k) {
                kthVal = root.val;
                break;
            }
            root = root.right;
        }
        return kthVal;
    }

    public int kthSmallest2(TreeNode root, int k) {
        Map<TreeNode, Integer> map = new HashMap<>();
        count(root, map);
        while (root != null) {
            int left = map.getOrDefault(root.left, 0);
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

    private int count(TreeNode root, Map<TreeNode, Integer> map) {
        if (root == null) {
            return 0;
        }
        map.put(root, 1 + count(root.left, map) + count(root.right, map));
        return map.get(root);
    }
}
