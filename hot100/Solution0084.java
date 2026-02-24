package hot100;

import java.util.Stack;
import java.util.Arrays;

// 给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1。

// 求在该柱状图中，能够勾勒出来的矩形的最大面积。

public class Solution0084 {
    public int largestRectangleArea(int[] heights) {
        int n = heights.length;
        int[] newHeights = Arrays.copyOf(heights, n + 1);
        newHeights[n] = 0;
        Stack<Integer> stack = new Stack<>();
        int maxArea = 0;
        for (int i = 0; i <= n; i++) {
            while (!stack.isEmpty() && newHeights[i] < newHeights[stack.peek()]) {
                int height = newHeights[stack.pop()];
                int width = stack.isEmpty() ? i : i - stack.peek() - 1;
                maxArea = Math.max(maxArea, height * width);
            }
            stack.push(i);
        }
        return maxArea;
    }

    public static void main(String[] args) {
        Solution0084 solution = new Solution0084();
        int[] heights = { 2, 1, 5, 6, 2, 3 };
        System.out.println(solution.largestRectangleArea(heights)); // 输出: 10
    }
}
