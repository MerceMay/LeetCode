package anew;

// 给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。

// 判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。

public class Solution0055 {
    public boolean canJump(int[] nums) {
        int n = nums.length;
        boolean[] dp = new boolean[n];
        dp[0] = true;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && j + nums[j] >= i) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n - 1];
    }

    public boolean canJump2(int[] nums) {
        int n = nums.length;
        int[] dp = new int[n];
        dp[0] = nums[0];
        for (int i = 1; i < n; i++) {
            if (i > dp[i - 1]) {
                return false;
            }
            dp[i] = Math.max(dp[i - 1], i + nums[i]);
        }
        return true;
    }

    public boolean canJump3(int[] nums) {
        int n = nums.length;
        int maxReach = nums[0];
        for (int i = 1; i < n; i++) {
            if (i > maxReach) {
                return false;
            }
            maxReach = Math.max(maxReach, i + nums[i]);
        }
        return true;
    }

    public static void main(String[] args) {
        Solution0055 solution = new Solution0055();
        int[] nums = { 2, 3, 1, 1, 4 };
        System.out.println(solution.canJump(nums));
        int[] nums2 = { 3, 2, 1, 0, 4 };
        System.out.println(solution.canJump(nums2));
        System.out.println(solution.canJump2(nums));
        System.out.println(solution.canJump2(nums2));
    }
}
