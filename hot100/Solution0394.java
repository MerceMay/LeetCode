package hot100;

import java.util.Stack;

// 给定一个经过编码的字符串，返回它解码后的字符串。

// 编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

// 你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

// 此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

// 测试用例保证输出的长度不会超过 105。

public class Solution0394 {
    public String decodeString(String s) {
        Stack<String> numStack = new Stack<>();
        Stack<String> strStack = new Stack<>();
        StringBuilder currentStr = new StringBuilder();
        StringBuilder currentNum = new StringBuilder();
        for (char c : s.toCharArray()) {
            if (Character.isDigit(c)) {
                currentNum.append(c);
            } else if (c == '[') {
                numStack.push(currentNum.toString());
                strStack.push(currentStr.toString());
                currentNum.setLength(0);
                currentStr.setLength(0);
            } else if (c == ']') {
                int repeatTimes = Integer.parseInt(numStack.pop());
                StringBuilder temp = new StringBuilder(strStack.pop());
                for (int i = 0; i < repeatTimes; i++) {
                    temp.append(currentStr);
                }
                currentStr = temp;
            } else {
                currentStr.append(c);
            }
        }
        return currentStr.toString();
    }

    public static void main(String[] args) {
        Solution0394 solution = new Solution0394();
        String s = "3[a]2[bc]";
        System.out.println(solution.decodeString(s)); // 输出: "aaabcbc"
    }
}
