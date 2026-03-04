package anew;

import java.util.Map;
import java.util.Random;
import java.util.HashMap;
// 给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。

public class Solution0347 {
    private static class MinHeap {
        private int[][] heap;
        private int size;

        public MinHeap(int capacity) {
            heap = new int[capacity][2];
            size = 0;
        }

        public void offer(int num, int freq) {
            heap[size][0] = num;
            heap[size][1] = freq;
            size++;
            heapifyUp(size - 1);
        }

        public int[] poll() {
            if (size == 0) {
                throw new IllegalStateException("Heap is empty");
            }
            int[] top = new int[] { heap[0][0], heap[0][1] };
            heap[0][0] = heap[size - 1][0];
            heap[0][1] = heap[size - 1][1];
            size--;
            heapifyDown(0);
            return top;
        }

        public int[] peek() {
            if (size == 0) {
                throw new IllegalStateException("Heap is empty");
            }
            return heap[0];
        }

        public int size() {
            return size;
        }

        private void swap(int i, int j) {
            int[] temp = heap[i];
            heap[i] = heap[j];
            heap[j] = temp;
        }

        private void heapifyUp(int index) {
            while (index > 0) {
                int parent = (index - 1) / 2;
                if (heap[index][1] < heap[parent][1]) {
                    swap(index, parent);
                    index = parent;
                } else {
                    break;
                }
            }
        }

        private void heapifyDown(int index) {
            while (true) {
                int left = 2 * index + 1;
                int right = 2 * index + 2;
                int smallest = index;

                if (left < size && heap[left][1] < heap[smallest][1]) {
                    smallest = left;
                }
                if (right < size && heap[right][1] < heap[smallest][1]) {
                    smallest = right;
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

    public int[] topKFrequent(int[] nums, int k) {
        MinHeap minHeap = new MinHeap(k);
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : nums) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }
        for (Map.Entry<Integer, Integer> entry : frequencyMap.entrySet()) {
            int num = entry.getKey();
            int freq = entry.getValue();
            if (minHeap.size() < k) {
                minHeap.offer(num, freq);
            } else if (freq > minHeap.peek()[1]) {
                minHeap.poll();
                minHeap.offer(num, freq);
            }
        }
        int[] result = new int[k];
        for (int i = k - 1; i >= 0; i--) {
            result[i] = minHeap.poll()[0];
        }
        return result;
    }

    private int[] topKFrequent2(int[] nums, int k) {
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : nums) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }
        int[][] freqArray = new int[frequencyMap.size()][2];
        int index = 0;
        for (Map.Entry<Integer, Integer> entry : frequencyMap.entrySet()) {
            int num = entry.getKey();
            int freq = entry.getValue();
            freqArray[index][0] = num;
            freqArray[index][1] = freq;
            index++;
        }
        for (int i = freqArray.length / 2 - 1; i >= 0; i--) {
            heapify(freqArray, i, freqArray.length);
        }
        int[] result = new int[k];
        for (int i = 0; i < k; i++) {
            result[i] = freqArray[0][0];
            freqArray[0][0] = freqArray[freqArray.length - 1 - i][0];
            freqArray[0][1] = freqArray[freqArray.length - 1 - i][1];
            heapify(freqArray, 0, freqArray.length - 1 - i);
        }
        return result;
    }

    private void heapify(int[][] array, int index, int size) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && array[left][1] > array[largest][1]) {
                largest = left;
            }
            if (right < size && array[right][1] > array[largest][1]) {
                largest = right;
            }
            if (largest != index) {
                int[] temp = array[index];
                array[index] = array[largest];
                array[largest] = temp;
                index = largest;
            } else {
                break;
            }
        }
    }

    public int[] topKFrequent3(int[] nums, int k) {
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : nums) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }
        int[][] freqArray = new int[frequencyMap.size()][2];
        int index = 0;
        for (Map.Entry<Integer, Integer> entry : frequencyMap.entrySet()) {
            int num = entry.getKey();
            int freq = entry.getValue();
            freqArray[index][0] = num;
            freqArray[index][1] = freq;
            index++;
        }
        quickSelect(freqArray, 0, freqArray.length - 1, k);
        int[] result = new int[k];
        for (int i = 0; i < k; i++) {
            result[i] = freqArray[i][0];
        }
        return result;
    }

    private static final Random RANDOM = new Random();

    private void quickSelect(int[][] array, int left, int right, int k) {
        if (left >= right) {
            return;
        }
        int pivotIndex = left + RANDOM.nextInt(right - left + 1);
        swap(array, pivotIndex, left);
        int pivotFreq = array[left][1];
        int i = left - 1, j = right + 1;
        while (i < j) {
            do {
                i++;
            } while (array[i][1] > pivotFreq);
            do {
                j--;
            } while (array[j][1] < pivotFreq);
            if (i < j) {
                swap(array, i, j);
            }
        }
        int leftSize = j - left + 1;
        if (k == leftSize) {
            return;
        } else if (k < leftSize) {
            quickSelect(array, left, j, k);
        } else {
            quickSelect(array, j + 1, right, k - leftSize);
        }
    }

    private void swap(int[][] array, int i, int j) {
        int[] temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    public int[] topKFrequent4(int[] nums, int k) {
        int min = nums[0], max = nums[0];
        for (int num : nums) {
            min = Math.min(min, num);
            max = Math.max(max, num);
        }
        int[] frequency = new int[max - min + 1];
        for (int num : nums) {
            frequency[num - min]++;
        }
        int maxFreq = 0;
        for (int freq : frequency) {
            maxFreq = Math.max(maxFreq, freq);
        }
        int[] result = new int[k];
        int index = 0;
        while (index < k && maxFreq > 0) {
            for (int i = 0; i < frequency.length; i++) {
                if (frequency[i] == maxFreq) {
                    result[index++] = i + min;
                    if (index == k) {
                        break;
                    }
                }
            }
            maxFreq--;
        }
        return result;
    }

    public static void main(String[] args) {
        Solution0347 solution = new Solution0347();
        int[] nums = { 1, 1, 1, 2, 2, 3 };
        int k = 2;
        int[] result = solution.topKFrequent(nums, k);
        for (int num : result) {
            System.out.print(num + " ");
        }

        int[] result2 = solution.topKFrequent2(nums, k);
        System.out.println();
        for (int num : result2) {
            System.out.print(num + " ");
        }
        int[] result3 = solution.topKFrequent3(nums, k);
        System.out.println();
        for (int num : result3) {
            System.out.print(num + " ");
        }
        int[] result4 = solution.topKFrequent4(nums, k);
        System.out.println();
        for (int num : result4) {
            System.out.print(num + " ");
        }
    }
}
