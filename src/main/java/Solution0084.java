import java.util.*;

//给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
//
//求在该柱状图中，能够勾勒出来的矩形的最大面积。

public class Solution0084 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int[] heights = Arrays.stream(line.substring(1, line.length() - 1).split(","))
                .mapToInt(Integer::parseInt)
                .toArray();
        System.out.println(largestRectangleArea(heights));
        System.out.println(largestRectangleArea2(heights));
    }

    public static int largestRectangleArea(int[] heights) {
        Deque<Integer> monotonicStack = new LinkedList<>();
        int maxArea = 0;
        for (int i = 0; i <= heights.length; i++) {
            int curHeight = i == heights.length ? 0 : heights[i];
            while (!monotonicStack.isEmpty() && heights[monotonicStack.peek()] > curHeight) {
                int index = monotonicStack.pop();
                int left = monotonicStack.isEmpty() ? -1 : monotonicStack.peek();
                maxArea = Math.max(maxArea, heights[index] * (i - left - 1));
            }
            monotonicStack.push(i);
        }
        return maxArea;
    }

    public static int largestRectangleArea2(int[] heights) {
        Deque<Integer> monotonicStack = new LinkedList<>();
        int[] left = new int[heights.length];
        int[] right = new int[heights.length];
        Arrays.fill(right, heights.length);
        for (int i = 0; i < heights.length; i++) {
            while (!monotonicStack.isEmpty() && heights[monotonicStack.peek()] >= heights[i]) {
                right[monotonicStack.pop()] = i;
            }
            left[i] = monotonicStack.isEmpty() ? -1 : monotonicStack.peek();
            monotonicStack.push(i);
        }
        int maxArea = 0;
        for (int i = 0; i < heights.length; i++) {
            maxArea = Math.max((right[i] - left[i] - 1) * heights[i], maxArea);
        }
        return maxArea;
    }

}
