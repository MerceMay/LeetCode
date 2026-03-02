package anew;

// 给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

// 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

public class Solution0079 {
    public boolean exist(char[][] board, String word) {
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[0].length; j++) {
                if (backtrack(board, word, 0, i, j)) {
                    return true;
                }
            }
        }
        return false;
    }

    private boolean backtrack(char[][] board, String word, int index, int i, int j) {
        if (index == word.length()) {
            return true;
        }
        if (i < 0 || i >= board.length || j < 0 || j >= board[0].length || word.charAt(index) != board[i][j]) {
            return false;
        }
        char temp = board[i][j];
        board[i][j] = '#';
        boolean found = backtrack(board, word, index + 1, i + 1, j) ||
                backtrack(board, word, index + 1, i - 1, j) ||
                backtrack(board, word, index + 1, i, j + 1) ||
                backtrack(board, word, index + 1, i, j - 1);
        board[i][j] = temp;
        return found;
    }

    public static void main(String[] args) {
        Solution0079 solution = new Solution0079();
        char[][] board = { { 'A', 'B', 'C', 'E' }, { 'S', 'F', 'C', 'S' }, { 'A', 'D', 'E', 'E' } };
        String word = "ABCCED";
        boolean ans = solution.exist(board, word);
        System.out.println(ans);
    }
}
