package anew;

import java.util.Stack;

// 给定一个经过编码的字符串，返回它解码后的字符串。

// 编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

// 你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

// 此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

// 测试用例保证输出的长度不会超过 105

public class Solution0394 {

    public String decodeString(String s) {
        Stack<String> stack = new Stack<>();
        int i = 0;
        while (i < s.length()) {
            char c = s.charAt(i);
            if (Character.isDigit(c)) {
                StringBuilder sb = new StringBuilder();
                while (i < s.length() && Character.isDigit(s.charAt(i))) {
                    sb.append(s.charAt(i++));
                }
                stack.push(sb.toString());
            } else if (Character.isLetter(c) || c == '[') {
                stack.push(String.valueOf(c));
                i++;
            } else {
                StringBuilder decoded = new StringBuilder();
                while (!stack.isEmpty() && !stack.peek().equals("[")) {
                    decoded.insert(0, stack.pop());
                }
                stack.pop(); // 弹出'['
                int repeatTimes = Integer.parseInt(stack.pop());
                StringBuilder temp = new StringBuilder();
                for (int j = 0; j < repeatTimes; j++) {
                    temp.append(decoded);
                }
                stack.push(temp.toString());
                i++;
            }
        }
        StringBuilder result = new StringBuilder();
        while (!stack.isEmpty()) {
            result.insert(0, stack.pop());
        }
        return result.toString();
    }

    public String decodeString2(String s) {
        Stack<Integer> numStack = new Stack<>();
        Stack<StringBuilder> strStack = new Stack<>();
        StringBuilder currentNum = new StringBuilder();
        StringBuilder currentStr = new StringBuilder();
        for (char c : s.toCharArray()) {
            if (Character.isDigit(c)) {
                currentNum.append(c);
            } else if (Character.isAlphabetic(c)) {
                currentStr.append(c);
            } else if (c == '[') {
                numStack.push(Integer.parseInt(currentNum.toString()));
                strStack.push(currentStr);
                currentNum.setLength(0);
                currentStr = new StringBuilder();
            } else {
                int repeatTimes = numStack.pop();
                StringBuilder temp = strStack.pop();
                for (int i = 0; i < repeatTimes; i++) {
                    temp.append(currentStr);
                }
                currentStr = temp;
            }
        }
        return currentStr.toString();
    }

    public static void main(String[] args) {
        Solution0394 solution = new Solution0394();
        String s = "3[a]2[bc]";
        System.out.println(solution.decodeString(s)); // 输出: "aaabcbc"
        System.out.println(solution.decodeString2(s)); // 输出: "aaabcbc"
    }
}
