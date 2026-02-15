#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <functional>
#include <array>
#include <set>
using namespace std;

// ====== Node / Edge / Graph  ======
template <typename V, typename W>
class Edge;

template <typename V, typename W>
class Node
{
public:
    V value;
    vector<Edge<V, W> *> edges;
    vector<Node<V, W> *> nexts;
    int inDegree, outDegree;
    Node(V val) : value(val), inDegree(0), outDegree(0) {}
};

template <typename V, typename W>
class Edge
{
public:
    W weight;
    Node<V, W> *from;
    Node<V, W> *to;
    Edge(W w, Node<V, W> *f, Node<V, W> *t) : weight(w), from(f), to(t) {}
};

template <typename V, typename W>
class Graph
{
public:
    unordered_map<V, Node<V, W> *> nodes;
    unordered_set<Edge<V, W> *> edges;
    bool directed;

    Graph(bool isDirected = true) : directed(isDirected) {}
    ~Graph()
    {
        for (auto &p : nodes)
            delete p.second;
        for (auto e : edges)
            delete e;
    }

    void addEdge(V fromVal, V toVal, W weight)
    {
        if (!nodes.count(fromVal))
            nodes[fromVal] = new Node<V, W>(fromVal);
        if (!nodes.count(toVal))
            nodes[toVal] = new Node<V, W>(toVal);
        Node<V, W> *from = nodes[fromVal];
        Node<V, W> *to = nodes[toVal];

        Edge<V, W> *edge = new Edge<V, W>(weight, from, to);
        from->nexts.push_back(to);
        from->edges.push_back(edge);
        from->outDegree++;
        to->inDegree++;
        edges.insert(edge);

        if (!directed)
        {
            Edge<V, W> *revEdge = new Edge<V, W>(weight, to, from);
            to->nexts.push_back(from);
            to->edges.push_back(revEdge);
            to->outDegree++;
            from->inDegree++;
            edges.insert(revEdge);
        }
    }
};

template <typename V>
class UnionFind
{
private:
    unordered_map<V, V> parent; // 节点 -> 父节点
    unordered_map<V, int> rank; // 树的高度/秩

public:
    UnionFind() {}
    void makeSet(const V &val)
    {
        if (!parent.count(val))
        {
            parent[val] = val;
            rank[val] = 1;
        }
    }

    UnionFind(const vector<V> &values)
    {
        for (const V &val : values)
        {
            parent[val] = val;
            rank[val] = 1;
        }
    }

    // 合并两个集合，按秩优化
    bool unionSets(const V &a, const V &b)
    {
        V rootA = find(a);
        V rootB = find(b);
        if (rootA == rootB)
            return false; // 已经在同一集合

        if (rank[rootA] < rank[rootB])
        {
            parent[rootA] = rootB;
        }
        else if (rank[rootA] > rank[rootB])
        {
            parent[rootB] = rootA;
        }
        else
        {
            parent[rootB] = rootA;
            rank[rootA]++;
        }
        return true;
    }

    // 判断两个节点是否属于同一集合
    bool isSameSet(const V &a, const V &b)
    {
        return find(a) == find(b);
    }

private:
    // 查找根节点，带路径压缩
    V find(const V &val)
    {
        if (parent[val] != val)
        {
            parent[val] = find(parent[val]); // 路径压缩
        }
        return parent[val];
    }
    // 也可以手动压栈
    V findIterative(const V &val)
    {
        stack<V> s;
        V cur = val;
        while (parent[cur] != cur)
        {
            s.push(cur);
            cur = parent[cur];
        }
        while (!s.empty())
        {
            parent[s.top()] = cur; // 路径压缩
            s.pop();
        }
        return cur;
    }
};

