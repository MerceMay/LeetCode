#include <algorithm>
#include <climits>
using namespace std;
// 二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。

// 路径和 是路径中各节点值的总和。

// 给你一个二叉树的根节点 root ，返回其 最大路径和 。

// 示例 1：

// 输入：root = [1,2,3]
// 输出：6
// 解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
// 示例 2：

// 输入：root = [-10,9,20,null,null,15,7]
// 输出：42
// 解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42

// 提示：

// 树中节点数目范围是 [1, 3 * 104]
// -1000 <= Node.val <= 1000
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
    // 一个递归函数，helper(node)，它应该返回什么？它应该返回从 node 向下延伸的、只能单向走的最大路径和。这个返回值可以参与父节点的路径计算。
    int helper(TreeNode *node)
    {
        if (!node)
            return 0;

        // 计算左右子树的最大路径和。子树要么经过，要么不经过为0
        int left = max(helper(node->left), 0);
        int right = max(helper(node->right), 0);

        // 更新全局最大路径和
        max_sum = max(max_sum, left + right + node->val);

        // 返回从当前节点向下延伸的最大路径和
        return max(left, right) + node->val;
    }

public:
    int maxPathSum(TreeNode *root)
    {
        helper(root);
        return max_sum;
    }
};