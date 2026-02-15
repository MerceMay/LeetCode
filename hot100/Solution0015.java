package hot100;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

// 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。

// 注意：答案中不可以包含重复的三元组。
public class Solution0015 {
    public List<List<Integer>> threeSum(int[] nums) {
        List<List<Integer>> res = new ArrayList<>();
        Arrays.sort(nums);
        for (int left = 0; left < nums.length - 2; left++) {
            if (left > 0 && nums[left] == nums[left - 1])
                continue;
            int mid = left + 1;
            int right = nums.length - 1;
            while (mid < right) {
                int sum = nums[left] + nums[mid] + nums[right];
                if (sum == 0) {
                    res.add(Arrays.asList(nums[left], nums[mid], nums[right]));
                    while (mid < right && nums[mid] == nums[mid + 1])
                        mid++;
                    while (mid < right && nums[right] == nums[right - 1])
                        right--;
                    mid++;
                    right--;
                } else if (sum < 0) {
                    mid++;
                } else {
                    right--;
                }
            }
        }
        return res;
    }

    public static void main(String[] args) {
        Solution0015 solution = new Solution0015();
        int[] nums = { -1, 0, 1, 2, -1, -4 };
        List<List<Integer>> res = solution.threeSum(nums);
        System.out.println(res);
    }
}
