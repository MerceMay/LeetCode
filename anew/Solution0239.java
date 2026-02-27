package anew;

import java.util.PriorityQueue;
import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;

// 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

// 返回 滑动窗口中的最大值。

public class Solution0239 {
    public int[] maxSlidingWindow(int[] nums, int k) {
        int[] res = new int[nums.length - k + 1];
        Deque<Integer> deque = new ArrayDeque<>();
        for (int i = 0; i < nums.length; i++) {
            if (!deque.isEmpty() && deque.peekFirst() < i - k + 1) {
                deque.pollFirst();
            }
            while (!deque.isEmpty() && nums[deque.peekLast()] < nums[i]) {
                deque.pollLast();
            }
            deque.offerLast(i);
            if (i >= k - 1) {
                res[i - k + 1] = nums[deque.peekFirst()];
            }
        }
        return res;
    }

    public int[] maxSlidingWindow2(int[] nums, int k) {
        int[] res = new int[nums.length - k + 1];
        PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b) -> b[0] - a[0] != 0 ? b[0] - a[0] : b[1] - a[1]);
        for (int i = 0; i < nums.length; i++) {
            maxHeap.offer(new int[] { nums[i], i });
            if (i >= k - 1) {
                while (maxHeap.peek()[1] < i - k + 1) {
                    maxHeap.poll();
                }
                res[i - k + 1] = maxHeap.peek()[0];
            }
        }
        return res;
    }

    public int[] maxSlidingWindow3(int[] nums, int k) {
        int n = nums.length;
        int[] left = new int[n];
        int[] right = new int[n];
        for (int i = 0; i < n; i++) {
            if (i % k == 0) {
                left[i] = nums[i];
            } else {
                left[i] = Math.max(left[i - 1], nums[i]);
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            if (i == n - 1 || (i + 1) % k == 0) {
                right[i] = nums[i];
            } else {
                right[i] = Math.max(right[i + 1], nums[i]);
            }
        }
        int[] res = new int[n - k + 1];
        for (int i = 0; i <= n - k; i++) {
            res[i] = Math.max(left[i + k - 1], right[i]);
        }
        return res;
    }

    public static void main(String[] args) {
        Solution0239 solution0239 = new Solution0239();
        int[] nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
        int k = 3;
        System.out.println(Arrays.toString(solution0239.maxSlidingWindow(nums, k)));
        System.out.println(Arrays.toString(solution0239.maxSlidingWindow2(nums, k)));
        System.out.println(Arrays.toString(solution0239.maxSlidingWindow3(nums, k)));
    }
}
