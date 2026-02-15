#include <queue>
using namespace std;
// 给你一个二叉树的根节点 root ， 检查它是否轴对称。

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
    bool isSymmetric(TreeNode *root)
    {
        if (!root)
            return true;
        return dfs(root->left, root->right);
    }

private:
    bool dfs(TreeNode *left, TreeNode *right)
    {
        if (!left && !right)
            return true;
        if (!left || !right)
            return false;
        return left->val == right->val && dfs(left->left, right->right) && dfs(left->right, right->left);
    }
};

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
    bool isSymmetric(TreeNode *root)
    {
        queue<TreeNode *> q;
        q.push(root), q.push(root);
        while (!q.empty())
        {
            TreeNode *node1 = q.front();
            q.pop();
            TreeNode *node2 = q.front();
            q.pop();
            if (!node1 && !node2)
                continue;
            if (!node1 || !node2)
                return false;
            if (node1->val != node2->val)
                return false;
            // node1往左做一步，node2往右走一步
            q.push(node1->left);
            q.push(node2->right);

            // node1往右走一步，node2往左走一步
            q.push(node1->right);
            q.push(node2->left);
        }
        return true;
    }
};