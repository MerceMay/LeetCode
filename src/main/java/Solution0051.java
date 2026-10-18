import java.util.*;

//按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
//
//n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
//
//给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
//
//每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

public class Solution0051 {
    public List<List<String>> solveNQueens(int n) {
        List<List<String>> result = new ArrayList<>();
        boolean[] col = new boolean[n];
        boolean[] dig1 = new boolean[2 * n - 1];
        boolean[] dig2 = new boolean[2 * n - 1];
        int[] loc = new int[n];
        backtrack(n, result, 0, loc, col, dig1, dig2);
        return result;
    }

    public void backtrack(int n, List<List<String>> result, int index, int[] loc, boolean[] col, boolean[] dig1, boolean[] dig2) {
        if (index == n) {
            result.add(generate(loc));
            return;
        }
        for (int i = 0; i < n; i++) {
            if (col[i]) {
                continue;
            }
            int digIdx1 = index - i + n - 1;
            if (dig1[digIdx1]) {
                continue;
            }
            int digIdx2 = index + i;
            if (dig2[digIdx2]) {
                continue;
            }
            loc[index] = i;
            col[i] = true;
            dig1[digIdx1] = true;
            dig2[digIdx2] = true;
            backtrack(n, result, index + 1, loc, col, dig1, dig2);
            col[i] = false;
            dig1[digIdx1] = false;
            dig2[digIdx2] = false;
        }
    }

    public List<String> generate(int[] loc) {
        int n = loc.length;
        List<String> board = new ArrayList<>();
        for (int i : loc) {
            char[] row = new char[n];
            Arrays.fill(row, '.');
            row[i] = 'Q';
            board.add(new String(row));
        }
        return board;
    }
}
