package anew;

import java.util.List;
import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Random;

// 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。

// 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

// 你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。

public class Solution0215 {
    public int findKthLargest(int[] nums, int k) {
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        for (int num : nums) {
            if (minHeap.size() < k) {
                minHeap.offer(num);
            } else if (num > minHeap.peek()) {
                minHeap.poll();
                minHeap.offer(num);
            }
        }
        return minHeap.peek();
    }

    public int findKthLargest2(int[] nums, int k) {
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>((a, b) -> b - a);
        for (int num : nums) {
            maxHeap.offer(num);
        }
        for (int i = 0; i < k - 1; i++) {
            maxHeap.poll();
        }
        return maxHeap.peek();
    }

    private static class MinHeap {
        private List<Integer> minHeap;

        public MinHeap() {
            minHeap = new ArrayList<>();
        }

        public void offer(int val) {
            minHeap.add(val);
            heapifyUp(minHeap.size() - 1);
        }

        public void poll() {
            if (minHeap.isEmpty()) {
                return;
            }
            swap(0, minHeap.size() - 1);
            minHeap.remove(minHeap.size() - 1);
            heapifyDown(0);
        }

        public int peek() {
            return minHeap.get(0);
        }

        public int size() {
            return minHeap.size();
        }

        private void swap(int i, int j) {
            int temp = minHeap.get(i);
            minHeap.set(i, minHeap.get(j));
            minHeap.set(j, temp);
        }

        private void heapifyUp(int index) {
            while (index > 0) {
                int parentIndex = (index - 1) / 2;
                if (minHeap.get(parentIndex) > minHeap.get(index)) {
                    swap(index, parentIndex);
                    index = parentIndex;
                } else {
                    break;
                }
            }
        }

        private void heapifyDown(int index) {
            int size = minHeap.size();
            while (true) {
                int leftChild = 2 * index + 1;
                int rightChild = 2 * index + 2;
                int smallest = index;

                if (leftChild < size && minHeap.get(leftChild) < minHeap.get(smallest)) {
                    smallest = leftChild;
                }
                if (rightChild < size && minHeap.get(rightChild) < minHeap.get(smallest)) {
                    smallest = rightChild;
                }

                if (smallest != index) {
                    swap(index, smallest);
                    index = smallest;
                } else {
                    break;
                }
            }
        }
    }

    public int findKthLargest3(int[] nums, int k) {
        MinHeap minHeap = new MinHeap();
        for (int num : nums) {
            if (minHeap.size() < k) {
                minHeap.offer(num);
            } else if (num > minHeap.peek()) {
                minHeap.poll();
                minHeap.offer(num);
            }
        }
        return minHeap.peek();
    }

    public int findKthLargest4(int[] nums, int k) {
        int heapSize = nums.length;
        for (int i = heapSize / 2 - 1; i >= 0; i--) {
            heapify(nums, heapSize, i);
        }
        for (int i = heapSize - 1; i >= heapSize - k; i--) {
            swap(nums, 0, i);
            heapify(nums, i, 0);
        }
        return nums[heapSize - k];
    }

    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    private void heapify(int[] nums, int heapSize, int index) {
        int largest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;

        if (leftChild < heapSize && nums[leftChild] > nums[largest]) {
            largest = leftChild;
        }
        if (rightChild < heapSize && nums[rightChild] > nums[largest]) {
            largest = rightChild;
        }
        if (largest != index) {
            swap(nums, index, largest);
            heapify(nums, heapSize, largest);
        }
    }

    public int findKthLargest5(int[] nums, int k) {
        return quickSelect(nums, 0, nums.length - 1, nums.length - k);
    }

    private int quickSelect(int[] nums, int left, int right, int k) {
        if (left == right) {
            return nums[left];
        }
        int pivot = nums[right];
        int i = left;
        for (int j = left; j < right; j++) {
            if (nums[j] < pivot) {
                swap(nums, i, j);
                i++;
            }
        }
        swap(nums, right, i);
        if (i == k) {
            return nums[i];
        } else if (i < k) {
            return quickSelect(nums, i + 1, right, k);
        } else {
            return quickSelect(nums, left, i - 1, k);
        }
    }

    private static final Random RANDOM = new Random();

    public int findKthLargest6(int[] nums, int k) {
        return quickSelect6(nums, 0, nums.length - 1, nums.length - k);
    }

    private int quickSelect6(int[] nums, int left, int right, int k) {
        if (left == right) {
            return nums[left];
        }
        int pivotIndex = RANDOM.nextInt(right - left + 1) + left;
        swap(nums, left, pivotIndex);
        int pivot = nums[left];
        int i = left - 1;
        int j = right + 1;
        while (i < j) {
            do {
                i++;
            } while (nums[i] < pivot);
            do {
                j--;
            } while (nums[j] > pivot);
            if (i < j) {
                swap(nums, i, j);
            }
        }
        if (k <= j) {
            return quickSelect6(nums, left, j, k);
        } else {
            return quickSelect6(nums, j + 1, right, k);
        }
    }

    public static void main(String[] args) {
        Solution0215 solution = new Solution0215();
        int[] nums = { 3, 2, 1, 5, 6, 4 };
        int k = 2;
        System.out.println(solution.findKthLargest(nums, k)); // 输出: 5
        System.out.println(solution.findKthLargest2(nums, k)); // 输出: 5
        System.out.println(solution.findKthLargest3(nums, k)); // 输出: 5
        System.out.println(solution.findKthLargest4(nums, k)); // 输出: 5
        System.out.println(solution.findKthLargest5(nums, k)); // 输出: 5
        System.out.println(solution.findKthLargest6(nums, k)); // 输出: 5
    }
}
