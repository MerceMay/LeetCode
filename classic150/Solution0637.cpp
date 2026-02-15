#include <vector>
#include <queue>
#include <stack>
using namespace std;
// 给定一个非空二叉树的根节点 root , 以数组的形式返回每一层节点的平均值。与实际答案相差 10-5 以内的答案可以被接受。
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
    vector<double> averageOfLevels(TreeNode *root)
    {
        vector<double> result;
        if (!root)
            return result;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            double sum = 0;
            for (int i = 0; i < size; i++)
            {
                TreeNode *node = q.front();
                q.pop();
                sum += node->val;
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
            result.push_back(sum / size);
        }
        return result;
    }
};

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
    vector<double> averageOfLevels(TreeNode *root)
    {
        vector<double> result;
        vector<long long> sums;
        vector<int> counts;
        if (!root)
            return result;
        stack<pair<TreeNode *, int>> stk; // 栈存储节点和其所在层级
        stk.push({root, 0});
        while (!stk.empty())
        {
            auto [node, level] = stk.top();
            stk.pop();
            if (level == sums.size())
            {
                sums.push_back(node->val);
                counts.push_back(1);
            }
            else
            {
                sums[level] += node->val;
                counts[level]++;
            }
            if (node->right)
                stk.push({node->right, level + 1});
            if (node->left)
                stk.push({node->left, level + 1});
        }
        for (int i = 0; i < sums.size(); i++)
            result.push_back(static_cast<double>(sums[i]) / counts[i]);
        return result;
    }
};