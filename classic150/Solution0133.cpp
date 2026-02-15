#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;
// 给你无向 连通 图中一个节点的引用，请你返回该图的 深拷贝（克隆）。

// 图中的每个节点都包含它的值 val（int） 和其邻居的列表（list[Node]）。

// 这张图中的节点数在 [0, 100] 之间。
// 1 <= Node.val <= 100
// 每个节点值 Node.val 都是唯一的，
// 图中没有重复的边，也没有自环。
// 图是连通图，你可以从给定节点访问到所有节点。
class Solution
{
    class Node
    {
    public:
        int val;
        vector<Node *> neighbors;
        Node()
        {
            val = 0;
            neighbors = vector<Node *>();
        }
        Node(int _val)
        {
            val = _val;
            neighbors = vector<Node *>();
        }
        Node(int _val, vector<Node *> _neighbors)
        {
            val = _val;
            neighbors = _neighbors;
        }
    };

    unordered_map<Node *, Node *> nodeMap; // 原节点到克隆节点的映射，同时记录是否访问过

public:
    Node *cloneGraph(Node *node)
    {
        if (node == nullptr)
            return nullptr;
        if (nodeMap.count(node))
            return nodeMap[node];
        Node *cloneNode = new Node(node->val);
        nodeMap[node] = cloneNode;
        for (Node *neighbor : node->neighbors)
        {
            cloneNode->neighbors.push_back(cloneGraph(neighbor));
        }
        return cloneNode;
    }
};

class Solution
{
    class Node
    {
    public:
        int val;
        vector<Node *> neighbors;
        Node()
        {
            val = 0;
            neighbors = vector<Node *>();
        }
        Node(int _val)
        {
            val = _val;
            neighbors = vector<Node *>();
        }
        Node(int _val, vector<Node *> _neighbors)
        {
            val = _val;
            neighbors = _neighbors;
        }
    };

public:
    Node *cloneGraph(Node *node)
    {
        if (node == nullptr)
            return nullptr;
        queue<Node *> q;
        unordered_map<Node *, Node *> nodeMap; // 原节点到克隆节点的映射，同时记录是否访问过
        q.push(node);
        nodeMap[node] = new Node(node->val);
        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();
            for (Node *neighbor : current->neighbors)
            {
                if (!nodeMap.count(neighbor))
                {
                    nodeMap[neighbor] = new Node(neighbor->val);
                    q.push(neighbor);
                }
                nodeMap[current]->neighbors.push_back(nodeMap[neighbor]);
            }
        }
        return nodeMap[node];
    }
};