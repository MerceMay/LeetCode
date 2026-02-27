package anew;

import java.util.Stack;

// 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
public class Solution0042 {
    public int trap(int[] height) {
        if (height.length == 0)
            return 0;
        int[] left_max = new int[height.length], right_max = new int[height.length];
        for (int i = 0; i < height.length; i++)
            left_max[i] = (i == 0) ? height[i] : Math.max(left_max[i - 1], height[i]);
        for (int i = height.length - 1; i >= 0; i--)
            right_max[i] = (i == height.length - 1) ? height[i] : Math.max(right_max[i + 1], height[i]);
        int area = 0;
        for (int i = 0; i < height.length; i++)
            area += Math.min(left_max[i], right_max[i]) - height[i];
        return area;
    }

    public int trap2(int[] height) {
        if (height.length == 0)
            return 0;
        Stack<Integer> stack = new Stack<>();
        int area = 0;
        for (int i = 0; i < height.length; i++) {
            while (!stack.isEmpty() && height[i] > height[stack.peek()]) {
                int temp = stack.pop();
                if (stack.isEmpty()) {
                    break;
                }
                int w = i - stack.peek() - 1;
                int h = Math.min(height[i], height[stack.peek()]) - height[temp];
                area += w * h;
            }
            stack.push(i);
        }
        return area;
    }

    public int trap3(int[] height) {
        int left = 0, right = height.length - 1;
        int leftMax = 0, rightMax = 0;
        int area = 0;
        while (left < right) {
            if (height[left] < height[right]) {
                leftMax = Math.max(leftMax, height[left]);
                area += leftMax - height[left];
                left++;
            } else {
                rightMax = Math.max(rightMax, height[right]);
                area += rightMax - height[right];
                right--;
            }
        }
        return area;
    }
}
