#include <queue>
using namespace std;
// 给定一个二叉树：

// struct Node {
//   int val;
//   Node *left;
//   Node *right;
//   Node *next;
// }
// 填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL 。

// 初始状态下，所有 next 指针都被设置为 NULL 。
class Solution
{
private:
    class Node
    {
    public:
        int val;
        Node *left;
        Node *right;
        Node *next;

        Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

        Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

        Node(int _val, Node *_left, Node *_right, Node *_next)
            : val(_val), left(_left), right(_right), next(_next) {}
    };

public:
    Node *connect(Node *root)
    {
        if (!root)
            return nullptr;
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            Node *prev = nullptr;
            while (size--)
            {
                Node *node = q.front();
                q.pop();
                if (prev)
                    prev->next = node;
                prev = node;
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
        }
        return root;
    }
};

// 空间复杂度为O(1)的方法
class Solution2
{
private:
    class Node
    {
    public:
        int val;
        Node *left;
        Node *right;
        Node *next;

        Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

        Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

        Node(int _val, Node *_left, Node *_right, Node *_next)
            : val(_val), left(_left), right(_right), next(_next) {}
    };

public:
    Node *connect(Node *root)
    {
        if (!root)
            return nullptr;

        Node *leftmost = root; // 当前层的最左节点
        while (leftmost)
        {
            Node *dummmy = new Node(0); // 下一层的虚拟头节点
            Node *temp = dummmy;        // 下一层的当前节点

            for (Node *cur = leftmost; cur != nullptr; cur = cur->next)
            {
                if (cur->left)
                {
                    temp->next = cur->left;
                    temp = temp->next;
                }
                if (cur->right)
                {
                    temp->next = cur->right;
                    temp = temp->next;
                }
            }
            leftmost = dummmy->next;
        }
        return root;
    }
};