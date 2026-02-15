package hot100;
// 给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。

import java.util.Map;
import java.util.HashMap;

// 子数组是数组中元素的连续非空串行。
public class Solution0560 {
    public int subarraySum(int[] nums, int k) {
        int sum = 0;
        int count = 0;
        Map<Integer, Integer> map = new HashMap<>();
        map.put(0, 1);
        for (int num : nums) {
            sum += num;
            if (map.containsKey(sum - k)) {
                count += map.get(sum - k);
            }
            map.put(sum, map.getOrDefault(sum, 0) + 1);
        }
        return count;
    }

    public static void main(String[] args) {
        Solution0560 solution0560 = new Solution0560();
        int[] nums = { 1, 1, 1 };
        int k = 2;
        System.out.println(solution0560.subarraySum(nums, k));
    }
}
