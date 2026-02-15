#include <algorithm>
using namespace std;
// 给你一棵二叉树的根节点，返回该树的 直径 。

// 二叉树的 直径 是指树中任意两个节点之间最长路径的 长度 。这条路径可能经过也可能不经过根节点 root 。

// 两节点之间路径的 长度 由它们之间边数表示。

// 示例 1：

// 输入：root = [1,2,3,4,5]
// 输出：3
// 解释：3 ，取路径 [4,2,1,3] 或 [5,2,1,3] 的长度。
// 示例 2：

// 输入：root = [1,2]
// 输出：1

// 提示：

// 树中节点数目在范围 [1, 104] 内
// -100 <= Node.val <= 100
// 深度：以根节点深度为0为起点，每向下一个节点深度加一
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

    int maxDiameter = 0;

public:
    int diameterOfBinaryTree(TreeNode *root)
    {
        maxDepth(root);
        return maxDiameter;
    }

private:
    int maxDepth(TreeNode *node)
    {
        if (node == nullptr)
            return 0;
        int leftDepth = maxDepth(node->left);
        int rightDepth = maxDepth(node->right);
        maxDiameter = max(maxDiameter, leftDepth + rightDepth); // 更新最大直径
        return max(leftDepth, rightDepth) + 1;                  // 返回当前节点的深度
    }
};