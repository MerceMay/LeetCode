package hot100;

import java.util.Stack;
// 给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。

public class Solution0739 {
    public int[] dailyTemperatures(int[] temperatures) {
        int n = temperatures.length;
        int[] answer = new int[n];
        Stack<Integer> stack = new Stack<>();
        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && temperatures[i] > temperatures[stack.peek()]) {
                int index = stack.pop();
                answer[index] = i - index;
            }
            stack.push(i);
        }
        return answer;
    }

    public static void main(String[] args) {
        Solution0739 solution = new Solution0739();
        int[] temperatures = { 73, 74, 75, 71, 69, 72, 76, 73 };
        int[] result = solution.dailyTemperatures(temperatures);
        for (int r : result) {
            System.out.print(r + " ");
        }
        // 输出: [1, 1, 4, 2, 1, 1, 0, 0]
    }
}