// 自定义小根堆：
// 根节点永远在数组的第一个位置
// 对于任何一个节点，它的父节点、左子节点和右子节点都可以通过简单的数学计算得到：
// 如果父节点在索引 i，那么它的左子节点在 2 * i + 1。右子节点在 2 * i + 2。
// 父节点在 (i - 1) / 2
template <typename V, typename W>
class MinHeap
{
private:
    vector<Node<V, W> *> minHeap;
    unordered_map<Node<V, W> *, int> heapIndexMap; // 记录节点在堆中的索引下标
    unordered_map<Node<V, W> *, W> distanceMap;    // 记录节点的距离
    int size;                                      // 堆中节点数量

public:
    MinHeap(int size)
    {
        minHeap.resize(size);
        this->size = 0;
    }
    bool empty()
    {
        return size == 0;
    }
    // 三种情况：加入、更新、忽略
    void addOrUpdateOrIgnore(Node<V, W> *node, W distance)
    {
        if (inHeap(node)) // 当前节点在小根堆中
        {
            if (distance < distanceMap[node]) // 只在距离真的变小时才更新
            {
                distanceMap[node] = min(distanceMap[node], distance);
                heapify_up(node, heapIndexMap[node]);
            }
        }
        if (!isEntered(node)) // 当前节点没有进来小根堆，需要创建加进来，实现add
        {
            minHeap[size] = node;
            heapIndexMap[node] = size;
            distanceMap[node] = distance;
            heapify_up(node, size++);
        }
        // 上面两个if都跳过，说明当前节点已经进来过，且最小距离已经求出来了，那么其已经已经锁死了，实现ignore
    }

    pair<Node<V, W> *, W> pop()
    {
        pair<Node<V, W> *, W> minNode = {minHeap[0], distanceMap[minHeap[0]]}; // 拿到堆顶的节点和距离
        // 将堆顶元素替换为最后一个元素
        swap(0, --size);
        // 并进行下沉操作
        heapIndexMap[minHeap[size]] = -1; // 代表这个节点已经出堆了
        distanceMap.erase(minHeap[size]);
        minHeap[size] = nullptr;
        if (size > 0) // 只在堆不为空时才下沉
        {
            heapify_down(0, size);
        }
        return minNode;
    }

private:
    bool isEntered(Node<V, W> *node) // 判断这个节点有没有进来过这个小根堆
    {
        return heapIndexMap.count(node);
    }
    bool inHeap(Node<V, W> *node) // 判断这个节点是否还在这个小根堆里
    {
        return isEntered(node) && heapIndexMap[node] != -1;
    }
    void swap(int index1, int index2) // 在小根堆中交换两个节点的位置
    {
        heapIndexMap[minHeap[index1]] = index2; // 交换索引表中的映射
        heapIndexMap[minHeap[index2]] = index1;
        std::swap(minHeap[index1], minHeap[index2]); // 交换堆中的关系
    }
    void heapify_up(Node<V, W> *node, int index) // 从index位置开始往上堆化
    {
        while (index > 0 && distanceMap[minHeap[index]] < distanceMap[minHeap[(index - 1) / 2]]) // 子节点比父节点小
        {
            swap(index, (index - 1) / 2);
            index = (index - 1) / 2;
        }
    }
    void heapify_down(int index, int size) // 从index位置开始往下堆化
    {
        int left = index * 2 + 1;
        while (left < size) // 说明有左孩子
        {
            int smallest = left + 1 < size && distanceMap[minHeap[left + 1]] < distanceMap[minHeap[left]] ? left + 1 : left; // 找出最小的孩子
            smallest = distanceMap[minHeap[smallest]] < distanceMap[minHeap[index]] ? smallest : index;                      // 找出父节点是否更小
            if (smallest == index)
                break; // 父节点最小，堆化完成
            swap(index, smallest);
            index = smallest;
            left = index * 2 + 1;
        }
    }
};

// 递归 DFS
template <typename V, typename W>
void dfsRecursive(Node<V, W> *node, unordered_set<Node<V, W> *> &visited, const function<void(Node<V, W> *)> &visit)
{
    if (!node || visited.count(node))
        return;
    visit(node); // 自定义处理逻辑
    visited.insert(node);
    for (auto next : node->nexts)
    {
        dfsRecursive(next, visited, visit);
    }
}

