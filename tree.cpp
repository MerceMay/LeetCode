#include <vector>
#include <stack>
#include <queue>
using namespace std;

// 方法一：递归
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
    vector<int> preOrderTraversal(TreeNode *root)
    {
        vector<int> result;
        preOrderTraversal(root, result);
        return result;
    }
    vector<int> inOrderTraversal(TreeNode *root)
    {
        vector<int> result;
        inOrderTraversal(root, result);
        return result;
    }
    vector<int> postOrderTraversal(TreeNode *root)
    {
        vector<int> result;
        postOrderTraversal(root, result);
        return result;
    }
    vector<int> levelOrderTraversal(TreeNode *root)
    {
        vector<vector<int>> level_result;
        levelOrderTraversal(root, 0, level_result);
        vector<int> result;
        for (const auto &level : level_result)
        {
            for (int val : level)
            {
                result.push_back(val);
            }
        }
        return result;
    }

private:
    void preOrderTraversal(TreeNode *node, vector<int> &result)
    {
        if (node == nullptr)
            return;

        result.push_back(node->val);
        preOrderTraversal(node->left, result);
        preOrderTraversal(node->right, result);
    }

    void inOrderTraversal(TreeNode *node, vector<int> &result)
    {
        if (node == nullptr)
            return;

        inOrderTraversal(node->left, result);
        result.push_back(node->val);
        inOrderTraversal(node->right, result);
    }

    void postOrderTraversal(TreeNode *node, vector<int> &result)
    {
        if (node == nullptr)
            return;

        postOrderTraversal(node->left, result);
        postOrderTraversal(node->right, result);
        result.push_back(node->val);
    }
    // 这实际上还是深度优先遍历，只不过巧妙的实现了层次遍历
    void levelOrderTraversal(TreeNode *node, int level, vector<vector<int>> &level_result)
    {
        if (node == nullptr)
            return;
        if (level_result.size() == level)
        {
            level_result.push_back({});
        }
        level_result[level].push_back(node->val);
        levelOrderTraversal(node->left, level + 1, level_result);
        levelOrderTraversal(node->right, level + 1, level_result);
    }
};

// 方法二：迭代/栈/队列
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
    vector<int> preOrderTraversal(TreeNode *root)
    {
        vector<int> result;
        if (root == nullptr)
            return result;
        stack<TreeNode *> stack;
        stack.push(root); // 把根节点压入栈
        while (!stack.empty())
        {
            TreeNode *curr = stack.top();
            stack.pop();
            result.push_back(curr->val); // 打印当前节点
            if (curr->right != nullptr)
            {
                stack.push(curr->right); // 压入当前节点的右节点
            }
            if (curr->left != nullptr)
            {
                stack.push(curr->left); // 压入当前节点的左节点
            }
        }
        return result;
    }
    vector<int> inOrderTraversal(TreeNode *root)
    {
        vector<int> result;
        if (root == nullptr)
            return result;
        TreeNode *curr = root;
        stack<TreeNode *> stack;
        while (curr != nullptr || !stack.empty()) // 当前节点不为空或者栈中有节点
        {
            while (curr != nullptr) // 当前节点不为空，且一直压入左节点，直到为空
            {
                // 把当前节点压入栈
                stack.push(curr);
                // 转向左子树
                curr = curr->left;
            }
            // 弹出整棵树的最左侧，打印。
            curr = stack.top();
            stack.pop();
            result.push_back(curr->val);
            // 然后转向当前节点的右节点
            curr = curr->right;
        }
        return result;
    }
    vector<int> postOrderTraversal(TreeNode *root)
    {
        vector<int> result;
        if (root == nullptr)
            return result;
        stack<TreeNode *> stack1; // 按照先序遍历，但是先压左，再压右，得到头右左。
        stack<TreeNode *> stack2; // 把stack1倒一遍，得到左右头
        stack1.push(root);
        while (!stack1.empty())
        {
            TreeNode *node = stack1.top();
            stack1.pop();
            stack2.push(node);
            if (node->left != nullptr)
            {
                stack1.push(node->left);
            }
            if (node->right != nullptr)
            {
                stack1.push(node->right);
            }
        }
        while (!stack2.empty())
        {
            result.push_back(stack2.top()->val);
            stack2.pop();
        }
        return result;
    }
    vector<int> levelOrderTraversal(TreeNode *root) // 类似先序遍历。都是把头节点先放进队列再while。但是先压左节点，再压右节点。因为FIFO
    {
        vector<int> result;
        if (root == nullptr)
            return result;
        queue<TreeNode *> queue;
        queue.push(root);
        while (!queue.empty())
        {
            TreeNode *node = queue.front();
            queue.pop();
            result.push_back(node->val);
            if (node->left != nullptr)
            {
                queue.push(node->left);
            }
            if (node->right != nullptr)
            {
                queue.push(node->right);
            }
        }
        return result;
    }
};

// 方法三：morris遍历，空间复杂度为O(1)
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
    vector<int> preOrderTraversal(TreeNode *root)
    {
        vector<int> result;
        morrisPreOrderTraversal(root, result);
        return result;
    }

    vector<int> inOrderTraversal(TreeNode *root)
    {
        vector<int> result;
        morrisInOrderTraversal(root, result);
        return result;
    }

    vector<int> postOrderTraversal(TreeNode *root)
    {
        vector<int> result;
        morrisPostOrderTraversal(root, result);
        return result;
    }

