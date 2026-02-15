package hot100;

// 给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除了 nums[i] 之外其余各元素的乘积 。

// 题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。

// 请 不要使用除法，且在 O(n) 时间复杂度内完成此题。
public class Solution0238 {
    public int[] productExceptSelf(int[] nums) {
        int[] prefixProducts = new int[nums.length];
        int[] suffixProducts = new int[nums.length];
        prefixProducts[0] = 1;
        for (int i = 1; i < nums.length; i++) {
            prefixProducts[i] = prefixProducts[i - 1] * nums[i - 1];
        }
        suffixProducts[nums.length - 1] = 1;
        for (int i = nums.length - 2; i >= 0; i--) {
            suffixProducts[i] = suffixProducts[i + 1] * nums[i + 1];
        }
        int[] result = new int[nums.length];
        for (int i = 0; i < nums.length; i++) {
            result[i] = prefixProducts[i] * suffixProducts[i];
        }
        return result;
    }

    public int[] productExceptSelf2(int[] nums) {
        int[] result = new int[nums.length];
        int prefixProduct = 1;
        for (int i = 0; i < nums.length; i++) {
            result[i] = prefixProduct;
            prefixProduct *= nums[i];
        }
        int suffixProduct = 1;
        for (int i = nums.length - 1; i >= 0; i--) {
            result[i] *= suffixProduct;
            suffixProduct *= nums[i];
        }
        return result;
    }

    public static void main(String[] args) {
        int[] nums = { 1, 2, 3, 4 };
        int[] result1 = new Solution0238().productExceptSelf(nums);
        int[] result2 = new Solution0238().productExceptSelf2(nums);
        System.out.println("Method 1 result:");
        for (int num : result1) {
            System.out.print(num + " ");
        }
        System.out.println("\nMethod 2 result:");
        for (int num : result2) {
            System.out.print(num + " ");
        }
    }
}