// 非递归 DFS
template <typename V, typename W>
void dfsIterative(Node<V, W> *start, const function<void(Node<V, W> *)> &visit)
{
    if (!start)
        return;
    unordered_set<Node<V, W> *> visited;
    stack<Node<V, W> *> s;
    s.push(start);

    while (!s.empty())
    {
        Node<V, W> *node = s.top();
        s.pop();
        if (visited.count(node))
            continue;
        visit(node);
        visited.insert(node);
        // 为了和递归顺序接近，可以逆序入栈
        for (auto it = node->nexts.rbegin(); it != node->nexts.rend(); ++it)
        {
            if (!visited.count(*it))
                s.push(*it);
        }
    }
}

// BFS
template <typename V, typename W>
void bfs(Node<V, W> *start, const function<void(Node<V, W> *)> &visit)
{
    if (!start)
        return;
    unordered_set<Node<V, W> *> visited;
    queue<Node<V, W> *> q;
    q.push(start);
    visited.insert(start);

    while (!q.empty())
    {
        Node<V, W> *node = q.front();
        q.pop();
        visit(node);
        for (auto next : node->nexts)
        {
            if (!visited.count(next))
            {
                visited.insert(next);
                q.push(next);
            }
        }
    }
}

// 拓扑排序
template <typename V, typename W>
vector<Node<V, W> *> topoSort(Graph<V, W> &g, const function<void(Node<V, W> *)> &visit = nullptr)
{
    vector<Node<V, W> *> result;                  // 存放拓扑序
    queue<Node<V, W> *> zeroInQueue;              // 入度为0的点才能进zeroInQueue队列
    unordered_map<Node<V, W> *, int> inDegreeMap; // key: 节点，value: 剩余入度

    // 入度为0的节点入队
    for (auto &[val, node] : g.nodes)
    {
        inDegreeMap[node] = node->inDegree;
        if (node->inDegree == 0)
            zeroInQueue.push(node);
    }

    while (!zeroInQueue.empty())
    {
        Node<V, W> *node = zeroInQueue.front();
        zeroInQueue.pop();
        result.push_back(node);
        if (visit)
            visit(node); // 自定义处理逻辑

        // 遍历邻接点，更新入度
        for (auto next : node->nexts)
        {
            int nextInDegree = --inDegreeMap[next];
            if (nextInDegree == 0)
            {
                zeroInQueue.push(next);
            }
        }
    }

    // 检测是否存在环
    if (result.size() != g.nodes.size())
        return {}; // 返回空表示有环，无法拓扑排序
    return result;
}

template <typename V, typename W>
void dfsTopo(Node<V, W> *node, unordered_set<Node<V, W> *> &visited, stack<Node<V, W> *> &st)
{
    if (!node || visited.count(node))
        return;
    visited.insert(node);
    for (auto next : node->nexts)
    {
        dfsTopo(next, visited, st);
    }
    st.push(node); // 后置入栈：使得其后续节点先压入栈
}
// dfs实现拓扑排序
template <typename V, typename W>
vector<Node<V, W> *> topoSortDFS(Graph<V, W> &g)
{
    vector<Node<V, W> *> res;
    unordered_set<Node<V, W> *> visited;
    stack<Node<V, W> *> st;

    for (auto &[val, node] : g.nodes)
    {
        if (!visited.count(node))
            dfsTopo(node, visited, st);
    }

    while (!st.empty())
    {
        res.push_back(st.top());
        st.pop();
    }

    return res;
}

// 朴素Dijkstra算法
template <typename V, typename W>
unordered_map<Node<V, W> *, W> dijkstraNaive(Graph<V, W> &g, Node<V, W> *start, W INF, W ZERO)
{
    unordered_map<Node<V, W> *, W> distanceMap; // 记录从start到各节点的最短距离
    unordered_set<Node<V, W> *, bool> selected; // 已确定最短路径的
    for (auto &[val, node] : g.nodes)
    {
        distanceMap[node] = INF;
        selected[node] = false;
    }
    distanceMap[start] = ZERO;
    for (size_t i = 0; i < g.nodes.size(); i++)
    {
        // 找到当前最小的节点
        Node<V, W> *minNode = nullptr;
        for (auto &[val, node] : g.nodes)
        {
            if (!selected[node] && (minNode == nullptr || distanceMap[node] < distanceMap[minNode]))
            {
                minNode = node;
            }
        }

        if (minNode == nullptr)
            break; // 剩余节点不可达

        selected[minNode] = true;

        // 更新邻接节点的距离
        for (auto &[next, weight] : minNode->edges)
        {
            if (!selected[next])
            {
                distanceMap[next] = min(distanceMap[next], distanceMap[minNode] + weight);
            }
        }
    }
    return distanceMap;
}

