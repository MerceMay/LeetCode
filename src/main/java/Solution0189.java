import java.util.*;

//给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。

public class Solution0189 {
    public void rotate(int[] nums, int k) {
        int n = nums.length;
        k = k % n;
        int[] temp = new int[n];
        for (int i = 0; i < n; i++) {
            temp[(i + k) % n] = nums[i];
        }
        System.arraycopy(temp, 0, nums, 0, n);
    }

    public void rotate2(int[] nums, int k) {
        int n = nums.length;
        k = k % n;
        int gcd = gcd(n, k);
        for (int i = 0; i < gcd; i++) {
            int current = i;
            do {
                int next = (current + k) % n;
                int temp = nums[next];
                nums[next] = nums[i];
                nums[i] = temp;
                current = next;
            } while (current != i);
        }
    }

    private int gcd(int a, int b) {
        return b > 0 ? gcd(b, a % b) : a;
    }

    public void rotate3(int[] nums, int k) {
        int n = nums.length;
        k = k % n;
        reverse(nums, 0, n - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, n - 1);
    }

    private void reverse(int[] nums, int left, int right) {
        while (left < right) {
            int temp = nums[left];
            nums[left] = nums[right];
            nums[right] = temp;
            left++;
            right--;
        }
    }
}
