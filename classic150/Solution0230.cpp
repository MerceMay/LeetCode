#include <stack>
#include <unordered_map>
using namespace std;
// 给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 小的元素（从 1 开始计数）。
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
    int count = 1;
    int result = -1;

public:
    int kthSmallest(TreeNode *root, int k)
    {
        inorder(root, k);
        return result;
    }

private:
    void inorder(TreeNode *root, int k)
    {
        if (!root || count > k)
            return;
        inorder(root->left, k);
        if (count == k)
            result = root->val;
        count++;
        inorder(root->right, k);
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
    int kthSmallest(TreeNode *root, int k)
    {
        if (!root)
            return -1;
        int count = 0;
        stack<TreeNode *> stk;
        TreeNode *current = root;
        while (current || !stk.empty())
        {
            while (current)
            {
                stk.push(current);
                current = current->left;
            }
            current = stk.top();
            stk.pop();
            count++;
            if (count == k)
                return current->val;
            current = current->right;
        }
        return -1;
    }
};

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
    unordered_map<TreeNode *, int> node_num_map; // 记录每个节点的子树节点个数
public:
    int kthSmallest(TreeNode *root, int k)
    {
        countNodeNum(root);
        TreeNode *current = root;
        while (current)
        {
            int leftTreeNodeNum = getNodeNum(current->left);
            if (leftTreeNodeNum == k - 1)
                return current->val;
            if (leftTreeNodeNum >= k)
                current = current->left;
            else
            {
                current = current->right;
                k -= leftTreeNodeNum + 1;
            }
        }
        return -1;
    }

private:
    int countNodeNum(TreeNode *node)
    {
        if (!node)
            return 0;
        if (node_num_map.count(node))
            return node_num_map[node];
        node_num_map[node] = 1 + countNodeNum(node->left) + countNodeNum(node->right);
        return node_num_map[node];
    }

    int getNodeNum(TreeNode *node)
    {
        if (node && node_num_map.count(node))
            return node_num_map[node];
        return -1;
    }
};