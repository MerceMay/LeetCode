import java.util.*;

//[0,1,0,2,1,0,1,3,2,1,2,1]

public class Solution0042 {
    public int trap(int[] height) {
        int n = height.length;
        if (n == 0) {
            return 0;
        }
        int[] leftHeight = new int[n];
        leftHeight[0] = height[0];
        for (int i = 1; i < n; i++) {
            leftHeight[i] = Math.max(height[i], leftHeight[i - 1]);
        }
        int[] rightHeight = new int[n];
        rightHeight[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rightHeight[i] = Math.max(height[i], rightHeight[i + 1]);
        }
        int result = 0;
        for (int i = 0; i < n; i++) {
            result += Math.min(leftHeight[i], rightHeight[i]) - height[i];
        }
        return result;
    }

    public int trap2(int[] height) {
        int result = 0;
        int left = 0, right = height.length - 1;
        int leftMax = 0, rightMax = 0;
        while (left < right) {
            leftMax = Math.max(leftMax, height[left]);
            rightMax = Math.max(rightMax, height[right]);
            if (height[left] < height[right]) {
                result += leftMax - height[left];
                left++;
            } else {
                result += rightMax - height[right];
                right--;
            }
        }
        return result;
    }

    public int trap3(int[] height) {
        int result = 0;
        Deque<Integer> stack = new ArrayDeque<>();
        for (int i = 0; i < height.length; i++) {
            while (!stack.isEmpty() && height[i] > height[stack.peek()]) {
                int cur = stack.pop();
                if (stack.isEmpty()) {
                    break;
                }
                int left = stack.peek();
                int w = i - left - 1;
                int h = Math.min(height[i], height[left]) - height[cur];
                result += w * h;
            }
            stack.push(i);
        }
        return result;
    }
}
