package anew;

import java.util.Stack;
// 给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

// 求在该柱状图中，能够勾勒出来的矩形的最大面积。

public class Solution0084 {
    // 找到i左右两边第一个比i矮的柱子，计算以i为高的矩形面积

    public int largestRectangleArea(int[] heights) {
        if (heights == null || heights.length == 0) {
            return 0;
        }
        int n = heights.length;
        int[] newHeights = new int[n + 1];
        System.arraycopy(heights, 0, newHeights, 0, n);
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

    public int largestRectangleArea2(int[] heights) {
        int n = heights.length;
        int[] leftMin = new int[n];
        int[] rightMin = new int[n];
        Stack<Integer> stack = new Stack<>();

        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && heights[i] <= heights[stack.peek()]) {
                stack.pop();
            }
            leftMin[i] = stack.isEmpty() ? -1 : stack.peek();
            stack.push(i);
        }

        for (int i = n - 1; i >= 0; i--) {
            while (!stack.isEmpty() && heights[i] <= heights[stack.peek()]) {
                stack.pop();
            }
            rightMin[i] = stack.isEmpty() ? n : stack.peek();
            stack.push(i);
        }

        int res = 0;
        for (int i = 0; i < n; i++) {
            res = Math.max(res, (rightMin[i] - leftMin[i] - 1) * heights[i]);
        }
        return res;
    }

    public int largestRectangleArea3(int[] heights) {
        int n = heights.length;
        int[] leftMin = new int[n];
        int[] rightMin = new int[n];
        Stack<Integer> stack = new Stack<>();

        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && heights[i] <= heights[stack.peek()]) {
                rightMin[stack.pop()] = i;
            }
            leftMin[i] = stack.isEmpty() ? -1 : stack.peek();
            stack.push(i);
        }

        int res = 0;
        for (int i = 0; i < n; i++) {
            res = Math.max(res, (rightMin[i] - leftMin[i] - 1) * heights[i]);
        }
        return res;
    }

    public int largestRectangleArea4(int[] heights) {
        int n = heights.length;
        int[] leftMin = new int[n];
        int[] rightMin = new int[n];
        leftMin[0] = -1;
        rightMin[n - 1] = n;

        for (int i = 1; i < n; i++) {
            int temp = i - 1; // 从i的左边开始往左找第一个比i矮的柱子
            while (temp >= 0 && heights[temp] >= heights[i]) { // temp比i高，继续往左找
                temp = leftMin[temp]; // leftMin[temp]是temp左边第一个比temp矮的，因此直接跳过从leftMin[temp]到temp之间的柱子
            }
            leftMin[i] = temp;
        }

        for (int i = n - 2; i >= 0; i--) {
            int temp = i + 1;
            while (temp < n && heights[temp] >= heights[i]) {
                temp = rightMin[temp];
            }
            rightMin[i] = temp;
        }

        int res = 0;
        for (int i = 0; i < n; i++) {
            res = Math.max(res, (rightMin[i] - leftMin[i] - 1) * heights[i]);
        }
        return res;
    }

    public static void main(String[] args) {
        Solution0084 solution = new Solution0084();
        int[] heights = { 2, 1, 5, 6, 2, 3 };
        System.out.println(solution.largestRectangleArea(heights)); // 输出: 10
        System.out.println(solution.largestRectangleArea2(heights)); // 输出: 10
        System.out.println(solution.largestRectangleArea3(heights)); // 输出: 10
        System.out.println(solution.largestRectangleArea4(heights)); // 输出: 10
    }
}
