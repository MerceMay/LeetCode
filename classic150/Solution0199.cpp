#include <vector>
#include <queue>
#include <stack>
using namespace std;
// 给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
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
    // 使用层次遍历，但是压入节点的时候先压入右节点，这样可以保证先遍历到右侧节点
    vector<int> rightSideView(TreeNode *root)
    {
        vector<int> result;
        if (!root)
            return result;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                TreeNode *node = q.front();
                q.pop();
                if (i == 0) // 第一个访问就是右侧可见节点
                    result.push_back(node->val);
                if (node->right)
                    q.push(node->right);
                if (node->left)
                    q.push(node->left);
            }
        }
        return result;
    }

    // 直接存储每个节点所在层
    vector<int> rightSideView2(TreeNode *root)
    {
        vector<int> result;
        if (!root)
            return result;
        queue<pair<TreeNode *, int>> q; // 存储节点和所在层级
        q.push({root, 0});
        while (!q.empty())
        {
            int size = q.size();
            while (size--)
            {
                auto [node, level] = q.front();
                q.pop();
                if (level == result.size())
                    result.push_back(node->val);
                if (node->right)
                    q.push({node->right, level + 1});
                if (node->left)
                    q.push({node->left, level + 1});
            }
        }
        return result;
    }
};

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
    // 使用深度优先遍历
    vector<int> rightSideView(TreeNode *root)
    {
        vector<int> result;
        dfs(root, 0, result);
        return result;
    }

private:
    void dfs(TreeNode *node, int level, vector<int> &result)
    {
        if (!node)
            return;
        if (level == result.size()) // 说明该层是第一次访问
            result.push_back(node->val);
        dfs(node->right, level + 1, result);
        dfs(node->left, level + 1, result);
    }

public:
    vector<int> rightSideView(TreeNode *root)
    {
        vector<int> result;
        stack<pair<TreeNode *, int>> stk; // 栈存储节点和其所在层级
        stk.push({root, 0});
        while (!stk.empty())
        {
            auto [node, level] = stk.top();
            stk.pop();
            if (level == result.size())
                result.push_back(node->val);
            if (node->right)
                stk.push({node->right, level + 1});
            if (node->left)
                stk.push({node->left, level + 1});
        }
        return result;
    }
};