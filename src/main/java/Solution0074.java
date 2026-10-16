import java.util.*;

//给你一个满足下述两条属性的 m x n 整数矩阵：
//
//每行中的整数从左到右按非严格递增顺序排列。
//每行的第一个整数大于前一行的最后一个整数。
//给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。
//
//你必须编写一个时间复杂度为 O(log(m * n)) 的解决方案。

public class Solution0074 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int target = sc.nextInt();
        int[][] matrix = Arrays.stream(line.substring(2, line.length() - 2).split("],\\["))
                .map(s -> Arrays.stream(s.split(",")).mapToInt(Integer::parseInt).toArray())
                .toArray(int[][]::new);
        System.out.println(searchMatrix(matrix, target));
    }

    public static boolean searchMatrix(int[][] matrix, int target) {
        int m = matrix.length, n = matrix[0].length;
        int left = 0, right = m * n - 1;
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            int num = matrix[mid / n][mid % n];
            if (num == target) {
                return true;
            } else if (num < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return false;
    }

    public static boolean searchMatrix2(int[][] matrix, int target) {
        int rowIndex = binarySearchFirstColumn(matrix, target);
        if (rowIndex < 0) {
            return false;
        }
        return binarySearchRow(matrix[rowIndex], target);
    }

    private static int binarySearchFirstColumn(int[][] matrix, int target) {
        int low = -1, high = matrix.length - 1;
        while (low < high) {
            int mid = low + ((high - low + 1) >> 1);
            if (matrix[mid][0] <= target) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        return low;
    }

    public static boolean binarySearchRow(int[] row, int target) {
        int low = 0, high = row.length - 1;
        while (low <= high) {
            int mid = (high - low) / 2 + low;
            if (row[mid] == target) {
                return true;
            } else if (row[mid] > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return false;
    }

}
