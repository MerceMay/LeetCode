#include <vector>
#include <queue>
using namespace std;
// 给你二叉树的根节点 root ，返回其节点值的 层序遍历 。 （即逐层地，从左到右访问所有节点）。

// 示例 1：

// 输入：root = [3,9,20,null,null,15,7]
// 输出：[[3],[9,20],[15,7]]
// 示例 2：

// 输入：root = [1]
// 输出：[[1]]
// 示例 3：

// 输入：root = []
// 输出：[]

// 提示：

// 树中节点数目在范围 [0, 2000] 内
// -1000 <= Node.val <= 1000
// 方法一：深度优先搜索
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
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> result;
        levelOrderTraversal(root, 0, result);
        return result;
    }

private:
    void levelOrderTraversal(TreeNode *node, int level, vector<vector<int>> &result)
    {
        if (node == nullptr)
            return;
        if (result.size() == level)
        {
            result.push_back({});
        }
        result[level].push_back(node->val);
        levelOrderTraversal(node->left, level + 1, result);
        levelOrderTraversal(node->right, level + 1, result);
    }
};

// 方法二：广度优先遍历
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
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> result;
        if (root == nullptr)
            return result;
        queue<TreeNode *> queue;
        queue.push(root);
        while (!queue.empty())
        {
            int level_size = queue.size();
            vector<int> level_result;
            for (int i = 0; i < level_size; i++)
            {
                TreeNode *node = queue.front();
                queue.pop();
                level_result.push_back(node->val);
                if (node->left != nullptr)
                    queue.push(node->left);
                if (node->right != nullptr)
                    queue.push(node->right);
            }
            result.push_back(level_result);
        }
        return result;
    }
};