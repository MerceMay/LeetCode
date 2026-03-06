package anew;

// 给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续 子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

// 测试用例的答案是一个 32-位 整数。

// 请注意，一个只包含一个元素的数组的乘积是这个元素的值。

public class Solution0152 {
    public int maxProduct(int[] nums) {
        int n = nums.length;
        int[] maxDp = new int[n];
        maxDp[0] = nums[0];
        int maxProduct = maxDp[0];
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                maxDp[i] = Math.max(maxDp[i], maxDp[j] * nums[i]);
            }
            maxDp[i] = Math.max(maxDp[i], nums[i]);
        }

    }

    public static void main(String[] args) {
        Solution0152 solution = new Solution0152();
        int[] nums = { 2, 3, -2, 4 };
        int result = solution.maxProduct(nums);
        System.out.println(result); // 输出: 6 (子数组 [2,3] 的乘积最大)
    }
}
