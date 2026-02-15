#include <queue>
using namespace std;
// 给你一棵 完全二叉树 的根节点 root ，求出该树的节点个数。

// 完全二叉树 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层（从第 0 层开始），则该层包含 1~ 2h 个节点。
// 进阶：遍历树来统计节点是一种时间复杂度为 O(n) 的简单解决方案。你可以设计一个更快的算法吗？
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
    int countNodes(TreeNode *root)
    {
        if (!root)
            return 0;
        queue<TreeNode *> q;
        q.push(root);
        int count = 0;
        while (!q.empty())
        {
            TreeNode *node = q.front();
            q.pop();
            count++;
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
        return count;
    }

    int countNodes2(TreeNode *root)
    {
        if (!root)
            return 0;
        int left_height = 0, right_height = 0;
        TreeNode *left = root, *right = root;
        while (left)
        {
            left_height++;
            left = left->left;
        }
        while (right)
        {
            right_height++;
            right = right->right;
        }
        // 如果左子树和右子树高度一样
        if (left_height == right_height)
            return (1 << left_height) - 1; // 2^h - 1

        // 如果左子树和右子树高度不一样。注意，完全二叉树，其左子树和右子树必有一个是满二叉树，因此，会立马停止迭代，另一个是完全二叉树
        // 因此时间复杂度为 O(log2 n* log2 n) // 第一个log2 n是指一共会进行 log2 n 次二分迭代。第二个log2 n是指数的高度为log2n
        return 1 + countNodes2(root->left) + countNodes2(root->right);
    }
};