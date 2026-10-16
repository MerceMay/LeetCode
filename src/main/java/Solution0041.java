//给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。
//
//请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。

public class Solution0041 {
    public int firstMissingPositive(int[] nums) {
        int n = nums.length;
        for (int i = 0; i < n; i++) {
            while (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1]) {
                int index = nums[i] - 1;
                int temp = nums[index];
                nums[index] = nums[i];
                nums[i] = temp;
            }
        }
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1;
    }
}
