#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;
// 给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。每个 Ai 或 Bi 是一个表示单个变量的字符串。

// 另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。

// 返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0 替代这个答案。

// 注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。

// 注意：未在等式列表中出现的变量是未定义的，因此无法确定它们的答案。

// 示例 1：

// 输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
// 输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
// 解释：
// 条件：a / b = 2.0, b / c = 3.0
// 问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
// 结果：[6.0, 0.5, -1.0, 1.0, -1.0 ]
// 注意：x 是未定义的 => -1.0
// 示例 2：

// 输入：equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
// 输出：[3.75000,0.40000,5.00000,0.20000]
// 示例 3：

// 输入：equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
// 输出：[0.50000,2.00000,-1.00000,-1.00000]

// 提示：

// 1 <= equations.length <= 20
// equations[i].length == 2
// 1 <= Ai.length, Bi.length <= 5
// values.length == equations.length
// 0.0 < values[i] <= 20.0
// 1 <= queries.length <= 20
// queries[i].length == 2
// 1 <= Cj.length, Dj.length <= 5
// Ai, Bi, Cj, Dj 由小写英文字母与数字组成

// 使用Flood-Warshall算法计算出整个图，但是存在double溢出问题
// 因此构建一部分图，剩下的使用BFS计算或者DFS计算
class Solution
{
public:
    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    {
        int n = equations.size(); // 一共有 n 个等式，可能涉及 2n 个变量
        vector<vector<double>> graph(2 * n, vector<double>(2 * n, -1.0));
        unordered_map<string, int> varIndex; // 变量到索引的映射
        unordered_map<int, string> indexVar; // 索引到变量的映射
        int index = 0;
        for (int i = 0; i < n; i++)
        {
            string varA = equations[i][0];
            string varB = equations[i][1];
            if (!varIndex.count(varA))
            {
                varIndex[varA] = index;
                indexVar[index] = varA;
                index++;
            }
            if (!varIndex.count(varB))
            {
                varIndex[varB] = index;
                indexVar[index] = varB;
                index++;
            }
            int idxA = varIndex[varA];
            int idxB = varIndex[varB];
            graph[idxA][idxB] = values[i];       // A / B = values
            graph[idxB][idxA] = 1.0 / values[i]; // B / A = 1 / values
            graph[idxA][idxA] = 1.0;             // A / A = 1
            graph[idxB][idxB] = 1.0;             // B / B = 1
        }
        vector<double> results(queries.size(), -1.0);
        for (int i = 0; i < queries.size(); i++)
        {
            string varC = queries[i][0];
            string varD = queries[i][1];
            if (!varIndex.count(varC) || !varIndex.count(varD))
                continue; // 有一个变量不存在，结果为 -1.0
            int idxC = varIndex[varC];
            int idxD = varIndex[varD];
            if (graph[idxC][idxD] != -1.0)
            {
                results[i] = graph[idxC][idxD]; // 直接有结果
                continue;
            }
            // 使用 BFS 查找从 C 到 D 的路径
            queue<pair<string, double>> q;
            unordered_map<string, bool> visited;
            q.push({varC, 1.0});
            visited[varC] = true;
            while (!q.empty())
            {
                auto [currentVar, currentValue] = q.front();
                q.pop();
                if (currentVar == varD)
                {
                    results[i] = currentValue;
                    break;
                }
                int currentIndex = varIndex[currentVar];
                for (int i = 0; i < index; i++)
                {
                    if (graph[currentIndex][i] != -1.0) // current能到达i
                    {
                        string nextVar = indexVar[i];
                        if (!visited[nextVar])
                        {
                            visited[nextVar] = true;
                            q.push({nextVar, currentValue * graph[currentIndex][i]});
                        }
                    }
                }
            }
        }
        return results;
    }
};

// 并查集
// 并查集 - 修改版
class Solution
{
private:
    class UnionFind
    {
    private:
        unordered_map<string, int> varIndex; // 变量到索引的映射
        vector<int> parent;                  // 父节点索引
        vector<double> weight;               // 当前节点到根节点的权重比值
        vector<int> rank;                    // 用于按秩合并
        int nodeCount;                       // 节点计数器

    public:
        UnionFind(vector<vector<string>> &equations, vector<double> &values)
        {
            nodeCount = 0;
            // 预估最大节点数量
            parent.reserve(equations.size() * 2);
            weight.reserve(equations.size() * 2);
            rank.reserve(equations.size() * 2);

            for (int i = 0; i < equations.size(); i++)
            {
                string varA = equations[i][0];
                string varB = equations[i][1];

                // 添加新变量
                addVariable(varA);
                addVariable(varB);

                // 合并两个变量，建立关系 A/B = values[i]
                unionSets(varA, varB, values[i]);
            }
        }

        // 添加新变量到并查集
        void addVariable(const string &var)
        {
            if (varIndex.find(var) == varIndex.end())
            {
                varIndex[var] = nodeCount;
                parent.push_back(nodeCount); // 初始时父节点是自己
                weight.push_back(1.0);       // 到根节点的权重为1
                rank.push_back(0);           // 初始秩为0
                nodeCount++;
            }
        }

        // 查找根节点并进行路径压缩
        int find(int x)
        {
            if (parent[x] != x)
            {
                int root = find(parent[x]);
                weight[x] *= weight[parent[x]]; // 更新权重
                parent[x] = root;               // 路径压缩
            }
            return parent[x];
        }

        // 合并两个集合
        void unionSets(const string &varA, const string &varB, double value)
        {
            int idxA = varIndex[varA];
            int idxB = varIndex[varB];

            int rootA = find(idxA);
            int rootB = find(idxB);

            if (rootA != rootB)
            {
                // 按秩合并
                if (rank[rootA] < rank[rootB])
                {
                    parent[rootA] = rootB;
                    weight[rootA] = weight[idxB] * value / weight[idxA];
                }
                else if (rank[rootA] > rank[rootB])
                {
                    parent[rootB] = rootA;
                    weight[rootB] = weight[idxA] / (weight[idxB] * value);
                }
                else
                {
                    parent[rootB] = rootA;
                    weight[rootB] = weight[idxA] / (weight[idxB] * value);
                    rank[rootA]++;
                }
            }
        }

        // 查询两个变量的比值
        double query(const string &varA, const string &varB)
        {
            // 检查变量是否存在
            if (varIndex.find(varA) == varIndex.end() ||
                varIndex.find(varB) == varIndex.end())
            {
                return -1.0;
            }

            int idxA = varIndex[varA];
            int idxB = varIndex[varB];

            int rootA = find(idxA);
            int rootB = find(idxB);

            // 不在同一个连通分量中
            if (rootA != rootB)
            {
                return -1.0;
            }

            // 返回 A/B 的值
            return weight[idxA] / weight[idxB];
        }
    };

public:
    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    {
        UnionFind uf(equations, values);
        vector<double> results;
        results.reserve(queries.size());

        for (const auto &query : queries)
        {
            results.push_back(uf.query(query[0], query[1]));
        }

        return results;
    }
};
