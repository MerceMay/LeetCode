#include <vector>
#include <queue>
using namespace std;
// 你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

// 在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。

// 例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
// 请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false
// 有向图的连通性，使用拓扑排序
class Solution
{
private:
    vector<vector<int>> edges;
    bool valid = true;
    vector<int> visited; // 0：未访问，1：访问中，2
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
    }

public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for (const auto &prerequisite : prerequisites)
        {
            edges[prerequisite[0]].push_back(prerequisite[1]);
        }
        for (int i = 0; i < numCourses && valid; i++)
        {
            if (!visited[i])
                dfs(i);
        }
        return valid;
    }
};

class Solution2
{
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
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
        int visited = 0;
        while (!q.empty())
        {
            visited++;
            int course = q.front();
            q.pop();
            for (const auto &next : edges[course])
            {
                if (--inDegree[next] == 0)
                    q.push(next);
            }
        }
        return visited == numCourses;
    }
};