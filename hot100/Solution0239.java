package hot100;

import java.util.Arrays;
import java.util.Deque;
import java.util.ArrayDeque;
import java.util.PriorityQueue;

// 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

// 返回 滑动窗口中的最大值 。
public class Solution0239 {
    // 暴力解法，时间复杂度 O(n*k)，空间复杂度 O(n-k+1)
    public int[] maxSlidingWindow1(int[] nums, int k) {
        int[] result = new int[nums.length - k + 1];
        for (int i = 0; i <= nums.length - k; i++) {
            int max = Integer.MIN_VALUE;
            for (int j = i; j < i + k; j++) {
                max = Math.max(max, nums[j]);
            }
            result[i] = max;
        }
        return result;
    }

    // 使用双端队列，时间复杂度 O(n)，空间复杂度 O(k)
    public int[] maxSlidingWindow2(int[] nums, int k) {
        int[] result = new int[nums.length - k + 1];
        Deque<Integer> deque = new ArrayDeque<>();
        for (int i = 0; i < nums.length; i++) {
            if (!deque.isEmpty() && deque.peekFirst() < i - k + 1) {
                deque.pollFirst();
            }
            while (!deque.isEmpty() && nums[deque.peekLast()] < nums[i]) {
                deque.pollLast();
            }
            deque.addLast(i);
            if (i >= k - 1) {
                result[i - k + 1] = nums[deque.peekFirst()];
            }
        }
        return result;
    }

    // 使用大根堆，同时存储元素和索引，时间复杂度 O(n log k)，空间复杂度 O(k)
    public int[] maxSlidingWindow3(int[] nums, int k) {
        int[] result = new int[nums.length - k + 1];
        PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b) -> b[0] - a[0] != 0 ? b[0] - a[0] : b[1] - a[1]);
        for (int i = 0; i < nums.length; i++) {
            maxHeap.offer(new int[] { nums[i], i });
            if (i >= k - 1) {
                while (maxHeap.peek()[1] < i - k + 1) {
                    maxHeap.poll();
                }
                result[i - k + 1] = maxHeap.peek()[0];
            }
        }
        return result;
    }

    // 分块：一个框要么恰好与块对齐，要么跨越两个块。对于每个块，我们预先计算出从左到右的最大值和从右到左的最大值。对于每个窗口，我们可以通过比较两个块的最大值来得到窗口的最大值。时间复杂度
    // O(n)，空间复杂度 O(n)
    public int[] maxSlidingWindow4(int[] nums, int k) {
        int[] result = new int[nums.length - k + 1];
        int[] left = new int[nums.length];
        int[] right = new int[nums.length];
        for (int i = 0; i < nums.length; i++) {
            if (i % k == 0) {
                left[i] = nums[i];
            } else {
                left[i] = Math.max(left[i - 1], nums[i]);
            }
        }
        for (int i = nums.length - 1; i >= 0; i--) {
            if (i == nums.length - 1 || (i + 1) % k == 0) {
                right[i] = nums[i];
            } else {
                right[i] = Math.max(right[i + 1], nums[i]);
            }
        }
        for (int i = 0; i <= nums.length - k; i++) {
            result[i] = Math.max(right[i], left[i + k - 1]);
        }
        return result;
    }

    public static void main(String[] args) {
        Solution0239 solution0239 = new Solution0239();
        int[] nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
        int k = 3;
        System.out.println(Arrays.toString(solution0239.maxSlidingWindow1(nums, k)));
        System.out.println(Arrays.toString(solution0239.maxSlidingWindow2(nums, k)));
        System.out.println(Arrays.toString(solution0239.maxSlidingWindow3(nums, k)));
        System.out.println(Arrays.toString(solution0239.maxSlidingWindow4(nums, k)));
    }
}
