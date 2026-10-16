import java.util.*;

//给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。
//
//子数组是数组中元素的连续非空序列。

public class Solution0560 {
    public int subarraySum(int[] nums, int k) {
        int curSum = 0;
        int result = 0;
        Map<Integer, Integer> map = new HashMap<>();
        map.put(0, 1);
        for (int num : nums) {
            curSum += num;
            result += map.getOrDefault(curSum - k, 0);
            map.put(curSum, map.getOrDefault(curSum, 0) + 1);
        }
        return result;
    }
}
