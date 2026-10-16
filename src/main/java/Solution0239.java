import java.util.*;

//给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
//
//返回 滑动窗口中的最大值 。

public class Solution0239 {
    public int[] maxSlidingWindow(int[] nums, int k) {
        int n = nums.length;
        PriorityQueue<int[]> pq = new PriorityQueue<>((o1, o2) ->
                o1[0] != o2[0] ? o2[0] - o1[0] : o2[1] - o1[1]
        );
        for (int i = 0; i < k; i++) {
            pq.add(new int[]{nums[i], i});
        }
        int[] result = new int[n - k + 1];
        result[0] = pq.peek()[0];
        for (int i = k; i < n; i++) {
            pq.offer(new int[]{nums[i], i});
            while (pq.peek()[1] <= i - k) {
                pq.poll();
            }
            result[i - k + 1] = pq.peek()[0];
        }
        return result;
    }

    public int[] maxSlidingWindow2(int[] nums, int k) {
        int n = nums.length;
        Deque<Integer> deque = new ArrayDeque<>();
        for (int i = 0; i < k; i++) {
            while (!deque.isEmpty() && nums[deque.peekLast()] <= nums[i]) {
                deque.pollLast();
            }
            deque.offerLast(i);
        }
        int[] result = new int[n - k + 1];
        result[0] = nums[deque.peekFirst()];
        for (int i = k; i < n; i++) {
            while (!deque.isEmpty() && nums[deque.peekLast()] <= nums[i]) {
                deque.pollLast();
            }
            deque.offerLast(i);
            while (deque.peekFirst() <= i - k) {
                deque.pollFirst();
            }
            result[i - k + 1] = nums[deque.peekFirst()];
        }
        return result;
    }

    public int[] maxSlidingWindow3(int[] nums, int k) {
        int n = nums.length;
        int[] prefixMax = new int[n];
        int[] suffixMax = new int[n];
        for (int i = 0; i < n; i++) {
            if (i % k == 0) {
                prefixMax[i] = nums[i];
            } else {
                prefixMax[i] = Math.max(prefixMax[i - 1], nums[i]);
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            if (i == n - 1 || (i + 1) % k == 0) {
                suffixMax[i] = nums[i];
            } else {
                suffixMax[i] = Math.max(suffixMax[i + 1], nums[i]);
            }
        }
        int[] result = new int[n - k + 1];
        for (int i = 0; i <= n - k; i++) {
            result[i] = Math.max(suffixMax[i], prefixMax[i + k - 1]);
        }
        return result;
    }
}
