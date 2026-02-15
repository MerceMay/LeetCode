#include <vector>
#include <stack>
#include <queue>
using namespace std;
// 给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

// 示例 1：
// 输入：root = [1,2,3,null,5,null,4]
// 输出：[1,3,4]
// 解释：

// 示例 2：
// 输入：root = [1,2,3,4,null,null,null,5]
// 输出：[1,3,4,5]
// 解释：

// 示例 3：
// 输入：root = [1,null,3]
// 输出：[1,3]

// 示例 4：
// 输入：root = []
// 输出：[]

// 提示:
// 二叉树的节点个数的范围是 [0,100]
// -100 <= Node.val <= 100
// 深度优先遍历：递归版
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
    vector<int> rightSideView(TreeNode *root)
    {
        vector<int> rightest_result;
        rightSideView(root, rightest_result, 0);
        return rightest_result;
    }

private:
    void rightSideView(TreeNode *root, vector<int> &rightest_result, int level)
    {
        if (!root)
            return;
        if (rightest_result.size() == level) // 说明该层是第一次访问，只需要先访问右子树在访问左子树
            rightest_result.push_back(root->val);
        rightSideView(root->right, rightest_result, level + 1);
        rightSideView(root->left, rightest_result, level + 1);
    }
};

// 深度优先遍历：压栈版
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
    vector<int> rightSideView(TreeNode *root)
    {
        vector<int> result;
        if (root == nullptr)
            return result;
        std::stack<std::pair<TreeNode *, int>> stack; // 栈存储节点和其所在层级
        stack.push({root, 0});
        while (!stack.empty())
        {
            auto [node, level] = stack.top();
            stack.pop();
            if (result.size() == level) // 说明该层是第一次访问
                result.push_back(node->val);
            if (node->left)
                stack.push({node->left, level + 1});
            if (node->right)
                stack.push({node->right, level + 1});
        }
        return result;
    }
};

// 广度优先遍历
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

public:
    vector<int> rightSideView(TreeNode *root)
    {
        vector<int> result;
        if (root == nullptr)
            return result;
        std::queue<std::pair<TreeNode *, int>> queue; // 队列存储节点和其所在层级
        queue.push({root, 0});
        while (!queue.empty())
        {
            auto [node, level] = queue.front();
            queue.pop();
            if (result.size() == level) // 说明该层是第一次访问
                result.push_back(node->val);
            if (node->right)
                queue.push({node->right, level + 1});
            if (node->left)
                queue.push({node->left, level + 1});
        }
        return result;
    }
};