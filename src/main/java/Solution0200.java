import java.util.*;

//给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
//
//岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
//
//此外，你可以假设该网格的四条边均被水包围。

public class Solution0200 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        StringBuilder sb = new StringBuilder();
        while (sc.hasNextLine()) {
            String line = sc.nextLine().trim();
            sb.append(line);
            if (line.equals("]")) {
                break;
            }
        }
        String input = sb.toString();
        String[] rows = input.substring(2, input.length() - 2).split("],\\[");
        char[][] grid = new char[rows.length][];
        for (int i = 0; i < rows.length; i++) {
            String[] nums = rows[i].replace("'", "").split(",");
            grid[i] = new char[nums.length];
            for (int j = 0; j < nums.length; j++) {
                grid[i][j] = nums[j].trim().charAt(0);
            }
        }
//        System.out.println(numIslands(grid));
//        System.out.println(numIslands2(grid));
        System.out.println(numIslands3(grid));
    }

    public static int numIslands(char[][] grid) {
        int m = grid.length;
        if (m == 0) {
            return 0;
        }
        int n = grid[0].length;
        int result = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    result++;
                    dfs(grid, i, j);
                }
            }
        }
        return result;
    }

    private static void dfs(char[][] grid, int i, int j) {
        int m = grid.length;
        int n = grid[0].length;
        grid[i][j] = '0';
        if (i - 1 >= 0 && grid[i - 1][j] == '1') dfs(grid, i - 1, j);
        if (i + 1 < m && grid[i + 1][j] == '1') dfs(grid, i + 1, j);
        if (j - 1 >= 0 && grid[i][j - 1] == '1') dfs(grid, i, j - 1);
        if (j + 1 < n && grid[i][j + 1] == '1') dfs(grid, i, j + 1);
    }

    public static int numIslands2(char[][] grid) {
        int m = grid.length;
        if (m == 0) {
            return 0;
        }
        int n = grid[0].length;
        int result = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    result++;
                    grid[i][j] = '0';
                    Queue<int[]> queue = new LinkedList<>();
                    queue.offer(new int[]{i, j});
                    while (!queue.isEmpty()) {
                        int[] point = queue.poll();
                        int row = point[0], col = point[1];
                        if (row - 1 >= 0 && grid[row - 1][col] == '1') {
                            queue.offer(new int[]{row - 1, col});
                            grid[row - 1][col] = '0';
                        }
                        if (row + 1 < m && grid[row + 1][col] == '1') {
                            queue.offer(new int[]{row + 1, col});
                            grid[row + 1][col] = '0';
                        }
                        if (col - 1 >= 0 && grid[row][col - 1] == '1') {
                            queue.offer(new int[]{row, col - 1});
                            grid[row][col - 1] = '0';
                        }
                        if (col + 1 < n && grid[row][col + 1] == '1') {
                            queue.offer(new int[]{row, col + 1});
                            grid[row][col + 1] = '0';
                        }
                    }
                }
            }
        }
        return result;
    }

    public static int numIslands3(char[][] grid) {
        int m = grid.length;
        if (m == 0) {
            return 0;
        }
        int n = grid[0].length;
        int result = 0;

        record Position(int i, int j) {
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    result++;

                    Deque<Position> stack = new LinkedList<>();
                    stack.push(new Position(i, j));
                    grid[i][j] = '0';

                    while (!stack.isEmpty()) {
                        Position pos = stack.pop();
                        int row = pos.i();
                        int col = pos.j();

                        if (row - 1 >= 0 && grid[row - 1][col] == '1') {
                            grid[row - 1][col] = '0';
                            stack.push(new Position(row - 1, col));
                        }

                        if (row + 1 < m && grid[row + 1][col] == '1') {
                            grid[row + 1][col] = '0';
                            stack.push(new Position(row + 1, col));
                        }

                        if (col - 1 >= 0 && grid[row][col - 1] == '1') {
                            grid[row][col - 1] = '0';
                            stack.push(new Position(row, col - 1));
                        }

                        if (col + 1 < n && grid[row][col + 1] == '1') {
                            grid[row][col + 1] = '0';
                            stack.push(new Position(row, col + 1));
                        }
                    }
                }
            }
        }

        return result;
    }
}
