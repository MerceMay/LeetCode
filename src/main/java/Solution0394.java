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
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String s = sc.nextLine();
        System.out.println(decodeString(s));
        System.out.println(decodeString2(s));
    }

    public static String decodeString(String s) {
        Deque<String> stack = new LinkedList<>();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (Character.isDigit(c)) {
                StringBuilder num = new StringBuilder();
                while (i < s.length() && Character.isDigit(s.charAt(i))) {
                    num.append(s.charAt(i));
                    i++;
                }
                stack.push(num.toString());
                i--;
            } else if (Character.isAlphabetic(c)) {
                StringBuilder str = new StringBuilder();
                while (i < s.length() && Character.isAlphabetic(s.charAt(i))) {
                    str.append(s.charAt(i));
                    i++;
                }
                stack.push(str.toString());
                i--;
            } else if (c == '[') {
                stack.push("[");
            } else {
                StringBuilder str = new StringBuilder();
                while (!stack.peek().equals("[")) {
                    str.insert(0, stack.pop());
                }
                stack.pop();
                int mul = Integer.parseInt(stack.pop());
                StringBuilder temp = new StringBuilder();
                for (int j = 0; j < mul; j++) {
                    temp.append(str);
                }
                stack.push(temp.toString());
            }
        }
        StringBuilder result = new StringBuilder();
        while (!stack.isEmpty()) {
            result.insert(0, stack.pop());
        }
        return result.toString();
    }

    public static String decodeString2(String s) {
        Deque<StringBuilder> strStack = new LinkedList<>();
        Deque<Integer> numStack = new LinkedList<>();
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
                curStr = preStr.append(String.valueOf(curStr).repeat(repeat));
            } else {
                curStr.append(c);
            }
        }
        return curStr.toString();
    }
}