// 重复入堆的Dijkstra算法
template <typename V, typename W>
unordered_map<Node<V, W> *, W> dijkstraPriorityQueue(Graph<V, W> &g, Node<V, W> *start, W INF, W ZERO)
{
    unordered_map<Node<V, W> *, W> distanceMap; // 记录从start到各节点的最短距离
    for (auto &[val, node] : g.nodes)
        distanceMap[node] = INF;
    distanceMap[start] = ZERO;

    // 使用优先队列（小根堆）来优化选择最小节点的过程
    using P = pair<W, Node<V, W> *>;
    priority_queue<P, vector<P>, greater<P>> minHeap;
    minHeap.push({ZERO, start});

    while (!minHeap.empty())
    {
        auto [dist, node] = minHeap.top();
        minHeap.pop();

        // 如果当前距离大于已知最短距离，说明小根堆中的是旧数据，跳过
        if (dist > distanceMap[node])
            continue;

        // 更新邻接节点的距离
        for (auto &[next, weight] : node->edges)
        {
            int newDist = min(distanceMap[next], distanceMap[node] + weight);
            distanceMap[next] = newDist;
            minHeap.push({newDist, next}); // 重复入堆
        }
    }
    return distanceMap;
}

// 自定义小根堆的Dijkstra算法
template <typename V, typename W>
unordered_map<Node<V, W> *, W> dijkstraMinHeap(Graph<V, W> &g, Node<V, W> *start, W INF, W ZERO)
{
    unordered_map<Node<V, W> *, W> distanceMap; // 记录从start到各节点的最短距离
    for (auto &[val, node] : g.nodes)
        distanceMap[node] = INF;
    distanceMap[start] = ZERO; // start节点为0

    MinHeap<V, W> minHeap(g.nodes.size());    // 使用自定义小根堆
    minHeap.addOrUpdateOrIgnore(start, ZERO); // 把起始节点入堆
    while (!minHeap.empty())
    {
        auto [node, dist] = minHeap.pop(); // 弹出距离最小的节点及距离
        for (auto &[next, weight] : node->edges)
        {
            W newDist = dist + weight;
            if (newDist < distanceMap[next])
            {
                distanceMap[next] = newDist;
                minHeap.addOrUpdateOrIgnore(next, newDist);
            }
        }
    }
    return distanceMap;
}

// Kruskal算法
template <typename V, typename W>
set<Edge<V, W> *> kruskalMST(Graph<V, W> &g)
{
    if (g.nodes.empty())
        return {};
    // 1. 将所有边按权重排序
    vector<Edge<V, W> *> edges(g.edges.begin(), g.edges.end());
    sort(edges.begin(), edges.end(), [](Edge<V, W> *a, Edge<V, W> *b)
         { return a->weight < b->weight; });

    // 2. 初始化并查集
    UnionFind<Node<V, W> *> unionfind;
    for (auto &[val, node] : g.nodes)
        unionfind.makeSet(node);

    // 3. 选择边
    set<Edge<V, W> *> result;
    for (auto edge : edges)
    {
        if (!unionfind.isSameSet(edge->from, edge->to))
        {
            unionfind.unionSets(edge->from, edge->to);
            result.push_back(edge);
        }
    }

    // 4. 返回最小生成树
    return result;
}

