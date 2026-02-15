#include <stack>
#include <unordered_map>
using namespace std;
// 给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 小的元素（从 1 开始计数）。

// 示例 1：

// 输入：root = [3,1,4,null,2], k = 1
// 输出：1
// 示例 2：

// 输入：root = [5,3,6,2,4,null,null,1], k = 3
// 输出：3

// 提示：

// 树中的节点数为 n 。
// 1 <= k <= n <= 104
// 0 <= Node.val <= 104

// 进阶：如果二叉搜索树经常被修改（插入/删除操作）并且你需要频繁地查找第 k 小的值，你将如何优化算法？
// 方法一：使用中序遍历
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

    int count = 0;
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
        if (root == nullptr || count >= k)
            return;
        inorder(root->left, k);
        count++;
        if (count == k)
            result = root->val;
        inorder(root->right, k);
    }
};

// 方法二：使用手动栈实现中序遍历
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
        stack<TreeNode *> stack;
        TreeNode *current = root;
        while (!stack.empty() || current != nullptr)
        {
            while (current != nullptr)
            {
                stack.push(current);
                current = current->left;
            }
            current = stack.top();
            stack.pop();
            k--;
            if (k == 0)
                return current->val;
            current = current->right;
        }
        return -1; // This line should never be reached
    }
};

// 方法三：子树返回其节点个数
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

private:
    unordered_map<TreeNode *, int> node_num_map;

public:
    int kthSmallest(TreeNode *root, int k)
    {
        countNodeNum(root);
        return findKthSmallest(root, k);
    }

private:
    int findKthSmallest(TreeNode *root, int k)
    {
        TreeNode *current = root;
        while (current != nullptr)
        {
            int leftTreeNodeNum = getNodeNum(current->left);
            if (leftTreeNodeNum + 1 == k)
                return current->val;
            else if (leftTreeNodeNum + 1 < k)
            {
                k -= leftTreeNodeNum + 1;
                current = current->right;
            }
            else
                current = current->left;
        }
    }
    int countNodeNum(TreeNode *node)
    {
        if (node == nullptr)
            return 0;
        node_num_map[node] = 1 + countNodeNum(node->left) + countNodeNum(node->right);
        return node_num_map[node];
    }

    int getNodeNum(TreeNode *node)
    {
        if (node != nullptr && node_num_map.count(node))
            return node_num_map[node];
        return 0;
    }
};

// 方法四：AVL树