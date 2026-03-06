package anew;

// 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

// 子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。

public class Solution0300 {
    public int lengthOfLIS(int[] nums) {
        // 注意，子序列不要求连续，只要保持相对顺序即可。
        int n = nums.length;
        int[] dp = new int[n];
        dp[0] = 1;
        int maxLen = 1;
        for (int i = 1; i < n; i++) {
            dp[i] = 1;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    dp[i] = Math.max(dp[i], dp[j] + 1);
                }
            }
            maxLen = Math.max(maxLen, dp[i]);
        }
        return dp[n - 1];
    }

    public int lengthOfLIS2(int[] nums) {
        // 维护一个最优候选数组 tails，其中 tails[k] 存储长度为 k+1 的递增子序列的末尾元素的最小值。
        int[] tails = new int[nums.length];
        int size = 0;

        for (int num : nums) {
            int left = 0, right = size;
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (tails[mid] < num) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            tails[left] = num;
            if (left == size) {
                size++;
            }
        }
        return size;
    }

    public static void main(String[] args) {
        Solution0300 solution = new Solution0300();
        int[] nums = { 10, 9, 2, 5, 3, 7, 101, 18 };
        int result = solution.lengthOfLIS(nums);
        System.out.println(result); // 输出: 4 (最长递增子序列是 [2,3,7,101])

        int result2 = solution.lengthOfLIS2(nums);
        System.out.println(result2); // 输出: 4 (最长递增子序列是 [2,3,7,101])
    }
}
