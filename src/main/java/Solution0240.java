import java.util.*;

//编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：
//
//每行的元素从左到右升序排列。
//每列的元素从上到下升序排列。

public class Solution0240 {
    public boolean searchMatrix(int[][] matrix, int target) {
        for (int[] row : matrix) {
            int index = binarysearch(row, target);
            if (index >= 0) {
                return true;
            }
        }
        return false;
    }

    private int binarysearch(int[] row, int target) {
        int left = 0, right = row.length - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (row[mid] == target) {
                return mid;
            } else if (row[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }

    public boolean searchMatrix2(int[][] matrix, int target) {
        int m = matrix.length, n = matrix[0].length;
        int row = m - 1, col = 0;
        while (row >= 0 && col < n) {
            if (matrix[row][col] == target) {
                return true;
            } else if (matrix[row][col] < target) {
                col++;
            } else {
                row--;
            }
        }
        return false;
    }
}
