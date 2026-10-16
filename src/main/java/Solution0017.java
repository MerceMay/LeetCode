import java.util.*;

//给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
//
//给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

public class Solution0017 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String digits = sc.nextLine();
        System.out.println(letterCombinations(digits));
    }

    private static String[] map = {"", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

    public static List<String> letterCombinations(String digits) {
        List<String> result = new ArrayList<>();
        backtrack(digits, result, new StringBuilder(), 0);
        return result;
    }

    private static void backtrack(String digits, List<String> result, StringBuilder sb, int index) {
        if (index == digits.length()) {
            result.add(sb.toString());
            return;
        }
        String candidate = map[digits.charAt(index) - '1'];
        for (int j = 0; j < candidate.length(); j++) {
            sb.append(candidate.charAt(j));
            backtrack(digits, result, sb, index + 1);
            sb.deleteCharAt(sb.length() - 1);
        }
    }
}
