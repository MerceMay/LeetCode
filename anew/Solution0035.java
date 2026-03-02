package anew;

// 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

// 请必须使用时间复杂度为 O(log n) 的算法。

public class Solution0035 {
    public int searchInsert(int[] nums, int target) {
        int left = 0, right = nums.length - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return left;
    }

    public int searchInsert2(int[] nums, int target) {
        return helper(nums, 0, nums.length - 1, target);
    }

    private int helper(int[] nums, int left, int right, int target) {
        if (left > right) {
            return left;
        }
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            return helper(nums, mid + 1, right, target);
        } else {
            return helper(nums, left, mid - 1, target);
        }
    }

    public static void main(String[] args) {
        Solution0035 solution = new Solution0035();
        int[] nums = { 1, 3, 5, 6 };
        int target = 5;
        System.out.println(solution.searchInsert(nums, target)); // 输出: 2
        System.out.println(solution.searchInsert2(nums, target)); // 输出: 2
    }
}
