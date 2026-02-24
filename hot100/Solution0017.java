package hot100;

import java.util.List;
import java.util.ArrayList;

// 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

// 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

public class Solution0017 {
    private static final String[] KEYS = { "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

    public List<String> letterCombinations(String digits) {
        List<String> ans = new ArrayList<>();
        if (digits == null || digits.length() == 0) {
            return ans;
        }
        backtrack(ans, digits, 0, new StringBuilder());
        return ans;
    }

    private void backtrack(List<String> ans, String digits, int index, StringBuilder sb) {
        if (index == digits.length()) {
            ans.add(sb.toString());
            return;
        }
        String key = KEYS[digits.charAt(index) - '2'];
        for (char c : key.toCharArray()) {
            sb.append(c);
            backtrack(ans, digits, index + 1, sb);
            sb.deleteCharAt(sb.length() - 1);
        }
    }

    public static void main(String[] args) {
        Solution0017 solution = new Solution0017();
        System.out.println(solution.letterCombinations("23"));
    }
}
