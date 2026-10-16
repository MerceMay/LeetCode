import java.util.*;

//给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。
//
//如果数组中不存在目标值 target，返回 [-1, -1]。
//
//你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。

public class Solution0034 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int target = sc.nextInt();
        int[] nums = Arrays.stream(line.substring(1, line.length() - 1).split(","))
                .mapToInt(Integer::parseInt)
                .toArray();
        System.out.println(Arrays.toString(searchRange(nums, target)));
    }

    public static int[] searchRange(int[] nums, int target) {
        if (nums.length == 0) {
            return new int[]{-1, -1};
        }
        int leftRes = lowerBound(nums, target);
        if (leftRes == nums.length || nums[leftRes] != target) {
            return new int[]{-1, -1};
        }
        int rightRes = upperBound(nums, target) - 1;

        return new int[]{leftRes, rightRes};
    }

    private static int lowerBound(int[] nums, int target) {
        int left = 0, right = nums.length;
        while (left < right) {
            int mid = left + ((right - left) >> 1);
            if (nums[mid] >= target) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }

    private static int upperBound(int[] nums, int target) {
        int left = 0, right = nums.length;
        while (left < right) {
            int mid = left + ((right - left) >> 1);
            if (nums[mid] > target) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
}
