package anew;

// 你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

// 在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。

// 例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
// 请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

public class Solution0207 {
    public boolean canFinish(int numCourses, int[][] prerequisites) {
        boolean[][] graph = new boolean[numCourses][numCourses];
        int[] visted = new int[numCourses];
        boolean valid = true;
        for (int[] prerequisite : prerequisites) {
            graph[prerequisite[0]][prerequisite[1]] = true;
        }
        for (int i = 0; i < numCourses && valid; i++) {
            if (visted[i] == 0) {
                valid = dfs(graph, visted, i);
            }
        }
        return valid;
    }

    private boolean dfs(boolean[][] graph, int[] visted, int i) {
        visted[i] = 1;
        for (int course = 0; course < graph.length; course++) {
            if (graph[i][course] == true) {
                if (visted[course] == 0) {
                    if (!dfs(graph, visted, course)) {
                        return false;
                    }
                } else if (visted[course] == 1) {
                    return false;
                }
            }
        }
        visted[i] = 2;
        return true;
    }

    public static void main(String[] args) {
        int numCourses = 2;
        int[][] prerequisites = { { 1, 0 } };
        Solution0207 solution = new Solution0207();
        boolean result = solution.canFinish(numCourses, prerequisites);
        System.out.println(result); // 输出: true
    }
}
