package anew;

import java.util.Stack;

// 给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。

public class Solution0739 {
    public int[] dailyTemperatures(int[] temperatures) {
        Stack<Integer> stack = new Stack<>();
        int[] res = new int[temperatures.length];
        for (int i = 0; i < temperatures.length; i++) {
            while (!stack.isEmpty() && temperatures[i] > temperatures[stack.peek()]) {
                int index = stack.pop();
                res[index] = i - index;
            }
            stack.push(i);
        }
        return res;
    }

    // 动态规划，倒序遍历，跳跃式比较
    public int[] dailyTemperatures2(int[] temperatures) {
        int n = temperatures.length;
        int[] res = new int[n];
        res[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--) {
            int next = i + 1;
            while (next < n) {
                if (temperatures[next] > temperatures[i]) { // 明天比今天暖和
                    res[i] = next - i;
                    break;
                } else if (res[next] == 0) { // 明天不比今天暖和且之后都不会再暖和了
                    break;
                } else { // 明天不比今天暖和但之后可能会暖和，跳到下一个更高温度的那一天继续比较
                    next += res[next];
                }
            }
        }
        return res;
    }

    public static void main(String[] args) {
        Solution0739 solution = new Solution0739();
        int[] temperatures = { 73, 74, 75, 71, 69, 72, 76, 73 };
        int[] result = solution.dailyTemperatures(temperatures);
        for (int r : result) {
            System.out.print(r + " ");
        }
        // 输出: [1, 1, 4, 2, 1, 1, 0, 0]
        System.out.println();

        int[] result2 = solution.dailyTemperatures2(temperatures);
        for (int r : result2) {
            System.out.print(r + " ");
        }
    }
}