private:
    // Morris遍历步骤：
    // - x无左孩子
    //     - x =x.right
    // - x有左孩子，找predecessor
    //     - predecessor 右孩子为空，右孩子指向x，x=x.left
    //     - predecessor 右孩子不为空，右孩子指向null，x=x.right
    // 当前遍历到的节点为 x，将 x 的左子树中最右边的节点的右孩子指向 x，这样在左子树遍历完成后我们通过这个指向走回了 x，且能通过这个指向知晓我们已经遍历完成了左子树，而不用再通过栈来维护，省去了栈的空间复杂度。
    void morris(TreeNode *root)
    {
        if (root == nullptr)
            return;
        TreeNode *current = root;
        while (current != nullptr)
        {
            if (current->left == nullptr) // 如果没有左子树
            {
                // 该节点没有左子树，所以它只会被访问一次，这次访问既是第一次，也是最后一次。先序中序都要打印
                current = current->right;
            }
            else
            {
                TreeNode *predecessor = current->left; // 先去左子树
                while (predecessor->right != nullptr && predecessor->right != current)
                {
                    predecessor = predecessor->right; // 找到左子树中最右边的节点，且没有连接的current
                }
                if (predecessor->right == nullptr) // 如果右孩子为空
                {
                    predecessor->right = current;
                    // 第一次访问发生在这里！先序打印
                    current = current->left;
                }
                else // 如果右孩子不为空
                {
                    predecessor->right = nullptr;
                    // 第二次访问发生在这里！中序打印
                    current = current->right;
                }
            }
        }
    }

    void morrisPreOrderTraversal(TreeNode *root, vector<int> &result)
    {
        if (root == nullptr)
            return;
        TreeNode *current = root;
        while (current != nullptr)
        {
            if (current->left == nullptr) // 如果没有左子树
            {
                // 该节点没有左子树，所以它只会被访问一次，这次访问既是第一次，也是最后一次
                result.push_back(current->val);
                current = current->right;
            }
            else
            {
                TreeNode *predecessor = current->left; // 先去左子树
                while (predecessor->right != nullptr && predecessor->right != current)
                {
                    predecessor = predecessor->right; // 找到左子树中最右边的节点，且没有连接的current
                }
                if (predecessor->right == nullptr) // 如果右孩子为空
                {
                    predecessor->right = current;
                    // 第一次访问发生在这里！
                    result.push_back(current->val);
                    current = current->left;
                }
                else // 如果右孩子不为空
                {
                    predecessor->right = nullptr;
                    // 第二次访问发生在这里！
                    current = current->right;
                }
            }
        }
    }

    void morrisInOrderTraversal(TreeNode *root, vector<int> &result)
    {
        if (root == nullptr)
            return;
        TreeNode *current = root;
        while (current != nullptr)
        {
            if (current->left == nullptr) // 如果没有左子树
            {
                // 该节点没有左子树，所以它只会被访问一次，这次访问既是第一次，也是最后一次
                result.push_back(current->val);
                current = current->right;
            }
            else
            {
                TreeNode *predecessor = current->left; // 先去左子树
                while (predecessor->right != nullptr && predecessor->right != current)
                {
                    predecessor = predecessor->right; // 找到左子树中最右边的节点，且没有连接的current
                }
                if (predecessor->right == nullptr) // 如果右孩子为空
                {
                    predecessor->right = current;
                    // 第一次访问发生在这里！
                    current = current->left;
                }
                else // 如果右孩子不为空
                {
                    predecessor->right = nullptr;
                    // 第二次访问发生在这里！
                    result.push_back(current->val);
                    current = current->right;
                }
            }
        }
    }

    // morris后序遍历比较复杂，在【第二次】访问一个节点的时候
    // 如果其没有左树，跳过。即分支if (current->left == nullptr)
    // 如果有左树，逆序打印整棵左树的右边界
    // 最后逆序打印整棵数的右边界
    void morrisPostOrderTraversal(TreeNode *root, vector<int> &result)
    {
        if (root == nullptr)
            return;
        TreeNode *current = root;
        while (current != nullptr)
        {
            if (current->left == nullptr) // 如果没有左子树
            {
                // 该节点没有左子树，所以它只会被访问一次，这次访问既是第一次，也是最后一次
                result.push_back(current->val);
                current = current->right;
            }
            else
            {
                TreeNode *predecessor = current->left; // 先去左子树
                while (predecessor->right != nullptr && predecessor->right != current)
                {
                    predecessor = predecessor->right; // 找到左子树中最右边的节点，且没有连接的current
                }
                if (predecessor->right == nullptr) // 如果右孩子为空
                {
                    predecessor->right = current;
                    // 第一次访问发生在这里！
                    current = current->left;
                }
                else // 如果右孩子不为空
                {
                    predecessor->right = nullptr;
                    // 第二次访问发生在这里！
                    printRightBoundary(current->left, result);
                    current = current->right;
                }
            }
        }
        printRightBoundary(root, result);
    }

private:
    void printRightBoundary(TreeNode *node, vector<int> &result)
    {
        TreeNode *tail = reverseEdge(node);
        TreeNode *curr = tail;
        while (curr != nullptr)
        {
            result.push_back(curr->val);
            curr = curr->right; // 逆序打印右边界
        }
        reverseEdge(tail); // 恢复原来的树结构
    }

    TreeNode *reverseEdge(TreeNode *root)
    {
        TreeNode *pre = nullptr, *next = nullptr;
        while (root != nullptr)
        {
            next = root->right;
            root->right = pre;
            pre = root;
            root = next;
        }
        return pre; // 返回逆序后的头节点
    }
};