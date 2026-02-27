package anew;

import java.util.Map;
import java.util.HashMap;

// 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

// 你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。

// 你可以按任意顺序返回答案。

public class Solution0001 {
    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            if (map.containsKey(target - nums[i])) {
                return new int[] { i, map.get(target - nums[i]) };
            }
            map.put(nums[i], i);
        }
        return new int[0];
    }

    public static void main(String[] args) {
        Solution0001 solution0001 = new Solution0001();
        int[] nums = { 2, 7, 11, 15 };
        int target = 9;
        int[] result = solution0001.twoSum(nums, target);
        System.out.println("Indices: [" + result[0] + ", " + result[1] + "]");
    }
}
