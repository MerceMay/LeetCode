#include <queue>
using namespace std;
// 给你一个二叉树的根节点 root ， 检查它是否轴对称。

// 示例 1：

// 输入：root = [1,2,2,3,4,4,3]
// 输出：true
// 示例 2：

// 输入：root = [1,2,2,null,3,null,3]
// 输出：false

// 提示：

// 树中节点数目在范围 [1, 1000] 内
// -100 <= Node.val <= 100

// 进阶：你可以运用递归和迭代两种方法解决这个问题吗？
// 方法一：递归。
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
    // 使用两根指针，分别指向左右子树的根节点。每次移动都相反，只要值相同就对
    bool isSymmetric(TreeNode *root)
    {
        if (root == nullptr)
            return true;
        return isSymmetric(root->left, root->right);
    }

private:
    bool isSymmetric(TreeNode *left, TreeNode *right)
    {
        if (left == nullptr && right == nullptr)
            return true;
        if (left == nullptr || right == nullptr)
            return false;
        return left->val == right->val && isSymmetric(left->left, right->right) && isSymmetric(left->right, right->left);
    }
};

// 方法二：迭代
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
    // 每次检验一对
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
            if (node1 == nullptr && node2 == nullptr)
                continue;
            if (node1 == nullptr || node2 == nullptr)
                return false;
            if (node1->val != node2->val)
                return false;
            q.push(node1->left);
            q.push(node2->right);
            q.push(node1->right);
            q.push(node2->left);
        }
        return true;
    }
};