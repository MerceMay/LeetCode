package anew;

// 给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。

// 如果数组中不存在目标值 target，返回 [-1, -1]。

// 你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。

public class Solution0034 {
    public int[] searchRange(int[] nums, int target) {
        int left = 0, right = nums.length - 1;
        int begin = -1, end = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                begin = mid;
                end = mid;
                while (begin - 1 >= 0 && nums[begin - 1] == target) {
                    begin--;
                }
                while (end + 1 < nums.length && nums[end + 1] == target) {
                    end++;
                }
                break;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return new int[] { begin, end };
    }

    private int left = -1;
    private int right = -1;

    public int[] searchRange2(int[] nums, int target) {
        binarySearch(nums, target, 0, nums.length - 1);
        return new int[] { left, right };
    }

    private void binarySearch(int[] nums, int target, int left, int right) {
        if (left > right) {
            return;
        }
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            if (this.left == -1 || mid < this.left) {
                this.left = mid;
            }
            if (this.right == -1 || mid > this.right) {
                this.right = mid;
            }
            binarySearch(nums, target, left, mid - 1);
            binarySearch(nums, target, mid + 1, right);
        } else if (nums[mid] < target) {
            binarySearch(nums, target, mid + 1, right);
        } else {
            binarySearch(nums, target, left, mid - 1);
        }
    }

    public int[] searchRange3(int[] nums, int target) {
        int left = binarySearch2(nums, target, true);
        int right = binarySearch2(nums, target, false);
        if (left == nums.length || nums[left] != target) {
            return new int[] { -1, -1 };
        }
        return new int[] { left, right - 1 };

    }

    private int binarySearch2(int[] nums, int target, boolean lower) {
        int left = 0, right = nums.length - 1;
        int ans = nums.length;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > target || (lower && nums[mid] >= target)) {
                right = mid - 1;
                ans = mid;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution0034 solution = new Solution0034();
        int[] nums = { 5, 7, 7, 8, 8, 10 };
        int target = 8;
        int[] result = solution.searchRange(nums, target);
        System.out.println("[" + result[0] + ", " + result[1] + "]"); // 输出: [3, 4]
        int[] result2 = solution.searchRange2(nums, target);
        System.out.println("[" + result2[0] + ", " + result2[1] + "]"); // 输出: [3, 4]
        int[] result3 = solution.searchRange3(nums, target);
        System.out.println("[" + result3[0] + ", " + result3[1] + "]"); // 输出: [3, 4]
    }
}
