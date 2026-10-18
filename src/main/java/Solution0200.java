import java.util.*;

//给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
//
//岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
//
//此外，你可以假设该网格的四条边均被水包围。

public class Solution0200 {
    public int numsIslands(char[][] grid) {
        int row = grid.length;
        int col = grid[0].length;
        int count = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == '1') {
                    count++;
                    dfs(grid, i, j);
                }
            }
        }
        return count;
    }

    private void dfs(char[][] grid, int i, int j) {
        int row = grid.length;
        int col = grid[0].length;
        if (i - 1 >= 0 && grid[i - 1][j] == '1') dfs(grid, i - 1, j);
        if (i + 1 < row && grid[i + 1][j] == '1') dfs(grid, i + 1, j);
        if (j - 1 >= 0 && grid[i][j - 1] == '1') dfs(grid, i, j - 1);
        if (j + 1 < col && grid[i][j + 1] == '1') dfs(grid, i, j + 1);
    }

    public int numsIslands2(char[][] grid) {
        int row = grid.length;
        if (row == 0) return 0;
        int col = grid[0].length;
        int count = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == '1') {
                    count++;
                    grid[i][j] = '0';
                    Queue<int[]> queue = new LinkedList<>();
                    queue.offer(new int[]{i, j});
                    while (!queue.isEmpty()) {
                        int[] cur = queue.poll();
                        int rowI = cur[0], curJ = cur[1];
                        if (rowI - 1 >= 0 && grid[rowI - 1][curJ] == '1') {
                            grid[rowI - 1][curJ] = '0';
                            queue.offer(new int[]{rowI - 1, curJ});
                        }
                        if (rowI + 1 < row && grid[rowI + 1][curJ] == '1') {
                            grid[rowI + 1][curJ] = '0';
                            queue.offer(new int[]{rowI + 1, curJ});
                        }
                        if (curJ - 1 >= 0 && grid[rowI][curJ - 1] == '1') {
                            grid[rowI][curJ - 1] = '0';
                            queue.offer(new int[]{rowI, curJ - 1, curJ});
                        }
                        if (curJ + 1 < col && grid[rowI][curJ + 1] == '1') {
                            grid[rowI][curJ + 1] = '0';
                            queue.offer(new int[]{rowI, curJ + 1, curJ});
                        }
                    }
                }
            }
        }
        return count;
    }

    public int numsIslands3(char[][] grid) {
        int row = grid.length;
        if (row == 0) return 0;
        int col = grid[0].length;
        int count = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == '1') {
                    count++;
                    grid[i][j] = '0';
                    Deque<int[]> deque = new LinkedList<>();
                    deque.offer(new int[]{i, j});
                    while (!deque.isEmpty()) {
                        int[] cur = deque.poll();
                        int rowI = cur[0], curJ = cur[1];
                        if (rowI - 1 >= 0 && grid[rowI - 1][curJ] == '1') {
                            grid[rowI - 1][curJ] = '0';
                            deque.offer(new int[]{rowI - 1, curJ});
                        }
                        if (rowI + 1 < row && grid[rowI + 1][curJ] == '1') {
                            grid[rowI + 1][curJ] = '0';
                            deque.offer(new int[]{rowI + 1, curJ});
                        }
                        if (curJ - 1 >= 0 && grid[rowI][curJ - 1] == '1') {
                            grid[rowI][curJ - 1] = '0';
                            deque.offer(new int[]{rowI, curJ - 1, curJ});
                        }
                        if (curJ + 1 < col && grid[rowI][curJ + 1] == '1') {
                            grid[rowI][curJ + 1] = '0';
                            deque.offer(new int[]{rowI, curJ + 1, curJ});
                        }
                    }
                }
            }
        }
        return count;
    }
}
