package anew;

// 给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除了 nums[i] 之外其余各元素的乘积 。

// 题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。

// 请 不要使用除法，且在 O(n) 时间复杂度内完成此题。

public class Solution0238 {
    public int[] productExceptSelf(int[] nums) {
        int n = nums.length;
        int[] answer = new int[n];
        int prefixProduct = 1;
        for (int i = 0; i < n; i++) {
            answer[i] = prefixProduct;
            prefixProduct *= nums[i];
        }
        int suffixProduct = 1;
        for (int i = n - 1; i >= 0; i--) {
            answer[i] *= suffixProduct;
            suffixProduct *= nums[i];
        }
        return answer;
    }

    public int[] productExceptSelf2(int[] nums) {
        int n = nums.length;
        int[] prefixProducts = new int[n];
        int[] suffixProducts = new int[n];
        prefixProducts[0] = 1;
        for (int i = 1; i < n; i++) {
            prefixProducts[i] = prefixProducts[i - 1] * nums[i - 1];
        }
        suffixProducts[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            suffixProducts[i] = suffixProducts[i + 1] * nums[i + 1];
        }
        int[] answer = new int[n];
        for (int i = 0; i < n; i++) {
            answer[i] = prefixProducts[i] * suffixProducts[i];
        }
        return answer;
    }

    public static void main(String[] args) {
        int[] nums = { 1, 2, 3, 4 };
        int[] result1 = new Solution0238().productExceptSelf(nums);
        for (int num : result1) {
            System.out.print(num + " ");
        }
        System.out.println();

        int[] result2 = new Solution0238().productExceptSelf2(nums);
        for (int num : result2) {
            System.out.print(num + " ");
        }
    }
}
