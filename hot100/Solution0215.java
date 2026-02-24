package hot100;

import java.util.PriorityQueue;
import java.util.List;
import java.util.ArrayList;

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

    class minHeap {
        private List<Integer> heap;

        public minHeap(int capacity) {
            this.heap = new ArrayList<>();
        }

        public void offer(int num) {
            heap.add(num);
            heapifyUp(heap.size() - 1);
        }

        public void poll() {
            if (heap.isEmpty()) {
                return;
            }
            swap(0, heap.size() - 1);
            heap.remove(heap.size() - 1);
            heapifyDown(0);
        }

        public int peek() {
            return heap.get(0);
        }

        public boolean isEmpty() {
            return heap.isEmpty();
        }

        public int size() {
            return heap.size();
        }

        private void swap(int i, int j) {
            int temp = heap.get(i);
            heap.set(i, heap.get(j));
            heap.set(j, temp);
        }

        private void heapifyUp(int index) {
            while (index > 0) {
                int parentIndex = (index - 1) / 2;
                if (heap.get(index) < heap.get(parentIndex)) {
                    swap(index, parentIndex);
                    index = parentIndex;
                } else {
                    break;
                }
            }
        }

        private void heapifyDown(int index) {
            int size = heap.size();
            while (true) {
                int leftChild = 2 * index + 1;
                int rightChild = 2 * index + 2;
                int smallest = index;

                if (leftChild < size && heap.get(leftChild) < heap.get(smallest)) {
                    smallest = leftChild;
                }
                if (rightChild < size && heap.get(rightChild) < heap.get(smallest)) {
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
        minHeap minHeap = new minHeap(k);
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
            heapify(nums, i, heapSize); // 从最后一个非叶子节点开始进行堆化
        }
        for (int i = nums.length - 1; i >= nums.length - k; i--) {
            swap(nums, 0, i); // 将堆顶元素与当前末尾元素交换
            heapify(nums, 0, i); // 重新堆化剩余的元素
        }
        return nums[nums.length - k]; // 返回第 k 个最大的元素
    }

    private void heapify(int[] nums, int index, int heapSize) {
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
            heapify(nums, largest, heapSize); // 递归堆化
        }
    }

    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    public int findKthLargest5(int[] nums, int k) {
        return quickSelect(nums, 0, nums.length - 1, nums.length - k);
    }

    private int quickSelect(int[] nums, int left, int right, int k) {
        if (left == right) {
            return nums[left];
        }
        int pivot = nums[left]; // 选择第一个元素作为基准
        int i = left + 1;
        for (int j = left + 1; j <= right; j++) {
            if (nums[j] < pivot) {
                swap(nums, i, j);
                i++;
            }
        }
        swap(nums, left, i - 1); // 将基准元素放到正确的位置
        if (i - 1 == k) {
            return nums[i - 1]; // 找到第 k 个元素
        } else if (i - 1 < k) {
            return quickSelect(nums, i, right, k); // 在右侧继续查找
        } else {
            return quickSelect(nums, left, i - 2, k); // 在左侧继续查找
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
    }
}
