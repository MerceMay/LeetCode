import java.util.*;

//给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
//
//请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
//
//你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。

public class Solution0215 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int k = sc.nextInt();
        int[] nums = Arrays.stream(line.substring(1, line.length() - 1).split(","))
                .mapToInt(Integer::parseInt)
                .toArray();
        System.out.println(findKthLargest(nums, k));
        System.out.println(findKthLargest2(nums, k));
        System.out.println(findKthLargest3(nums, k));
    }

    public static int findKthLargest(int[] nums, int k) {
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>((a, b) -> b - a);
        for (int num : nums) {
            maxHeap.offer(num);
        }
        for (int i = 0; i < k - 1; i++) {
            maxHeap.poll();
        }
        return maxHeap.peek();
    }

    public static int findKthLargest2(int[] nums, int k) {
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        for (int num : nums) {
            minHeap.offer(num);
            if (minHeap.size() > k) {
                minHeap.poll();
            }
        }
        return minHeap.peek();
    }

    public static int findKthLargest3(int[] nums, int k) {
        int n = nums.length;
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(nums, i, n);
        }
        int heapSize = n;
        for (int i = n - 1; i >= n - k + 1; i--) {
            swap(nums, 0, i);
            heapSize--;
            heapify(nums, 0, heapSize);
        }
        return nums[0];
    }

    private static void heapify(int[] nums, int i, int heapSize) {
        int left = i * 2 + 1, right = i * 2 + 2, largest = i;
        if (left < heapSize && nums[left] > nums[largest]) {
            largest = left;
        }
        if (right < heapSize && nums[right] > nums[largest]) {
            largest = right;
        }
        if (largest != i) {
            swap(nums, i, largest);
            heapify(nums, largest, heapSize);
        }
    }

    private static void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
}
