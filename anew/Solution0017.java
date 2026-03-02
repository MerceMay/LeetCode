package anew;

import java.util.ArrayList;
import java.util.List;

// 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

// 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

public class Solution0017 {
    private static final String[] KEYS = { "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

    public List<String> letterCombinations(String digits) {
        List<String> res = new ArrayList<>();
        if (digits == null || digits.length() == 0) {
            return res;
        }
        backtrack(digits, 0, res, new StringBuilder());
        return res;
    }

    private void backtrack(String digits, int index, List<String> res, StringBuilder sb) {
        if (index == digits.length()) {
            res.add(sb.toString());
            return;
        }
        String key = KEYS[digits.charAt(index) - '2'];
        for (char c : key.toCharArray()) {
            sb.append(c);
            backtrack(digits, index + 1, res, sb);
            sb.deleteCharAt(sb.length() - 1);
        }
    }

    public static void main(String[] args) {
        Solution0017 solution = new Solution0017();
        System.out.println(solution.letterCombinations("23"));
    }
}
