#include <queue>
using namespace std;
// 给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同。

// 如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。
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
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        if (p == nullptr && q == nullptr)
            return true;
        if (p == nullptr || q == nullptr)
            return false;
        if (p->val != q->val)
            return false;
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
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
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        if (p == nullptr && q == nullptr)
            return true;
        if (p == nullptr || q == nullptr)
            return false;
        queue<TreeNode *> queueP;
        queue<TreeNode *> queueQ;
        queueP.push(p);
        queueQ.push(q);
        while (!queueP.empty() && !queueQ.empty())
        {
            TreeNode *nodeP = queueP.front();
            TreeNode *nodeQ = queueQ.front();
            queueP.pop();
            queueQ.pop();
            if (nodeP == nullptr && nodeQ == nullptr)
                continue;
            if (nodeP == nullptr || nodeQ == nullptr)
                return false;
            if (nodeP->val != nodeQ->val)
                return false;
            queueP.push(nodeP->left);
            queueP.push(nodeP->right);
            queueQ.push(nodeQ->left);
            queueQ.push(nodeQ->right);
        }
        return queueP.empty() && queueQ.empty();
    }
};