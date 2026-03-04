package anew;

// 给你一个满足下述两条属性的 m x n 整数矩阵：

// 每行中的整数从左到右按非严格递增顺序排列。
// 每行的第一个整数大于前一行的最后一个整数。
// 给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。

public class Solution0074 {
    public boolean searchMatrix(int[][] matrix, int target) {
        int m = matrix.length;
        int n = matrix[0].length;
        int left = 0;
        int right = m * n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            int midValue = matrix[mid / n][mid % n];
            if (midValue == target) {
                return true;
            } else if (midValue < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return false;
    }

    public boolean searchMatrix2(int[][] matrix, int target) {
        int m = matrix.length;
        int n = matrix[0].length;
        return binarySearch(matrix, target, 0, m * n - 1);
    }

    private boolean binarySearch(int[][] matrix, int target, int left, int right) {
        if (left > right) {
            return false;
        }
        int n = matrix[0].length;
        int mid = left + (right - left) / 2;
        int midValue = matrix[mid / n][mid % n];
        if (midValue == target) {
            return true;
        } else if (midValue < target) {
            return binarySearch(matrix, target, mid + 1, right);
        } else {
            return binarySearch(matrix, target, left, mid - 1);
        }
    }

    public boolean searchMatrix3(int[][] matrix, int target) {
        int m = matrix.length;
        int n = matrix[0].length;
        int row = 0;
        while (row < n && matrix[row][n - 1] < target) {
            row++;
        }
        if (row == m) {
            return false;
        }
        int left = 0;
        int right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (matrix[row][mid] == target) {
                return true;
            } else if (matrix[row][mid] < target) {
                right = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        Solution0074 solution = new Solution0074();
        int[][] matrix = {
                { 1, 3, 5, 7 },
                { 10, 11, 16, 20 },
                { 23, 30, 34, 60 }
        };
        int target = 3;
        System.out.println(solution.searchMatrix(matrix, target)); // 输出: true
        System.out.println(solution.searchMatrix2(matrix, target)); // 输出: true
        System.out.println(solution.searchMatrix3(matrix, target)); // 输出: true
    }
}
