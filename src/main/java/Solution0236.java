import java.util.*;

//给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
//
//百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

public class Solution0236 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int pVal = sc.nextInt();
        int qVal = sc.nextInt();
        String[] nodes = line.substring(1, line.length() - 1).split(",");
        TreeNode p = null, q = null;
        TreeNode root = new TreeNode(Integer.parseInt(nodes[0]));
        if (pVal == root.val) {
            p = root;
        }
        if (qVal == root.val) {
            q = root;
        }
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        int i = 1;
        while (i < nodes.length) {
            TreeNode cur = queue.poll();
            if (i < nodes.length && !nodes[i].equals("null")) {
                cur.left = new TreeNode(Integer.parseInt(nodes[i]));
                queue.offer(cur.left);

                if (pVal == cur.left.val) {
                    p = cur.left;
                }
                if (qVal == cur.left.val) {
                    q = cur.left;
                }
            }
            i++;
            if (i < nodes.length && !nodes[i].equals("null")) {
                cur.right = new TreeNode(Integer.parseInt(nodes[i]));
                queue.offer(cur.right);
                if (pVal == cur.right.val) {
                    p = cur.right;
                }
                if (qVal == cur.right.val) {
                    q = cur.right;
                }
            }
            i++;
        }
        TreeNode lca = lowestCommonAncestor(root, p, q);
        System.out.println(lca == null ? "null" : lca.val);
        lca = lowestCommonAncestor2(root, p, q);
        System.out.println(lca == null ? "null" : lca.val);
        lca = lowestCommonAncestor3(root, p, q);
        System.out.println(lca == null ? "null" : lca.val);
        lca = lowestCommonAncestor4(root, p, q);
        System.out.println(lca == null ? "null" : lca.val);
        lca = lowestCommonAncestor5(root, p, q);
        System.out.println(lca == null ? "null" : lca.val);
        lca = lowestCommonAncestor6(root, p, q);
        System.out.println(lca == null ? "null" : lca.val);
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

    private static TreeNode result;

    public static TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        dfs(root, p, q);
        return result;
    }

    private static boolean dfs(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null) {
            return false;
        }
        boolean lSon = dfs(root.left, p, q);
        boolean rSon = dfs(root.right, p, q);
        if ((lSon && rSon) || ((root == p || root == q) && (lSon || rSon))) {
            result = root;
        }
        return lSon || rSon || (root == p || root == q);
    }

    public static TreeNode lowestCommonAncestor2(TreeNode root, TreeNode p, TreeNode q) {
        TreeNode result = null;
        if (root == null) {
            return result;
        }
        Map<TreeNode, Boolean> son = new HashMap<>();
        record NodeVisited(TreeNode node, boolean visited) {
        }
        Deque<NodeVisited> stack = new LinkedList<>();
        stack.push(new NodeVisited(root, false));
        while (!stack.isEmpty() && result == null) {
            NodeVisited nv = stack.pop();
            TreeNode node = nv.node();
            boolean visited = nv.visited();
            if (!visited) {
                // 第一次遇见，不能处理，应该压回去，再压右左
                stack.push(new NodeVisited(node, true));
                if (node.right != null) {
                    stack.push(new NodeVisited(node.right, false));
                }
                if (node.left != null) {
                    stack.push(new NodeVisited(node.left, false));
                }
            } else {
                boolean lSon = node.left != null && son.get(node.left);
                boolean rSon = node.right != null && son.get(node.right);
                if ((lSon && rSon) || ((node == p || node == q) && (lSon || rSon))) {
                    result = node;
                }
                boolean isSon = lSon || rSon || node == p || node == q;
                son.put(node, isSon);
            }
        }
        return result;
    }

    public static TreeNode lowestCommonAncestor3(TreeNode root, TreeNode p, TreeNode q) {
        TreeNode result = null;
        if (root == null) {
            return result;
        }
        Map<TreeNode, Boolean> son = new HashMap<>();
        Deque<TreeNode> stack1 = new LinkedList<>();
        Deque<TreeNode> stack2 = new LinkedList<>();
        stack1.push(root);
        while (!stack1.isEmpty()) {
            TreeNode cur = stack1.pop();
            stack2.push(cur);
            if (cur.left != null) {
                stack1.push(cur.left);
            }
            if (cur.right != null) {
                stack1.push(cur.right);
            }
        }
        while (!stack2.isEmpty() && result == null) {
            TreeNode node = stack2.pop();

            boolean lSon = node.left != null && son.get(node.left);
            boolean rSon = node.right != null && son.get(node.right);
            if ((lSon && rSon) || ((lSon || rSon) && (node == p || node == q))) {
                result = node;
            }
            son.put(node, lSon || rSon || node == p || node == q);
        }
        return result;
    }

    public static TreeNode lowestCommonAncestor4(TreeNode root, TreeNode p, TreeNode q) {
        Set<TreeNode> visited = new HashSet<>();
        Map<TreeNode, TreeNode> parent = new HashMap<>();
        dfs(root, parent);
        while (p != null) {
            visited.add(p);
            p = parent.get(p);
        }
        while (q != null) {
            if (visited.contains(q)) {
                return q;
            }
            q = parent.get(q);
        }
        return null;
    }

    private static void dfs(TreeNode node, Map<TreeNode, TreeNode> parent) {
        if (node.left != null) {
            parent.put(node.left, node);
            dfs(node.left, parent);
        }
        if (node.right != null) {
            parent.put(node.right, node);
            dfs(node.right, parent);
        }
    }

    public static TreeNode lowestCommonAncestor5(TreeNode root, TreeNode p, TreeNode q) {
        Set<TreeNode> visited = new HashSet<>();
        Map<TreeNode, TreeNode> parent = new HashMap<>();
        Deque<TreeNode> stack = new LinkedList<>();
        stack.push(root);
        while (!stack.isEmpty()) {
            TreeNode cur = stack.pop();
            if (cur.left != null) {
                parent.put(cur.left, cur);
                stack.push(cur.left);
            }
            if (cur.right != null) {
                parent.put(cur.right, cur);
                stack.push(cur.right);
            }
        }
        while (p != null) {
            visited.add(p);
            p = parent.get(p);
        }
        while (q != null) {
            if (visited.contains(q)) {
                return q;
            }
            q = parent.get(q);
        }
        return null;
    }

    public static TreeNode lowestCommonAncestor6(TreeNode root, TreeNode p, TreeNode q) {
        if (root == null) {
            return null;
        }
        if (p == root || q == root) {
            return root;
        }
        TreeNode left = lowestCommonAncestor6(root.left, p, q);
        TreeNode right = lowestCommonAncestor6(root.right, p, q);
        if (left == null && right == null) {
            return null;
        }
        if (left == null) {
            return right;
        }
        if (right == null) {
            return left;
        }
        return root;
    }
}
