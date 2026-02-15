package hot100;

import java.util.ArrayDeque;
import java.util.Deque;

// 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
public class Solution0042 {
    public int trap(int[] height) {
        Deque<Integer> stack = new ArrayDeque<>();
        int area = 0;
        for (int i = 0; i < height.length; i++) {
            while (!stack.isEmpty() && height[i] > height[stack.peek()]) {
                int top = stack.pop();
                if (stack.isEmpty()) {
                    break;
                }
                int left = stack.peek();
                int w = i - left - 1;
                int h = Math.min(height[i], height[left]) - height[top];
                area += w * h;
            }
            stack.push(i);
        }
        return area;
    }

    public int trap2(int[] height) {
        int left = 0;
        int right = height.length - 1;
        int left_max = 0, right_max = 0;
        int area = 0;
        while (left < right) {
            if (height[left] < height[right]) {
                left_max = Math.max(left_max, height[left]);
                area += left_max - height[left];
                left++;
            } else {
                right_max = Math.max(right_max, height[right]);
                area += right_max - height[right];
                right--;
            }
        }
        return area;
    }

    public int trap3(int[] height) {
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

    public static void main(String[] args) {
        Solution0042 solution0042 = new Solution0042();
        int[] nums = new int[] { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
        System.out.println(solution0042.trap(nums));
        System.out.println(solution0042.trap2(nums));
        System.out.println(solution0042.trap3(nums));
    }
}
