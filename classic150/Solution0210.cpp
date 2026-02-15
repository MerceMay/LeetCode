#include <vector>
#include <queue>
using namespace std;
// 现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1。给你一个数组 prerequisites ，其中 prerequisites[i] = [ai, bi] ，表示在选修课程 ai 前 必须 先选修 bi 。

// 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1] 。
// 返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回 一个空数组 。
class Solution
{
private:
    vector<vector<int>> edges;
    vector<int> visited;
    bool valid = true;
    vector<int> result;

    void dfs(int i)
    {
        visited[i] = 1;
        for (const auto &next : edges[i])
        {
            if (visited[next] == 0)
                dfs(next);
            else if (visited[next] == 1)
                valid = false;
        }
        visited[i] = 2;
        result.push_back(i);
    }

public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for (const auto &prerequisite : prerequisites)
        {
            edges[prerequisite[0]].push_back(prerequisite[1]); // 先学后面的再学前面的
        }
        for (int i = 0; i < numCourses && valid; i++)
        {
            if (!visited[i])
                dfs(i);
        }
        return valid ? result : vector<int>{};
    }
};

class Solution2
{
public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        queue<int> q;
        vector<int> inDegree(numCourses, 0);
        vector<vector<int>> edges(numCourses);
        for (const auto &prerequisite : prerequisites)
        {
            edges[prerequisite[1]].push_back(prerequisite[0]);
            inDegree[prerequisite[0]]++;
        }
        for (int i = 0; i < numCourses; i++)
        {
            if (inDegree[i] == 0)
                q.push(i);
        }
        vector<int> result;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            result.push_back(u);
            for (const auto &v : edges[u])
            {
                if (--inDegree[v] == 0)
                    q.push(v);
            }
        }
        if (result.size() != numCourses)
            return {};
        return result;
    }
};