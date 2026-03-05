package anew;

// 给定一个长度为 n 的 0 索引整数数组 nums。初始位置在下标 0。

// 每个元素 nums[i] 表示从索引 i 向后跳转的最大长度。换句话说，如果你在索引 i 处，你可以跳转到任意 (i + j) 处：

// 0 <= j <= nums[i] 且
// i + j < n
// 返回到达 n - 1 的最小跳跃次数。测试用例保证可以到达 n - 1

public class Solution0045 {
    public int jump(int[] nums) {
        int n = nums.length;
        int[][] dp = new int[n][2];
        dp[0][0] = 0;
        dp[0][1] = nums[0];
        for (int i = 1; i < n; i++) {
            dp[i][0] = Integer.MAX_VALUE;
            for (int j = 0; j < i; j++) {
                if (i <= dp[j][1]) {
                    dp[i][0] = Math.min(dp[i][0], dp[j][0] + 1);
                    dp[i][1] = Math.max(dp[i][1], i + nums[i]);
                }
            }
        }
        return dp[n - 1][0];
    }

    // dp[i][0]是非递减的，所以可以用一个指针j来找到第一个可以跳到i的下标
    public int jump2(int[] nums) {
        int n = nums.length;
        int[] dp = new int[n];
        dp[0] = 0;

        int j = 0;
        for (int i = 1; i < n; i++) {
            while (j + nums[j] < i) {
                j++;
            }
            dp[i] = dp[j] + 1;
        }
        return dp[n - 1];
    }

    public int jump3(int[] nums) {
        int n = nums.length;
        int jump = 0;
        int curMaxReach = 0;
        int nextMaxReach = 0;
        for (int i = 0; i < n - 1; i++) {
            nextMaxReach = Math.max(nextMaxReach, i + nums[i]);
            if (i == curMaxReach) {
                jump++;
                curMaxReach = nextMaxReach;
            }
        }
        return jump;
    }

    public static void main(String[] args) {
        Solution0045 solution = new Solution0045();
        int[] nums = { 2, 3, 1, 1, 4 };
        System.out.println(solution.jump(nums));
        System.out.println(solution.jump2(nums));
        System.out.println(solution.jump3(nums));
        int[] nums2 = { 2, 3, 0, 1, 4 };
        System.out.println(solution.jump(nums2));
        System.out.println(solution.jump2(nums2));
        System.out.println(solution.jump3(nums2));
    }
}
