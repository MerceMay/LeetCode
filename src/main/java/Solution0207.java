import java.util.*;

//你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。
//
//在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。
//
//例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
//请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

public class Solution0207 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int numCourses = sc.nextInt();
        int[][] prerequisites = Arrays.stream(line.substring(2, line.length() - 2).split("],\\["))
                .map(s -> Arrays.stream(s.split(","))
                        .mapToInt(Integer::parseInt)
                        .toArray())
                .toArray(int[][]::new);
        System.out.println(canFinish(numCourses, prerequisites));
    }

    public static boolean canFinish(int numCourses, int[][] prerequisites) {
        List<List<Integer>> graph = new ArrayList<>(numCourses);
        int[] indegree = new int[numCourses];
        for (int i = 0; i < numCourses; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] p : prerequisites) {
            int course = p[0];
            int pre = p[1];
            graph.get(pre).add(course);
            indegree[course]++;
        }
        Queue<Integer> queue = new LinkedList<>();
        int count = 0;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                queue.offer(i);
            }
        }
        while (!queue.isEmpty()) {
            int cur = queue.poll();
            count++;
            for (int next : graph.get(cur)) {
                indegree[next]--;
                if (indegree[next] == 0) {
                    queue.offer(next);
                }
            }
        }

        return count == numCourses;
    }
}
