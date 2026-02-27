package anew;

// 给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。

public class Solution0189 {
    public void rotate(int[] nums, int k) {
        int n = nums.length;
        k = k % n;
        int count = gcd(n, k);
        for (int i = 0; i < count; i++) {
            int current = i;
            int currentValue = nums[current];
            do {
                int next = (current + k) % n;
                int temp = nums[next];
                nums[next] = currentValue;
                currentValue = temp;
                current = next;
            } while (current != i);
        }
    }

    private int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    public void rotate2(int[] nums, int k) {
        int[] temp = new int[nums.length];
        for (int i = 0; i < nums.length; i++) {
            temp[(i + k) % nums.length] = nums[i];
        }
        System.arraycopy(temp, 0, nums, 0, nums.length);
    }

    public void rotate3(int[] nums, int k) {
        k = k % nums.length;
        reverse(nums, 0, nums.length - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, nums.length - 1);
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

    public static void main(String[] args) {
        int[] nums = { 1, 2, 3, 4, 5, 6, 7 };
        int k = 3;
        new Solution0189().rotate(nums, k);
        for (int num : nums) {
            System.out.print(num + " ");
        }
        System.out.println();

        int[] nums2 = { 1, 2, 3, 4, 5, 6, 7 };
        new Solution0189().rotate2(nums2, k);
        for (int num : nums2) {
            System.out.print(num + " ");
        }
        System.out.println();

        int[] nums3 = { 1, 2, 3, 4, 5, 6, 7 };
        new Solution0189().rotate3(nums3, k);
        for (int num : nums3) {
            System.out.print(num + " ");
        }
    }
}
