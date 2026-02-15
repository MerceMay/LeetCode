#include <climits>
#include <stack>
using namespace std;
// 给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。

// 有效 二叉搜索树定义如下：

// 节点的左子树只包含 严格小于 当前节点的数。
// 节点的右子树只包含 严格大于 当前节点的数。
// 所有左子树和右子树自身必须也是二叉搜索树。

// 方法一：递归：需要注意，一个节点不仅要比较其左节点和右节点，还要确保其左子树和右子树
// 因此，需要子树传递其范围给父节点。因此需要一个辅助函数
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
    bool isValidBST(TreeNode *root)
    {
        return isValidBST(root, LONG_MIN, LONG_MAX);
    }

private:
    bool isValidBST(TreeNode *root, long minVal, long maxVal)
    {
        if (!root)
            return true;
        if (root->val <= minVal || root->val >= maxVal)
            return false;
        return isValidBST(root->left, minVal, root->val) && isValidBST(root->right, root->val, maxVal);
    }

public:
    bool isValidBST2(TreeNode *root)
    {
        if (!root)
            return true;
        stack<tuple<TreeNode *, long, long>> stk; // 节点，最小值，最大值
        stk.push(make_tuple(root, LONG_MIN, LONG_MAX));
        while (!stk.empty())
        {
            auto [node, minVal, maxVal] = stk.top();
            stk.pop();
            if (!node)
                continue;
            if (node->val <= minVal || node->val >= maxVal)
                return false;
            stk.push(make_tuple(node->left, minVal, node->val));
            stk.push(make_tuple(node->right, node->val, maxVal));
        }
        return true;
    }
};

// 方法二：二叉搜索树的中序遍历是一个递增的序列，因此只需要判断前一个节点是否小于当前节点
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
    long prev = LONG_MIN;

public:
    bool isValidBST(TreeNode *root)
    {
        return inorder(root);
    }

private:
    bool inorder(TreeNode *root)
    {
        if (!root)
            return true;
        if (!inorder(root->left))
            return false;
        if (root->val <= prev)
            return false;
        prev = root->val;
        return inorder(root->right);
    }

public:
    // 手动压栈
    bool isValidBST2(TreeNode *root)
    {
        if (!root)
            return true;
        stack<TreeNode *> stk;
        TreeNode *cur = root;
        long prev = LONG_MIN;
        while (cur || !stk.empty())
        {
            while (cur)
            {
                stk.push(cur);
                cur = cur->left;
            }
            cur = stk.top();
            stk.pop();
            if (cur->val <= prev)
                return false;
            prev = cur->val;
            cur = cur->right;
        }
        return true;
    }
};
