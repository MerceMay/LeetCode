import java.util.*;

//给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
//
//给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

public class Solution0017 {

    public List<String> letterCombinations(String digits) {
        String[] map = {"", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "xyz"};
        List<String> result = new ArrayList<>();
        backtrack(digits, result, new StringBuilder(), 0, map);
        return result;
    }

    public void backtrack(String digits, List<String> result, StringBuilder sb, int index, String[] map) {
        if (index == digits.length()) {
            result.add(sb.toString());
            return;
        }
        String s = map[digits.charAt(index) - '1'];
        for (int i = 0; i < s.length(); i++) {
            sb.append(s.charAt(i));
            backtrack(digits, result, sb, index + 1, map);
            sb.deleteCharAt(sb.length() - 1);
        }
    }
}
