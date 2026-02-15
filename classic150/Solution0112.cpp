#include <stack>
using namespace std;
// 给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。如果存在，返回 true ；否则，返回 false 。

// 叶子节点 是指没有子节点的节点。

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
    bool hasPathSum(TreeNode *root, int targetSum)
    {
        if (!root)
            return false;
        if (!root->left && !root->right)
            return root->val == targetSum;
        targetSum -= root->val;
        return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);
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
    bool hasPathSum(TreeNode *root, int targetSum)
    {
        if (!root)
            return false;
        stack<pair<TreeNode *, int>> stk;
        stk.push({root, targetSum - root->val});
        while (!stk.empty())
        {
            auto [node, currSum] = stk.top();
            stk.pop();
            if (!node->left && !node->right && currSum == 0)
                return true;
            if (node->left)
                stk.push({node->left, currSum - node->left->val});
            if (node->right)
                stk.push({node->right, currSum - node->right->val});
        }
        return false;
    }
};