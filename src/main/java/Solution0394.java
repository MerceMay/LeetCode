import java.util.*;

//给定一个经过编码的字符串，返回它解码后的字符串。
//
//编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。
//
//你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。
//
//此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。
//
//测试用例保证输出的长度不会超过 105。

public class Solution0394 {
    public String decodeString(String s) {
        Deque<StringBuilder> strStack = new ArrayDeque<>();
        Deque<Integer> numStack = new ArrayDeque<>();
        StringBuilder curStr = new StringBuilder();
        int curNum = 0;
        for (char c : s.toCharArray()) {
            if (Character.isDigit(c)) {
                curNum = curNum * 10 + c - '0';
            } else if (c == '[') {
                strStack.push(curStr);
                numStack.push(curNum);
                curNum = 0;
                curStr = new StringBuilder();
            } else if (c == ']') {
                int repeat = numStack.pop();
                StringBuilder preStr = strStack.pop();
                for (int i = 0; i < repeat; i++) {
                    preStr.append(curStr);
                }
                curStr = preStr;
            } else {
                curStr.append(c);
            }
        }
        return curStr.toString();
    }
}
