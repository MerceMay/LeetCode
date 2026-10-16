import java.util.*;

//在给定的 m x n 网格 grid 中，每个单元格可以有以下三个值之一：
//
//值 0 代表空单元格；
//值 1 代表新鲜橘子；
//值 2 代表腐烂的橘子。
//每分钟，腐烂的橘子 周围 4 个方向上相邻 的新鲜橘子都会腐烂。
//
//返回 直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1 。

public class Solution0994 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int[][] grid = Arrays.stream(line.substring(2, line.length() - 2).split("],\\["))
                .map(s -> Arrays.stream(s.split(","))
                        .mapToInt(Integer::parseInt)
                        .toArray())
                .toArray(int[][]::new);
//        System.out.println(orangesRotting(grid));
        System.out.println(orangesRotting2(grid));
    }

    public static int orangesRotting(int[][] grid) {
        int m = grid.length;
        if (m == 0) {
            return 0;
        }
        int n = grid[0].length;
        int result = 0;
        record Point(int x, int y) {
        }
        Queue<Point> queue = new LinkedList<>();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) {
                    queue.offer(new Point(i, j));
                }
            }
        }
        int[][] directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!queue.isEmpty()) {
            int size = queue.size();
            boolean rotten = false;
            for (int i = 0; i < size; i++) {
                Point p = queue.poll();
                int x = p.x();
                int y = p.y();
                for (int[] direction : directions) {
                    int newX = x + direction[0];
                    int newY = y + direction[1];
                    if (0 <= newX && newX < m && 0 <= newY && newY < n && grid[newX][newY] == 1) {
                        grid[newX][newY] = 2;
                        queue.offer(new Point(newX, newY));
                        rotten = true;
                    }
                }
            }
            if (rotten) { // 防止最后一层腐烂的继续统计
                result++;
            }
        }
        for (int[] row : grid) {
            for (int i : row) {
                if (i == 1) {
                    return -1;
                }
            }
        }
        return result;
    }

    public static int orangesRotting2(int[][] grid) {
        int m = grid.length;
        if (m == 0) {
            return 0;
        }
        int n = grid[0].length;

        int result = 0;
        int fresh = 0;

        record Point(int x, int y) {
        }

        Queue<Point> queue = new LinkedList<>();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) {
                    queue.offer(new Point(i, j));
                } else if (grid[i][j] == 1) {
                    fresh++;
                }
            }
        }

        int[][] directions = {
                {1, 0},
                {-1, 0},
                {0, 1},
                {0, -1}
        };

        while (!queue.isEmpty() && fresh > 0) {
            int size = queue.size();

            for (int i = 0; i < size; i++) {
                Point p = queue.poll();
                int x = p.x();
                int y = p.y();

                for (int[] direction : directions) {
                    int newX = x + direction[0];
                    int newY = y + direction[1];

                    if (0 <= newX && newX < m
                            && 0 <= newY && newY < n
                            && grid[newX][newY] == 1) {

                        grid[newX][newY] = 2;
                        fresh--;
                        queue.offer(new Point(newX, newY));
                    }
                }
            }

            result++; //不会统计最后一层腐烂的，所以不需要判断
        }

        return fresh == 0 ? result : -1;
    }
}
