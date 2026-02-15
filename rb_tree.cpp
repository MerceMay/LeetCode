#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class RBTree
{
private:
    enum Color
    {
        RED,
        BLACK
    };

    struct Node
    {
        T value;
        Color color;
        Node *parent;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node(const T &val, Color c, Node *p = nullptr)
            : value(val), color(c), parent(p), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> root;

    // 获取颜色
    Color getColor(const Node *node) const
    {
        return node ? node->color : BLACK;
    }
    void setColor(Node *node, Color color)
    {
        if (node)
            node->color = color;
    }

    // 左旋
    void leftRotate(Node *x)
    {
        std::unique_ptr<Node> y = std::move(x->right); // 右子节点
        Node *yRaw = y.get();

        // y的左子节点成为x的右子节点，并把y的左子节点的父节点指向x
        x->right = std::move(yRaw->left);
        if (x->right)
            x->right->parent = x;

        yRaw->parent = x->parent; // 把x的父节点赋值给y
        if (!x->parent)           // x是根节点
        {
            root = std::move(y);
            root->left.reset(x);
            root->left->parent = root.get();
        }
        else if (x == x->parent->left.get()) // x是左子节点
        {
            x->parent->left = std::move(y);
            x->parent->left->left.reset(x);
            x->parent->left->left->parent = x->parent->left.get();
        }
        else // x是右子节点
        {
            x->parent->right = std::move(y);
            x->parent->right->left.reset(x);
            x->parent->right->left->parent = x->parent->right.get();
        }
    }

    // 右旋
    void rightRotate(Node *y)
    {
        std::unique_ptr<Node> x = std::move(y->left); // 左子节点
        Node *xRaw = x.get();

        // x的右子节点成为y的左子节点，并把x的右子节点的父节点指向y
        y->left = std::move(xRaw->right);
        if (y->left)
            y->left->parent = y;

        xRaw->parent = y->parent;
        if (!y->parent) // y是根节点
        {
            root = std::move(x);
            root->right.reset(y);
            root->right->parent = root.get();
        }
        else if (y == y->parent->left.get()) // y是左子节点
        {
            y->parent->left = std::move(x);
            y->parent->left->right.reset(y);
            y->parent->left->right->parent = y->parent->left.get();
        }
        else // y是右子节点
        {
            y->parent->right = std::move(x);
            y->parent->right->right.reset(y);
            y->parent->right->right->parent = y->parent->right.get();
        }
    }

    // 插入修复
    void fixInsert(Node *z)
    {
        while (z->parent && getColor(z->parent) == RED) // 存在父节点且父节点为红色
        {
            Node *parent = z->parent;
            Node *grandparent = parent->parent;

            if (parent == grandparent->left.get()) // 父节点是祖父节点的左子节点
            {
                Node *uncle = grandparent->right.get();
                if (getColor(uncle) == RED) // 情况一：叔叔节点为红色
                {
                    // 把父节点和叔叔节点染黑，祖父节点染红
                    setColor(parent, BLACK);
                    setColor(uncle, BLACK);
                    setColor(grandparent, RED);
                    z = grandparent;
                }
                else // 情况二和三：叔叔节点为黑色
                {
                    // 情况二：z是右子节点
                    if (z == parent->right.get())
                    {
                        z = parent;
                        leftRotate(z);
                    }
                    setColor(parent, BLACK);
                    setColor(grandparent, RED);
                    rightRotate(grandparent);
                }
            }
            else // 父节点是祖父节点的右子节点
            {
                Node *uncle = grandparent->left.get();
                if (getColor(uncle) == RED)
                {
                    setColor(parent, BLACK);
                    setColor(uncle, BLACK);
                    setColor(grandparent, RED);
                    z = grandparent;
                }
                else
                {
                    if (z == parent->left.get())
                    {
                        z = parent;
                        rightRotate(z);
                    }
                    setColor(parent, BLACK);
                    setColor(grandparent, RED);
                    leftRotate(grandparent);
                }
            }
        }
        setColor(root.get(), BLACK);
    }

    Node *insertNode(std::unique_ptr<Node> &node, Node *parent, const T &key)
    {
        if (!node)
        {
            node = std::make_unique<Node>(key, RED, parent);
            return node.get();
        }
        if (key < node->value)
            return insertNode(node->left, node.get(), key);
        else if (key > node->value)
            return insertNode(node->right, node.get(), key);
        else
            return node.get(); // 忽略重复值
    }

    // 查找
    Node *findNode(Node *node, const T &key) const
    {
        if (!node)
            return nullptr;
        if (key == node->value)
            return node;
        if (key < node->value)
            return findNode(node->left.get(), key);
        return findNode(node->right.get(), key);
    }

    // 删除修复
    void fixDelete(Node *x, Node *parent)
    {
        while ((x != root.get()) && getColor(x) == BLACK)
        {
            if (x == parent->left.get())
            {
                Node *w = parent->right.get();
                if (getColor(w) == RED)
                {
                    setColor(w, BLACK);
                    setColor(parent, RED);
                    leftRotate(parent);
                    w = parent->right.get();
                }
                if (getColor(w->left.get()) == BLACK && getColor(w->right.get()) == BLACK)
                {
                    setColor(w, RED);
                    x = parent;
                    parent = x->parent;
                }
                else
                {
                    if (getColor(w->right.get()) == BLACK)
                    {
                        setColor(w->left.get(), BLACK);
                        setColor(w, RED);
                        rightRotate(w);
                        w = parent->right.get();
                    }
                    setColor(w, getColor(parent));
                    setColor(parent, BLACK);
                    setColor(w->right.get(), BLACK);
                    leftRotate(parent);
                    x = root.get();
                }
            }
            else
            {
                Node *w = parent->left.get();
                if (getColor(w) == RED)
                {
                    setColor(w, BLACK);
                    setColor(parent, RED);
                    rightRotate(parent);
                    w = parent->left.get();
                }
                if (getColor(w->left.get()) == BLACK && getColor(w->right.get()) == BLACK)
                {
                    setColor(w, RED);
                    x = parent;
                    parent = x->parent;
                }
                else
                {
                    if (getColor(w->left.get()) == BLACK)
                    {
                        setColor(w->right.get(), BLACK);
                        setColor(w, RED);
                        leftRotate(w);
                        w = parent->left.get();
                    }
                    setColor(w, getColor(parent));
                    setColor(parent, BLACK);
                    setColor(w->left.get(), BLACK);
                    rightRotate(parent);
                    x = root.get();
                }
            }
        }
        setColor(x, BLACK);
    }

    // 删除节点
    void removeNode(std::unique_ptr<Node> &node, const T &key)
    {
        if (!node)
            return;
        if (key < node->value)
        {
            removeNode(node->left, key);
        }
        else if (key > node->value)
        {
            removeNode(node->right, key);
        }
        else
        {
            if (!node->left || !node->right) // 只有一个子节点或没有子节点
            {
                std::unique_ptr<Node> child = (node->left) ? std::move(node->left) : std::move(node->right);
                Node *parent = node->parent;
                Color originalColor = node->color;

                Node *childRaw = child.get();
                node = std::move(child);
                if (node) // 如果有子节点，更新其父节点
                    node->parent = parent;

                if (originalColor == BLACK) // 只有在删除的节点是黑色时才需要修复
                {
                    fixDelete(childRaw, parent);
                }
            }
            else
            {
                Node *successor = node->right.get();
                while (successor->left)
                    successor = successor->left.get(); // 找到中序后继
                node->value = successor->value;
                removeNode(node->right, successor->value);
            }
        }
    }

    void inorder(const Node *node, std::vector<T> &result) const
    {
        if (!node)
            return;
        inorder(node->left.get(), result);
        result.push_back(node->value);
        inorder(node->right.get(), result);
    }

public:
    void insert(const T &key)
    {
        Node *inserted = insertNode(root, nullptr, key);
        fixInsert(inserted);
    }

    bool contains(const T &key) const
    {
        return findNode(root.get(), key) != nullptr;
    }

    void remove(const T &key)
    {
        removeNode(root, key);
    }

    std::vector<T> inorder() const
    {
        std::vector<T> result;
        inorder(root.get(), result);
        return result;
    }
};
