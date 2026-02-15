#include <climits>
using namespace std;
// 给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。

// 有效 二叉搜索树定义如下：

// 节点的左子树只包含 严格小于 当前节点的数。
// 节点的右子树只包含 严格大于 当前节点的数。
// 所有左子树和右子树自身必须也是二叉搜索树。

// 示例 1：

// 输入：root = [2,1,3]
// 输出：true
// 示例 2：

// 输入：root = [5,1,4,null,null,3,6]
// 输出：false
// 解释：根节点的值是 5 ，但是右子节点的值是 4 。

// 提示：

// 树中节点数目范围在[1, 104] 内
// -231 <= Node.val <= 231 - 1

// 方法一：递归：需要注意，一个节点不仅要比较其左节点和右节点，还要确保其左子树和右子树
// 因此，需要子树传递其范围给父节点。因此需要一个辅助函数
class Solution1
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
    bool isValidBST(TreeNode *root)
    {
        return helper(root, LONG_MIN, LONG_MAX);
    }

private:
    bool helper(TreeNode *root, long minVal, long maxVal)
    {
        if (root == nullptr)
            return true;
        if (root->val <= minVal || root->val >= maxVal)
            return false;
        return helper(root->left, minVal, root->val) && helper(root->right, root->val, maxVal);
    }
};

// 方法二：中序遍历
class Solution1
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
    bool isValidBST(TreeNode *root)
    {
        long prev = LONG_MIN; // 使用long类型防止溢出
        return inorder(root, prev);
    }

private:
    bool inorder(TreeNode *root, long &prev)
    {
        if (root == nullptr)
            return true;
        if (!inorder(root->left, prev))
            return false;
        if (root->val <= prev) // 如果当前节点小于等于前一个节点，说明不是二叉搜索树
            return false;
        prev = root->val; // 更新前一个节点的值
        return inorder(root->right, prev);
    }
};