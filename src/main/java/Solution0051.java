import java.util.*;

//按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
//
//n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
//
//给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
//
//每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

public class Solution0051 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.println(solveNQueens(n));
        System.out.println(solveNQueens2(n));
    }

    public static List<List<String>> solveNQueens(int n) {
        List<List<String>> result = new ArrayList<>();
        boolean[] col = new boolean[n];
        boolean[] dig1 = new boolean[2 * n - 1];
        boolean[] dig2 = new boolean[2 * n - 1];
        int[] location = new int[n];
        backtrack(n, result, location, 0, col, dig1, dig2);
        return result;
    }

    private static void backtrack(int n, List<List<String>> result, int[] location, int rowIndex, boolean[] col, boolean[] dig1, boolean[] dig2) {
        if (rowIndex == n) {
            result.add(generate(location));
            return;
        }
        for (int i = 0; i < n; i++) {
            if (col[i]) {
                continue;
            }
            int digIndex1 = rowIndex - i + n - 1;
            if (dig1[digIndex1]) {
                continue;
            }
            int digIndex2 = rowIndex + i;
            if (dig2[digIndex2]) {
                continue;
            }
            location[rowIndex] = i;
            col[i] = true;
            dig1[digIndex1] = true;
            dig2[digIndex2] = true;
            backtrack(n, result, location, rowIndex + 1, col, dig1, dig2);
            col[i] = false;
            dig1[digIndex1] = false;
            dig2[digIndex2] = false;
        }
    }

    private static List<String> generate(int[] location) {
        int n = location.length;
        List<String> board = new ArrayList<>();
        for (int i : location) {
            char[] row = new char[n];
            Arrays.fill(row, '.');
            row[i] = 'Q';
            board.add(new String(row));
        }
        return board;
    }

    public static List<List<String>> solveNQueens2(int n) {
        List<List<String>> result = new ArrayList<>();
        int[] loc = new int[n];

        int mask = (1 << n) - 1;

        backtrack(n, result, loc, 0, 0, 0, 0, mask);

        return result;
    }

    private static void backtrack(int n, List<List<String>> result, int[] loc, int rowIndex, int col, int dig1, int dig2, int mask) {
        if (rowIndex == n) {
            result.add(generate(loc));
            return;
        }

        // 当前行所有可以放皇后的位置
        int available = mask & ~(col | dig1 | dig2);

        while (available != 0) {
            // 取最低位的 1
            int position = available & -available;

            // 去掉这个位置
            available &= available - 1;

            // position 是 2^i，得到列号 i
            int colIndex = Integer.numberOfTrailingZeros(position);
            loc[rowIndex] = colIndex;

            backtrack(n, result, loc, rowIndex + 1, col | position, (dig1 | position) << 1, (dig2 | position) >> 1, mask);
        }
    }
}
