#include <queue>
using namespace std;
// 给你一个二叉树的根节点 root ，树中每个节点都存放有一个 0 到 9 之间的数字。
// 每条从根节点到叶节点的路径都代表一个数字：

// 例如，从根节点到叶节点的路径 1 -> 2 -> 3 表示数字 123 。
// 计算从根节点到叶节点生成的 所有数字之和 。

// 叶节点 是指没有子节点的节点。

// 示例 1：

// 输入：root = [1,2,3]
// 输出：25
// 解释：
// 从根到叶子节点路径 1->2 代表数字 12
// 从根到叶子节点路径 1->3 代表数字 13
// 因此，数字总和 = 12 + 13 = 25
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
    int sumNumbers(TreeNode *root)
    {
        return dfs(root, 0);
    }

private:
    int dfs(TreeNode *node, int sum)
    {
        if (!node)
            return 0;
        sum = sum * 10 + node->val;
        if (!node->left && !node->right)
            return sum;
        return dfs(node->left, sum) + dfs(node->right, sum);
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
    int sumNumbers(TreeNode *root)
    {
        if (!root)
            return 0;
        queue<pair<TreeNode, int>> q;
        q.push({*root, root->val});
        int result = 0;
        while (!q.empty())
        {
            auto [node, sum] = q.front();
            q.pop();
            if (!node.left && !node.right)
            {
                result += sum;
            }
            if (node.left)
            {
                q.push({*node.left, sum * 10 + node.left->val});
            }
            if (node.right)
            {
                q.push({*node.right, sum * 10 + node.right->val});
            }
        }
        return result;
    }
};