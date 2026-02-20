package hot100;

import java.util.ArrayList;
import java.util.List;

// 你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

// 在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。

// 例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
// 请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

public class Solution0207 {

    public boolean canFinish(int numCourses, int[][] prerequisites) {
        List<List<Integer>> graph = new ArrayList<>(numCourses);
        List<Integer> visited = new ArrayList<>(numCourses);
        boolean valid = true;
        for (int i = 0; i < numCourses; i++) {
            graph.add(new ArrayList<>());
            visited.add(0);
        }
        for (int[] prerequisite : prerequisites) {
            int course = prerequisite[0];
            int preCourse = prerequisite[1];
            graph.get(preCourse).add(course);
        }
        for (int i = 0; i < numCourses && valid; i++) {
            if (visited.get(i) == 0) {
                valid = dfs(graph, visited, i);
            }
        }
        return valid;
    }

    private boolean dfs(List<List<Integer>> graph, List<Integer> visited, int course) {
        visited.set(course, 1);
        for (int nextCourse : graph.get(course)) {
            if (visited.get(nextCourse) == 0) {
                if (!dfs(graph, visited, nextCourse)) {
                    return false;
                }
            } else if (visited.get(nextCourse) == 1) {
                return false;
            }
        }
        visited.set(course, 2);
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
