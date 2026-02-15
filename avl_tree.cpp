#include <iostream>
#include <vector>    // std::vector
#include <algorithm> // std::max
#include <memory>    // std::unique_ptr

template <typename T>
class AVLTree
{
private:
    struct Node
    {
        T value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        int height;

        Node(const T &val) : value(val), left(nullptr), right(nullptr), height(1) {}
    };

    std::unique_ptr<Node> root;

    int getHeight(const std::unique_ptr<Node> &node) const
    {
        return node ? node->height : 0;
    }

    int getBalance(const std::unique_ptr<Node> &node) const
    {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void updateHeight(Node *node)
    {
        if (node)
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    // 右旋：让y的左子节点x成为新的根节点，y成为x的右子节点，x的右子节点T2成为y的左子节点
    std::unique_ptr<Node> rightRotate(std::unique_ptr<Node> y)
    {
        std::unique_ptr<Node> x = std::move(y->left);
        std::unique_ptr<Node> T2 = std::move(x->right);

        x->right = std::move(y);
        x->right->left = std::move(T2);

        updateHeight(x->right.get());
        updateHeight(x.get());

        return x;
    }

    // 左旋：让x的右子节点y成为新的根节点，x成为y的左子节点，y的左子节点T2成为x的右子节点
    std::unique_ptr<Node> leftRotate(std::unique_ptr<Node> x)
    {
        std::unique_ptr<Node> y = std::move(x->right);
        std::unique_ptr<Node> T2 = std::move(y->left);

        y->left = std::move(x);
        y->left->right = std::move(T2);

        updateHeight(y->left.get());
        updateHeight(y.get());

        return y;
    }

    std::unique_ptr<Node> insert(std::unique_ptr<Node> node, const T &key)
    {
        if (!node)
            return std::make_unique<Node>(key);

        if (key < node->value)
            node->left = insert(std::move(node->left), key);
        else if (key > node->value)
            node->right = insert(std::move(node->right), key);
        else
            return node; // 重复值不插入

        updateHeight(node.get());

        int balance = getBalance(node);

        // 左左
        if (balance > 1 && key < node->left->value)
            return rightRotate(std::move(node));

        // 右右
        if (balance < -1 && key > node->right->value)
            return leftRotate(std::move(node));

        // 左右
        if (balance > 1 && key > node->left->value)
        {
            node->left = leftRotate(std::move(node->left));
            return rightRotate(std::move(node));
        }

        // 右左
        if (balance < -1 && key < node->right->value)
        {
            node->right = rightRotate(std::move(node->right));
            return leftRotate(std::move(node));
        }

        return node;
    }

    std::unique_ptr<Node> minValueNode(std::unique_ptr<Node> &node)
    {
        Node *current = node.get();
        while (current->left)
            current = current->left.get();
        return std::make_unique<Node>(current->value);
    }

    std::unique_ptr<Node> remove(std::unique_ptr<Node> node, const T &key)
    {
        if (!node)
            return node;

        if (key < node->value)
            node->left = remove(std::move(node->left), key);
        else if (key > node->value)
            node->right = remove(std::move(node->right), key);
        else
        {
            // 节点有一个或没有子节点
            if (!node->left || !node->right)
            {
                std::unique_ptr<Node> temp = node->left ? std::move(node->left) : std::move(node->right);
                return temp; // 直接返回子树
            }
            else
            {
                // 两个子节点
                std::unique_ptr<Node> temp = minValueNode(node->right);    // 找到右子树的最小节点
                node->value = temp->value;                                 // 用这个值替换当前节点
                node->right = remove(std::move(node->right), temp->value); // 删除右子树中的最小节点
            }
        }

        updateHeight(node.get());
        int balance = getBalance(node);

        // 左左
        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(std::move(node));

        // 左右
        if (balance > 1 && getBalance(node->left) < 0)
        {
            node->left = leftRotate(std::move(node->left));
            return rightRotate(std::move(node));
        }

        // 右右
        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(std::move(node));

        // 右左
        if (balance < -1 && getBalance(node->right) > 0)
        {
            node->right = rightRotate(std::move(node->right));
            return leftRotate(std::move(node));
        }

        return node;
    }

    bool contains(const std::unique_ptr<Node> &node, const T &key) const
    {
        if (!node)
            return false;
        if (key == node->value)
            return true;
        if (key < node->value)
            return contains(node->left, key);
        return contains(node->right, key);
    }

    void inorder(const std::unique_ptr<Node> &node, std::vector<T> &result) const
    {
        if (!node)
            return;
        inorder(node->left, result);
        result.push_back(node->value);
        inorder(node->right, result);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const T &key)
    {
        root = insert(std::move(root), key);
    }

    void remove(const T &key)
    {
        root = remove(std::move(root), key);
    }

    bool contains(const T &key) const
    {
        return contains(root, key);
    }

    std::vector<T> inorder() const
    {
        std::vector<T> result;
        inorder(root, result);
        return result;
    }
};
