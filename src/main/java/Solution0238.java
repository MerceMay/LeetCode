import java.util.*;

//给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除了 nums[i] 之外其余各元素的乘积 。
//
//题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。
//
//请 不要使用除法，且在 O(n) 时间复杂度内完成此题。

public class Solution0238 {
    public int[] produceExceptSelf(int[] nums) {
        int n = nums.length;
        int[] leftProduct = new int[n];
        int[] rightProduct = new int[n];
        leftProduct[0] = 1;
        for (int i = 1; i < n; i++) {
            leftProduct[i] = leftProduct[i - 1] * nums[i - 1];
        }
        rightProduct[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            rightProduct[i] = rightProduct[i + 1] * nums[i + 1];
        }
        int[] result = new int[n];
        for (int i = 0; i < n; i++) {
            result[i] = leftProduct[i] * rightProduct[i];
        }
        return result;
    }

    public int[] productExceptSelf2(int[] nums) {
        int n = nums.length;
        int[] result = new int[n];
        result[0] = 1;
        for (int i = 1; i < n; i++) {
            result[i] = result[i - 1] * nums[i - 1];
        }
        int r = 1;
        for (int i = n - 2; i >= 0; i--) {
            r = r * nums[i + 1];
            result[i] *= r;
        }
        return result;
    }
}
