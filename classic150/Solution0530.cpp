#include <climits>
#include <algorithm>
using namespace std;
// 给你一个二叉搜索树的根节点 root ，返回 树中任意两不同节点值之间的最小差值 。

// 差值是一个正数，其数值等于两值之差的绝对值。
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
    int minDiff = INT_MAX;
    TreeNode *prev = nullptr;

public:
    // 分析：二叉搜索树，中序遍历是从小到大的，左中右，因此最小值是相邻两个节点的差值。
    // 遍历的时候只能读取当前节点的值，因此需要使用一个变量保存上一个节点的值
    int getMinimumDifference(TreeNode *root)
    {
        inorderTraversal(root);
        return minDiff;
    }

private:
    void inorderTraversal(TreeNode *root)
    {
        if (!root)
            return;
        inorderTraversal(root->left);
        if (prev)
            minDiff = min(minDiff, root->val - prev->val);
        prev = root;
        inorderTraversal(root->right);
    }
};