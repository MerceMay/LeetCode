#include <climits>
#include <algorithm>
using namespace std;
// 二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。

// 路径和 是路径中各节点值的总和。

// 给你一个二叉树的根节点 root ，返回其 最大路径和 。
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

private:
    int max_sum = INT_MIN;

public:
    int maxPathSum(TreeNode *root)
    {
        dfs(root);
        return max_sum;
    }

private:
    int dfs(TreeNode *node)
    {
        if (!node)
            return 0;

        // 计算左右作为路径的最大值，注意，路径拐弯点为当前节点不是子节点。子节点可以经过，也可以不经过
        int left_max = max(0, dfs(node->left));
        int right_max = max(0, dfs(node->right));
        max_sum = max(max_sum, left_max + right_max + node->val); // 计算当前节点为拐点
        return max(left_max, right_max) + node->val; // 返回给父节点其作为路径经过点的最大值
    }
};