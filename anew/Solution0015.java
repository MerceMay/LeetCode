package anew;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Solution0015 {
    public List<List<Integer>> threeSum(int[] nums) {
        List<List<Integer>> res = new ArrayList<>();
        Arrays.sort(nums);
        for (int left = 0; left < nums.length - 2; left++) {
            if (left > 0 && nums[left] == nums[left - 1]) {
                continue;
            }
            int mid = left + 1;
            int right = nums.length - 1;
            while (mid < right) {
                int sum = nums[left] + nums[mid] + nums[right];
                if (sum == 0) {
                    res.add(List.of(nums[left], nums[mid], nums[right]));
                    while (mid < right && nums[mid] == nums[mid + 1]) {
                        mid++;
                    }
                    while (mid < right && nums[right] == nums[right - 1]) {
                        right--;
                    }
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
}
