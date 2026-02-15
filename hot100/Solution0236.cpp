#include <unordered_map>
#include <unordered_set>
using namespace std;
// 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

// 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

// 示例 1：

// 输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
// 输出：3
// 解释：节点 5 和节点 1 的最近公共祖先是节点 3 。
// 示例 2：

// 输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
// 输出：5
// 解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。
// 示例 3：

// 输入：root = [1,2], p = 1, q = 2
// 输出：1

// 提示：

// 树中节点数目在范围 [2, 105] 内。
// -109 <= Node.val <= 109
// 所有 Node.val 互不相同 。
// p != q
// p 和 q 均存在于给定的二叉树中。
class Solution
{
private:
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
    TreeNode *result;

public:
    // 使用后续遍历，每个子树返回信息，是否包含某个节点，
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        postOrderTraversal(root, p, q);
        return result;
    }

private:
    bool postOrderTraversal(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (!root)
            return false;

        bool left_tree_has = postOrderTraversal(root->left, p, q);
        bool right_tree_has = postOrderTraversal(root->right, p, q);

        // 如果左子树有结果，右子树有结果，root为公共祖先。
        // 如果根节点等于p或q，并且其子树中有结果，则root也是公共祖先。
        if ((left_tree_has && right_tree_has) ||
            ((root->val == p->val || root->val == q->val) && (left_tree_has || right_tree_has)))
            result = root;

        // 返回当前子树是否包含p或q
        return left_tree_has || right_tree_has || (root == p || root == q);
    }
};

// 方法二：
class Solution2
{
private:
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        // 如果root不存在，或者root本身就是p或q，则直接返回root
        if (!root || root == p || root == q)
            return root;

        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);

        // 情况一：如果左子树有结果，右子树有结果，root为公共祖先。
        if ((left && right))
            return root;

        // 情况二：子树只有一个有结果，返回结果。即从这里开始，往上走，只会返回有没有该节点的情况
        return left ? left : right;
    }
};

// 方法三：
class Solution3
{
private:
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    unordered_map<TreeNode *, TreeNode *> parent; // 记录每个节点的父节点
    unordered_set<TreeNode *> anscestor;          // 记录p的所有祖先节点
public:
    // 记录每个节点的父节点。然后分别找到p和q，然后p和q往上走，找到第一个相同的节点就是最近公共祖先。
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        parent[root] = nullptr; // 根节点没有父节点
        dfs(root);
        // 找到p的所有祖先节点
        while (p)
        {
            anscestor.insert(p);
            p = parent[p];
        }
        // 从q开始，找到第一个在p的祖先节点集合中的节点就是最近公共祖先
        while (q)
        {
            if (anscestor.count(q))
                return q;
            q = parent[q];
        }
        return nullptr;
    }

private:
    void dfs(TreeNode *node)
    {
        if (node->left)
        {
            parent[node->left] = node;
            dfs(node->left);
        }
        if (node->right)
        {
            parent[node->right] = node;
            dfs(node->right);
        }
    }
};
