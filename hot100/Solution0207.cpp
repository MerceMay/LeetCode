#include <vector>
#include <unordered_map>
using namespace std;
// 你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

// 在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。

// 例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
// 请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

// 示例 1：

// 输入：numCourses = 2, prerequisites = [[1,0]]
// 输出：true
// 解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
// 示例 2：

// 输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
// 输出：false
// 解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。

// 提示：

// 1 <= numCourses <= 2000
// 0 <= prerequisites.length <= 5000
// prerequisites[i].length == 2
// 0 <= ai, bi < numCourses
// prerequisites[i] 中的所有课程对 互不相同
// 有向图的环检测：拓扑排序
class Solution
{
private:
    vector<vector<int>> edges; // 最外层表示有多少个课程，edges[i]学习课程 i 之前需要完成的课程
    bool valid = true;         // 是否可能
    vector<int> visited;       // 0：未访问，1：访问中，2：已访问。
    void dfs(int cur)
    {
        visited[cur] = 1; // 访问中
        for (const auto &next : edges[cur])
        {
            if (visited[next] == 0)
                dfs(next);
            else if (visited[next] == 1)
                valid = false;
        }
        visited[cur] = 2; // 已访问
    }

public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for (const auto &prerequisite : prerequisites)
        {
            edges[prerequisite[0]].push_back(prerequisite[1]);
            // edges[prerequisite[1]] = prerequisite[]; 这个也是对的，实际上，这两种一个构建的是正向图，一个是反向图。
        }
        for (int i = 0; i < numCourses && valid; i++)
        {
            if (!visited[i])
                dfs(i);
        }
        return valid;
    }
};