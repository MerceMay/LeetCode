#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
// 给定两个整数数组 inorder 和 postorder ，其中 inorder 是二叉树的中序遍历， postorder 是同一棵树的后序遍历，请你构造并返回这颗 二叉树 。

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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        return recursiveBuildTree(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }

private:
    TreeNode *recursiveBuildTree(vector<int> &inorder, int in_start, int in_end, vector<int> &postorder, int post_start, int post_end)
    {
        if (in_start > in_end || post_start > post_end)
            return nullptr;

        int root_val = postorder[post_end];
        TreeNode *root = new TreeNode(root_val);

        int root_pos = find(inorder.begin() + in_start, inorder.begin() + in_end + 1, root_val) - inorder.begin();
        int left_tree_size = root_pos - in_start;

        // 中序：左中右，因此为[start, root_pos -1]
        // 后续：左右中，因为为[start, post_start + left_tree_size - 1] -1是因为pos_start移动左树大小-1才是左树结尾
        root->left = recursiveBuildTree(inorder, in_start, root_pos - 1, postorder, post_start, post_start + left_tree_size - 1);
        root->right = recursiveBuildTree(inorder, root_pos + 1, in_end, postorder, post_start + left_tree_size, post_end - 1);

        return root;
    }
};

// 方法二：迭代，依旧看不懂
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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        if (postorder.size() == 0)
        {
            return nullptr;
        }
        auto root = new TreeNode(postorder[postorder.size() - 1]);
        auto s = stack<TreeNode *>();
        s.push(root);
        int inorderIndex = inorder.size() - 1;
        for (int i = int(postorder.size()) - 2; i >= 0; i--)
        {
            int postorderVal = postorder[i];
            auto node = s.top();
            if (node->val != inorder[inorderIndex])
            {
                node->right = new TreeNode(postorderVal);
                s.push(node->right);
            }
            else
            {
                while (!s.empty() && s.top()->val == inorder[inorderIndex])
                {
                    node = s.top();
                    s.pop();
                    inorderIndex--;
                }
                node->left = new TreeNode(postorderVal);
                s.push(node->left);
            }
        }
        return root;
    }
};