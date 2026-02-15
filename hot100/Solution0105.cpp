#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>
using namespace std;
// 给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

// 示例 1:

// 输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
// 输出: [3,9,20,null,null,15,7]
// 示例 2:

// 输入: preorder = [-1], inorder = [-1]
// 输出: [-1]

// 提示:

// 1 <= preorder.length <= 3000
// inorder.length == preorder.length
// -3000 <= preorder[i], inorder[i] <= 3000
// preorder 和 inorder 均 无重复 元素
// inorder 均出现在 preorder
// preorder 保证 为二叉树的前序遍历序列
// inorder 保证 为二叉树的中序遍历序列

// 方法一：使用二分法查找和递归
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
        if (!preorder.size() || !inorder.size() || preorder.size() != inorder.size())
            return nullptr;
        return recursiveBuildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

private:
    TreeNode *recursiveBuildTree(vector<int> &preorder, int pre_start, int pre_end, vector<int> &inorder, int in_start, int in_end)
    {
        if (pre_start > pre_end || in_start > in_end)
            return nullptr;
        int root_value = preorder[pre_start];
        TreeNode *root = new TreeNode(root_value);

        // 在中序遍历中找根节点位置
        auto root_pos = find(inorder.begin() + in_start, inorder.begin() + in_end + 1, root_value); // [a,b)
        int left_tree_size = distance(inorder.begin() + in_start, root_pos);                        // [a,b)的大小

        root->left = recursiveBuildTree(preorder, pre_start + 1, pre_start + left_tree_size, inorder, in_start, root_pos - inorder.begin() - 1);
        root->right = recursiveBuildTree(preorder, pre_start + left_tree_size + 1, pre_end, inorder, root_pos - inorder.begin() + 1, in_end);
    }
};

// 方法二：使用哈希加递归
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

    unordered_map<int, int> inorder_index_map; // 存储中序遍历值到索引的映射

public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        if (!preorder.size() || !inorder.size() || preorder.size() != inorder.size())
            return nullptr;

        for (int i = 0; i < inorder.size(); i++)
        {
            inorder_index_map[inorder[i]] = i;
        }
        return recursiveBuildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

private:
    TreeNode *recursiveBuildTree(vector<int> &preorder, int pre_start, int pre_end, vector<int> &inorder, int in_start, int in_end)
    {
        if (pre_start > pre_end || in_start > in_end)
            return nullptr;
        int root_value = preorder[pre_start];
        TreeNode *root = new TreeNode(root_value);

        // 在中序遍历中找根节点位置
        auto root_pos = inorder_index_map.find(root_value);
        int left_tree_size = root_pos->second - in_start;

        root->left = recursiveBuildTree(preorder, pre_start + 1, pre_start + left_tree_size, inorder, in_start, root_pos->second - 1);
        root->right = recursiveBuildTree(preorder, pre_start + left_tree_size + 1, pre_end, inorder, root_pos->second + 1, in_end);
        return root;
    }
};

// 方法三：迭代：看不懂，后续解决
class Solution3
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

    unordered_map<int, int> inorder_index_map; // 存储中序遍历值到索引的映射

public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        if (!preorder.size())
        {
            return nullptr;
        }
        TreeNode *root = new TreeNode(preorder[0]);
        stack<TreeNode *> stk;
        stk.push(root);
        int inorderIndex = 0;
        for (int i = 1; i < preorder.size(); ++i)
        {
            int preorderVal = preorder[i];
            TreeNode *node = stk.top();
            if (node->val != inorder[inorderIndex])
            {
                node->left = new TreeNode(preorderVal);
                stk.push(node->left);
            }
            else
            {
                while (!stk.empty() && stk.top()->val == inorder[inorderIndex])
                {
                    node = stk.top();
                    stk.pop();
                    ++inorderIndex;
                }
                node->right = new TreeNode(preorderVal);
                stk.push(node->right);
            }
        }
        return root;
    }
};