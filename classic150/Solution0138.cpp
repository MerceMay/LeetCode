#include <unordered_map>
using namespace std;
// 给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。

// 构造这个链表的 深拷贝。 深拷贝应该正好由 n 个 全新 节点组成，其中每个新节点的值都设为其对应的原节点的值。新节点的 next 指针和 random 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点 。

// 例如，如果原链表中有 X 和 Y 两个节点，其中 X.random --> Y 。那么在复制链表中对应的两个节点 x 和 y ，同样有 x.random --> y 。

// 返回复制链表的头节点。

// 用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：

// val：一个表示 Node.val 的整数。
// random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。
// 你的代码 只 接受原链表的头节点 head 作为传入参数。

// 示例 1：

// 输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
// 输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
// 示例 2：

// 输入：head = [[1,1],[2,1]]
// 输出：[[1,1],[2,1]]
// 示例 3：

// 输入：head = [[3,null],[3,0],[3,null]]
// 输出：[[3,null],[3,0],[3,null]]

// 提示：

// 0 <= n <= 1000
// -104 <= Node.val <= 104
// Node.random 为 null 或指向链表中的节点。
class Solution
{
private:
    class Node
    {
    public:
        int val;
        Node *next;
        Node *random;

        Node(int _val)
        {
            val = _val;
            next = nullptr;
            random = nullptr;
        }
    };

public:
    // 使用两边遍历。或者使用递归
    Node *copyRandomList(Node *head)
    {
        if (!head)
            return nullptr;

        // 创建一个哈希表，用于存储原节点和新节点的映射关系
        unordered_map<Node *, Node *> nodeMap;

        // 第一次遍历，复制节点值，并建立映射关系
        Node *current = head;
        while (current)
        {
            nodeMap[current] = new Node(current->val);
            current = current->next;
        }

        // 第二次遍历，复制 random 指针
        current = head;
        while (current)
        {
            nodeMap[current]->next = nodeMap[current->next];
            nodeMap[current]->random = nodeMap[current->random];
            current = current->next;
        }

        // 返回新链表的头节点
        return nodeMap[head];
    }
};

class Solution2
{
private:
    class Node
    {
    public:
        int val;
        Node *next;
        Node *random;

        Node(int _val)
        {
            val = _val;
            next = nullptr;
            random = nullptr;
        }
    };
    unordered_map<Node *, Node *> nodeMap;

public:
    // 使用两边遍历。或者使用递归
    Node *copyRandomList(Node *head)
    {
        if (!head)
            return nullptr;
        if (nodeMap.count(head))
            return nodeMap[head];

        // 创建新节点
        Node *newNode = new Node(head->val);
        nodeMap[head] = newNode;

        // 递归复制 next 和 random 指针
        newNode->next = copyRandomList(head->next);
        newNode->random = copyRandomList(head->random);

        return newNode;
    }
};

// 方法三：先把新节点插入原链表中，在抽出来
class Solution3
{
private:
    class Node
    {
    public:
        int val;
        Node *next;
        Node *random;

        Node(int _val)
        {
            val = _val;
            next = nullptr;
            random = nullptr;
        }
    };

public:
    Node *copyRandomList(Node *head)
    {
        if (!head)
            return nullptr;
        for (Node *current = head; current; current = current->next->next)
        {
            Node *copy = new Node(current->val);
            current->next = copy;
            copy->next = current->next;
        }
        for (Node *current = head; current; current = current->next->next)
        {
            Node *copy = current->next;
            copy->random = current->random ? current->random->next : nullptr;
        }
        Node *newHead = head->next;
        for (Node *current = head; current; current = current->next)
        {
            Node *copy = current->next;
            current->next = copy->next;
            copy->next = current->next ? current->next->next : nullptr;
        }
        return newHead;
    }
};