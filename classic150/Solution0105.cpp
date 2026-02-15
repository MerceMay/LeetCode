#include <vector>
#include <algorithm>
using namespace std;
// 给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。
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
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        return recursiveBuildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

private:
    TreeNode *recursiveBuildTree(vector<int> &preorder, int pre_start, int pre_end, vector<int> &inorder, int in_start, int in_end)
    {
        if (pre_start > pre_end || in_start > in_end)
            return nullptr;
        int root_val = preorder[pre_start];
        TreeNode *root = new TreeNode(root_val);

        auto root_pos = find(inorder.begin() + in_start, inorder.begin() + in_end + 1, root_val);
        int left_tree_size = root_pos - inorder.begin() - in_start;

        root->left = recursiveBuildTree(preorder, pre_start + 1, pre_start + left_tree_size, inorder, in_start, in_start + left_tree_size - 1);
        root->right = recursiveBuildTree(preorder, pre_start + left_tree_size + 1, pre_end, inorder, in_start + left_tree_size + 1, in_end);
        return root;
    }
};