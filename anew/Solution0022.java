package anew;

import java.util.ArrayList;
import java.util.List;

// 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

public class Solution0022 {
    public List<String> generateParenthesis(int n) {
        List<String> res = new ArrayList<>();
        backtrack(res, new StringBuilder(), 0, 0, n);
        return res;
    }

    private void backtrack(List<String> res, StringBuilder sb, int open, int close, int n) {
        if (sb.length() == 2 * n) {
            res.add(sb.toString());
            return;
        }
        if (open < n) {
            sb.append('(');
            backtrack(res, sb, open + 1, close, n);
            sb.deleteCharAt(sb.length() - 1);
        }
        if (close < open) {
            sb.append(')');
            backtrack(res, sb, open, close + 1, n);
            sb.deleteCharAt(sb.length() - 1);
        }
    }

    public List<String> generateParenthesis2(int n) {
        List<String> res = new ArrayList<>();
        recursive(res, new StringBuilder(), n);
        return res;
    }

    private void recursive(List<String> res, StringBuilder sb, int n) {
        if (sb.length() == 2 * n) {
            String str = sb.toString();
            if (valid(str)) {
                res.add(str);
            }
            return;
        }
        sb.append('(');
        recursive(res, sb, n);
        sb.deleteCharAt(sb.length() - 1);
        sb.append(')');
        recursive(res, sb, n);
        sb.deleteCharAt(sb.length() - 1);
    }

    private boolean valid(String str) {
        int balance = 0;
        for (char c : str.toCharArray()) {
            if (c == '(') {
                balance++;
            } else {
                balance--;
            }
            if (balance < 0)
                return false;
        }
        return balance == 0;
    }

    public List<String> generateParenthesis3(int n) {
        List<List<String>> cache = new ArrayList<>(n + 1);
        for (int i = 0; i <= n; i++) {
            cache.add(null);
        }
        return generate(n, cache);
    }

    private List<String> generate(int n, List<List<String>> cache) {
        if (cache.get(n) != null) {
            return cache.get(n);
        }
        List<String> res = new ArrayList<>();
        if (n == 0) {
            res.add("");
        } else {
            for (int i = 0; i < n; i++) {
                for (String left : generate(i, cache)) {
                    for (String right : generate(n - i - 1, cache)) {
                        res.add("(" + left + ")" + right);
                    }
                }
            }
        }
        cache.set(n, res);
        return res;
    }

    public static void main(String[] args) {
        Solution0022 solution = new Solution0022();
        List<String> ans = solution.generateParenthesis(3);
        System.out.println(ans);

        List<String> ans2 = solution.generateParenthesis2(3);
        System.out.println(ans2);

        List<String> ans3 = solution.generateParenthesis3(3);
        System.out.println(ans3);
    }
}
