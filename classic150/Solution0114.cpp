#include <stack>
using namespace std;
// 给你二叉树的根结点 root ，请你将它展开为一个单链表：

// 展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
// 展开后的单链表应该与二叉树 先序遍历 顺序相同。

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
    void flatten(TreeNode *root)
    {
        if (!root)
            return;
        stack<TreeNode *> stk;
        stk.push(root);
        while (!stk.empty())
        {
            TreeNode *node = stk.top();
            stk.pop();
            TreeNode *left = node->left;
            TreeNode *right = node->right;
            if (right)
                stk.push(right);
            if (left)
                stk.push(left);
            node->left = nullptr;
            node->right = left ? left : (stk.empty() ? nullptr : stk.top()); // 一个节点有左节点就把他变成右节点；没有就把栈顶元素作为右节点
        }
    }

    // 方法二：使用栈
    void flatten2(TreeNode *root)
    {
        if (!root)
            return;
        stack<TreeNode *> stk;
        stk.push(root);
        TreeNode *prev = nullptr; // 使用prev记录先序遍历时的前一个节点，这样只需要把前一个节点的右指针指向当前节点
        while (!stk.empty())
        {
            TreeNode *node = stk.top();
            stk.pop();
            if (prev)
            {
                prev->left = nullptr;
                prev->right = node;
            }
            if (node->right)
                stk.push(node->right);
            if (node->left)
                stk.push(node->left);
            prev = node;
        }
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
    void flatten(TreeNode *root)
    {
        TreeNode *cur = root;
        while (cur)
        {
            if (cur->left != nullptr)
            {
                TreeNode *next = cur->left;
                TreeNode *predecessor = next;
                while (predecessor->right != nullptr)
                    predecessor = predecessor->right;
                predecessor->left = cur->right; // 使用前驱节点记录下当前节点的右子树，这样当遍历完左子树时，返回的就是右子树
                cur->left = nullptr;
                cur->right = next;
            }
            cur = cur->right;
        }
    }
};