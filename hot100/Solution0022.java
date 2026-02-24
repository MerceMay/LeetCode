package hot100;

import java.util.List;
import java.util.ArrayList;

// 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

public class Solution0022 {
    public List<String> generateParenthesis(int n) {
        List<String> ans = new ArrayList<>();
        backtrack(ans, new StringBuilder(), 0, 0, n);
        return ans;
    }

    private void backtrack(List<String> ans, StringBuilder sb, int open, int close, int n) {
        if (sb.length() == 2 * n) {
            ans.add(sb.toString());
            return;
        }
        if (open < n) {
            sb.append('(');
            backtrack(ans, sb, open + 1, close, n);
            sb.deleteCharAt(sb.length() - 1);
        }
        if (close < open) {
            sb.append(')');
            backtrack(ans, sb, open, close + 1, n);
            sb.deleteCharAt(sb.length() - 1);
        }
    }

    public List<String> generateParenthesis2(int n) {
        List<String> ans = new ArrayList<>();
        recursive(ans, "", n);
        return ans;
    }

    private void recursive(List<String> ans, String s, int n) {
        if (s.length() == 2 * n) {
            if (isValid(s)) {
                ans.add(s);
            }
            return;
        }
        recursive(ans, s + '(', n);
        recursive(ans, s + ')', n);
    }

    private boolean isValid(String s) {
        int count = 0;
        for (char c : s.toCharArray()) {
            if (c == '(') {
                count++;
            } else {
                count--;
                if (count < 0) {
                    return false;
                }
            }
        }
        return count == 0;
    }

    private List<String> cache[] = new List[100];

    public List<String> generateParenthesis3(int n) {
        return generate(n);
    }

    private List<String> generate(int n) {
        if (cache[n] != null) {
            return cache[n];
        }
        List<String> ans = new ArrayList<>();
        if (n == 0) {
            ans.add("");
        } else {
            for (int i = 0; i < n; i++) {
                List<String> left = generate(i);
                List<String> right = generate(n - 1 - i);
                for (String l : left) {
                    for (String r : right) {
                        ans.add("(" + l + ")" + r);
                    }
                }
            }
        }
        cache[n] = ans;
        return ans;
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