// Prim算法
template <typename V, typename W>
set<Edge<V, W> *> primMST(Graph<V, W> &g)
{
    if (g.nodes.empty())
        return {};
    set<Edge<V, W> *> result;                  // 结果边集
    unordered_set<Node<V, W> *> selectedNodes; // 已加入MST的节点
    auto cmp = [](const Edge<V, W> *a, const Edge<V, W> *b)
    {
        return a->weight > b->weight;
    };
    priority_queue<Edge<V, W> *, vector<Edge<V, W> *>, decltype(cmp)> pq(cmp);

    // 1. 随便挑一个节点，加入MST
    Node<V, W> *start = g.nodes.begin()->second;
    selectedNodes.insert(start);
    for (auto edge : start->edges)
        pq.push(edge);

    // 2. 处理小根堆
    while (!pq.empty() && selectedNodes.size() < g.nodes.size())
    {
        auto minEdge = pq.top();
        pq.pop();
        Node<V, W> *toNode = minEdge->to;
        // 如果最小边的终点已经在MST中，跳过
        if (selectedNodes.count(toNode))
            continue;

        result.insert(minEdge);
        selectedNodes.insert(toNode);

        for (auto edge : toNode->edges)
            if (!selectedNodes.count(edge->to))
                pq.push(edge);
    }
    return result;
}

// Bellman-Ford算法
template <typename V, typename W>
pair<unordered_map<Node<V, W> *, pair<W, Node<V, W> *>>, bool> bellmanFord(Graph<V, W> &g, Node<V, W> *start, W INF, W ZERO)
{
    unordered_map<Node<V, W> *, pair<W, Node<V, W> *>> distanceMap; // 记录从start到各节点的最短距离及每个节点的前驱
    for (auto &[val, node] : g.nodes)
        distanceMap[node] = {INF, nullptr};
    distanceMap[start] = {ZERO, nullptr};

    int V = g.nodes.size();
    // 进行V-1次松弛操作
    for (int i = 0; i < V - 1; i++)
    {
        for (auto edge : g.edges)
        {
            Node<V, W> *from = edge->from;
            Node<V, W> *to = edge->to;
            W weight = edge->weight;
            if (distanceMap[from].first != INF && distanceMap[from].first + weight < distanceMap[to].first)
                distanceMap[to] = {distanceMap[from].first + weight, from};
        }
    }

    // 检测负权重环
    for (auto edge : g.edges)
    {
        Node<V, W> *from = edge->from;
        Node<V, W> *to = edge->to;
        W weight = edge->weight;
        if (distanceMap[from].first != INF && distanceMap[from].first + weight < distanceMap[to].first)
            return {distanceMap, false}; // 存在负权重环
    }

    return {distanceMap, true}; // 不存在负权重环
}

// Floyd-Warshall。无法检测负权环
template <typename V, typename W>
vector<vector<pair<W, Node<V, W> *>>> floydWarshall(Graph<V, W> &g, W INF, W ZERO)
{
    int n = g.nodes.size();
    vector<Node<V, W> *> nodeList;
    unordered_map<Node<V, W> *, int> nodeIndexMap; // 节点对应在nodeList中的索引
    int index = 0;
    for (auto &[val, node] : g.nodes)
    {
        nodeList.push_back(node);
        nodeIndexMap[node] = index++;
    }

    // 初始化距离矩阵
    vector<vector<pair<W, Node<V, W> *>>> dist(n, vector<pair<W, Node<V, W> *>>(n, {INF, nullptr}));
    for (int i = 0; i < n; i++)
        dist[i][i] = {ZERO, nullptr}; // 自己到自己的距离为0

    for (auto &edge : g.edges)
    {
        int fromIndex = nodeIndexMap[edge->from];
        int toIndex = nodeIndexMap[edge->to];
        dist[fromIndex][toIndex] = {edge->weight, edge->from}; // 记录权重和前驱节点
    }

    // 核心算法
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k].first != INF && dist[k][j].first != INF &&
                    dist[i][k].first + dist[k][j].first < dist[i][j].first)
                    dist[i][j] = {dist[i][k].first + dist[k][j].first, dist[k][j].second}; // 存贮的是最后一跳的前驱
                    // dist[i][j] = {dist[i][k].first + dist[k][j].first, dist[i][k].second}; // 存储的是第一跳的前驱
            }
        }
    }

    return dist;
}