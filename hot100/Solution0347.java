package hot100;

import java.util.PriorityQueue;
import java.util.Map;
import java.util.HashMap;

// 给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。
public class Solution0347 {
    public int[] topKFrequent(int[] nums, int k) {
        PriorityQueue<int[]> minHeap = new PriorityQueue<>((a, b) -> a[1] - b[1]);
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : nums) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }
        for (Map.Entry<Integer, Integer> entry : frequencyMap.entrySet()) {
            int num = entry.getKey();
            int freq = entry.getValue();
            if (minHeap.size() < k) {
                minHeap.offer(new int[] { num, freq });
            } else if (freq > minHeap.peek()[1]) {
                minHeap.poll();
                minHeap.offer(new int[] { num, freq });
            }
        }
        int[] result = new int[k];
        for (int i = 0; i < k; i++) {
            result[i] = minHeap.poll()[0];
        }
        return result;
    }

    public int[] topKFrequent2(int[] nums, int k) {
        PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b) -> b[1] - a[1]);
        Map<Integer, Integer> frequencyMap = new HashMap<>();
        for (int num : nums) {
            frequencyMap.put(num, frequencyMap.getOrDefault(num, 0) + 1);
        }
        for (Map.Entry<Integer, Integer> entry : frequencyMap.entrySet()) {
            int num = entry.getKey();
            int freq = entry.getValue();
            maxHeap.offer(new int[] { num, freq });
        }
        int[] result = new int[k];
        for (int i = 0; i < k; i++) {
            result[i] = maxHeap.poll()[0];
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
    }
}
