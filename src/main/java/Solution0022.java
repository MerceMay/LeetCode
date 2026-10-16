import java.util.*;

//数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

public class Solution0022 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.println(generateParenthesis(n));
        System.out.println(generateParenthesis2(n));
    }

    public static List<String> generateParenthesis(int n) {
        List<String> result = new ArrayList<>();
        backtrack2(n, result, new StringBuilder(), 0, 0);
        return result;
    }

    private static void backtrack(int n, List<String> result, StringBuilder sb, int left, int right) {
        if (left < right) {
            return;
        }
        if (left == n) {
            int oldLength = sb.length();
            while (right != n) {
                sb.append(")");
                right++;
            }
            result.add(sb.toString());
            sb.setLength(oldLength);
            return;
        }
        sb.append("(");
        backtrack(n, result, sb, left + 1, right);
        sb.deleteCharAt(sb.length() - 1);
        sb.append(")");
        backtrack(n, result, sb, left, right + 1);
        sb.deleteCharAt(sb.length() - 1);
    }

    private static void backtrack2(int n, List<String> result, StringBuilder sb, int left, int right) {
        if (left == n && right == n) {
            result.add(sb.toString());
            return;
        }
        if (left < n) {
            sb.append("(");
            backtrack2(n, result, sb, left + 1, right);
            sb.deleteCharAt(sb.length() - 1);
        }
        if (right < left) {
            sb.append(")");
            backtrack2(n, result, sb, left, right + 1);
            sb.deleteCharAt(sb.length() - 1);
        }
    }

    private static List[] cache = new List[100];

    public static List<String> generateParenthesis2(int n) {
        if (cache[n] != null) {
            return cache[n];
        }
        List<String> result = new ArrayList<>();
        if (n == 0) {
            result.add("");
        } else {
            for (int i = 0; i < n; i++) {
                for (String left : generateParenthesis2(i)) {
                    for (String right : generateParenthesis2(n - 1 - i)) {
                        result.add("(" + left + ")" + right);
                    }
                }
            }
        }
        cache[n] = result;
        return result;
    }
}
