#include <unordered_map>
#include <unordered_set>
using namespace std;
// 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

// 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
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
    // 遍历到当前节点时，需要直到左子树和右子树是否含有 p 和 q，因此使用后续遍历
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

        // 情况一：如果左子树有结果，右子树有结果，root为公共祖先。
        // 情况二：如果root等于p或q，并且其子树中有结果，又因为p和q不相同，则root也是公共祖先。
        if ((left_tree_has && right_tree_has) || ((root == p || root == q) && (left_tree_has || right_tree_has)))
            return result = root, true;

        // 需要给父节点返回该节点中还不含有结果
        return left_tree_has || right_tree_has || root == p || root == q;
    }
};

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

public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        // 递归，如果root为数有结果，返回结果，如果没有结果，返回nullpter
        // 如果root不存在，或者root本身就是p或q，则直接返回root
        if (!root || root == p || root == q)
            return root;

        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);

        // 如果左右子树都有结果，则root为公共祖先
        if (left && right)
            return root;

        // 剩下两种情况，一：只有一个有结果，返回；二：两个都没结果，返回nullptr
        return left ? left : right;
    }
};

// 方法三：分别从p和q往上走，找到第一个相同的节点。相当于拉拉链
// 因此我们需要首先直到每个节点的父节点是谁：使用哈希表
// 其次，使用一个集合来存储p的所有祖先节点，之后再让q往上走，找到第一个在p的祖先节点集合中的节点
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
    unordered_map<TreeNode *, TreeNode *> parent;
    unordered_set<TreeNode *> path;

public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        parent[root] = nullptr;
        dfs(root);
        while (p)
        {
            path.insert(p);
            p = parent[p];
        }

        while(q)
        {
            if (path.count(q))
                return q;
            q = parent[q];
        }
        return nullptr;
    }

private:
    void dfs(TreeNode *node)
    {
        if (!node)
            return;
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