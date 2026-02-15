#include <stack>
using namespace std;
// 给你二叉树的根结点 root ，请你将它展开为一个单链表：

// 展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
// 展开后的单链表应该与二叉树 先序遍历 顺序相同。

// 示例 1：

// 输入：root = [1,2,5,3,4,null,6]
// 输出：[1,null,2,null,3,null,4,null,5,null,6]
// 示例 2：

// 输入：root = []
// 输出：[]
// 示例 3：

// 输入：root = [0]
// 输出：[0]

// 提示：

// 树中结点数在范围 [0, 2000] 内
// -100 <= Node.val <= 100

// 进阶：你可以使用原地算法（O(1) 额外空间）展开这棵树吗？
// 方法一：递归前序遍历，节点把打印换成vector<TreeNode*>，最后展开
// 方法二：使用栈
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
        if (root == nullptr)
            return;
        std::stack<TreeNode *> stack;
        stack.push(root);
        while (!stack.empty())
        {
            TreeNode *current = stack.top();
            stack.pop();
            TreeNode *left = current->left;
            TreeNode *right = current->right;
            if (right)
                stack.push(right);
            if (left)
                stack.push(left);
            current->left = nullptr;
            current->right = left ? left : (stack.empty() ? nullptr : stack.top()); // 一个节点有左节点就把他变成右节点；没有就把栈顶元素作为右节点
        }
    }
};

// 方法三：寻找前驱节点：即修改Morris遍历
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
    // 前驱节点：某个节点左子树中最右的节点
    // 先序遍历是：[当前节点]-[前驱节点]-[当前节点的右节点]。
    // 因此：找到[前驱节点]，然后把[前驱节点]的右节点设置成[当前节点的右节点]
    // 把当前节点的右节点设置成当前节点的左节点
    // 然后把当前节点的左节点设置成nullptr
    // 没有左子树的节点，直接处理下一个节点
    void flatten(TreeNode *root)
    {
        TreeNode *current = root;
        while (current)
        {
            if (current->left) // 如果有左子树
            {
                TreeNode *predecessor = current->left; // 前驱节点
                while (predecessor->right)             // 找到左子树中最右的节点
                {
                    predecessor = predecessor->right;
                }
                predecessor->right = current->right; // 把前驱节点的右节点设置成当前节点的右节点。当处理完左子树后，会回到右子树
                current->right = current->left;      // 把当前节点的右节点设置成当前节点的左节点
                current->left = nullptr;             // 把当前节点的左节点设置成nullptr
            }
            current = current->right; // 继续处理下一个节点
        }
    }
};