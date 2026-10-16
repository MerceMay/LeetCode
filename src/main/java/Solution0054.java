import java.util.*;

//给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。

public class Solution0054 {
    public List<Integer> spiralOrder(int[][] matrix) {
        List<Integer> result = new ArrayList<>();
        int m = matrix.length, n = matrix[0].length;
        if (m == 0 || n == 0) {
            return result;
        }
        int left = 0, right = n - 1, top = 0, bottom = m - 1;
        while (left <= right && top <= bottom) {
            for (int i = left; i <= right; i++) {
                result.add(matrix[top][i]);
            }
            top++;
            for (int i = top; i <= bottom; i++) {
                result.add(matrix[i][right]);
            }
            right--;
            if (left <= right && top <= bottom) {
                for (int i = right; i >= left; i--) {
                    result.add(matrix[bottom][i]);
                }
                bottom--;
                for (int i = bottom; i >= top; i--) {
                    result.add(matrix[i][left]);
                }
                left++;
            }
        }
        return result;
    }

    public List<Integer> spiralOrder2(int[][] matrix) {
        List<Integer> result = new ArrayList<>();
        int m = matrix.length, n = matrix[0].length;
        if (n == 0) {
            return result;
        }
        boolean[][] visited = new boolean[m][n];
        int total = m * n;
        int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int index = 0;
        int row = 0, col = 0;
        for (int i = 0; i < total; i++) {
            result.add(matrix[row][col]);
            visited[row][col] = true;
            int nexRow = row + directions[index][0], nexCol = col + directions[index][1];
            if (nexRow < 0 || nexRow >= m || nexCol < 0 || nexCol >= n || visited[nexRow][nexCol]) {
                index = (index + 1) % 4;
            }
            row += directions[index][0];
            col += directions[index][1];
        }
        return result;
    }
}
