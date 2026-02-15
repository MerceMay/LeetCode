#include <vector>
#include <queue>
using namespace std;
// 给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。
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
    // 层序遍历改变，即根据奇偶层决定是是先压左节点还是先压右节点。
    // 根节点为第一层，奇数层从左往右，偶数层从右往左
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int>> result;
        if (!root)
            return result;
        queue<TreeNode *> q;
        q.push(root);
        bool LeftToRight = true;
        while (!q.empty())
        {
            int size = q.size();
            vector<int> level(size);
            for (int i = 0; i < size; i++)
            {
                TreeNode *node = q.front();
                q.pop();
                if (LeftToRight)
                    level[i] = node->val;
                else
                    level[size - 1 - i] = node->val;
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
            LeftToRight = !LeftToRight;
            result.push_back(level);
        }
        return result;
    }
};