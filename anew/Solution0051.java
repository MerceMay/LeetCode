package anew;

import java.util.Set;
import java.util.HashSet;
import java.util.ArrayList;
import java.util.List;

// 按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。

// n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。

// 给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。

// 每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

public class Solution0051 {
    public List<List<String>> solveNQueens(int n) {
        List<List<String>> ans = new ArrayList<>();
        backtrack(ans, new ArrayList<>(), n, 0);
        return ans;
    }

    private void backtrack(List<List<String>> ans, List<String> path, int n, int row) {
        if (row == n) {
            ans.add(new ArrayList<>(path));
            return;
        }
        for (int col = 0; col < n; col++) {
            if (valid(path, n, row, col)) {
                StringBuilder sb = new StringBuilder();
                for (int i = 0; i < n; i++) {
                    sb.append(i == col ? "Q" : ".");
                }
                path.add(sb.toString());
                backtrack(ans, path, n, row + 1);
                path.remove(path.size() - 1);
            }
        }
    }

    private boolean valid(List<String> path, int n, int row, int col) {
        for (int i = 0; i < row; i++) {
            String s = path.get(i);
            if (s.charAt(col) == 'Q') {
                return false;
            }
            int diff = row - i;
            if (col - diff >= 0 && s.charAt(col - diff) == 'Q') {
                return false;
            }
            if (col + diff < n && s.charAt(col + diff) == 'Q') {
                return false;
            }
        }
        return true;
    }

    private Set<Integer> cols = new HashSet<>();
    private Set<Integer> diag1 = new HashSet<>();
    private Set<Integer> diag2 = new HashSet<>();

    public List<List<String>> solveNQueens2(int n) {
        List<List<String>> ans = new ArrayList<>();
        backtrack2(ans, new ArrayList<>(), n, 0);
        return ans;
    }

    private void backtrack2(List<List<String>> ans, List<String> path, int n, int row) {
        if (row == n) {
            ans.add(new ArrayList<>(path));
            return;
        }
        for (int col = 0; col < n; col++) {
            if (isValid2(row, col)) {
                StringBuilder sb = new StringBuilder();
                for (int i = 0; i < n; i++) {
                    sb.append(i == col ? "Q" : ".");
                }
                path.add(sb.toString());
                cols.add(col);
                diag1.add(row - col);
                diag2.add(row + col);
                backtrack2(ans, path, n, row + 1);
                path.remove(path.size() - 1);
                cols.remove(col);
                diag1.remove(row - col);
                diag2.remove(row + col);
            }
        }
    }

    private boolean isValid2(int row, int col) {
        return !cols.contains(col) && !diag1.contains(row - col) && !diag2.contains(row + col);
    }

    public static void main(String[] args) {
        Solution0051 solution = new Solution0051();
        List<List<String>> ans = solution.solveNQueens(4);
        System.out.println(ans);
        List<List<String>> ans2 = solution.solveNQueens2(4);
        System.out.println(ans2);
    }
}
