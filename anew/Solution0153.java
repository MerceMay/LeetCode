package anew;

// 已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次 旋转 后，得到输入数组。例如，原数组 nums = [0,1,2,4,5,6,7] 在变化后可能得到：
// 若旋转 4 次，则可以得到 [4,5,6,7,0,1,2]
// 若旋转 7 次，则可以得到 [0,1,2,4,5,6,7]
// 注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0], a[1], a[2], ..., a[n-2]] 。

// 给你一个元素值 互不相同 的数组 nums ，它原来是一个升序排列的数组，并按上述情形进行了多次旋转。请你找出并返回数组中的 最小元素 。

// 你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。

public class Solution0153 {
    public int findMin(int[] nums) {
        int left = 0, right = nums.length - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < nums[right]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return nums[left];
    }

    private int minimum = Integer.MAX_VALUE;

    public int findMin2(int[] nums) {
        binarySearch(nums, 0, nums.length - 1);
        return minimum;
    }

    private void binarySearch(int[] nums, int left, int right) {
        if (left > right)
            return;
        if (left == right || nums[left] < nums[right]) {
            minimum = Math.min(minimum, nums[left]);
            return;
        }
        int mid = left + (right - left) / 2;
        binarySearch(nums, left, mid);
        binarySearch(nums, mid + 1, right);
    }

    public static void main(String[] args) {
        Solution0153 solution = new Solution0153();
        int[] nums = { 4, 5, 6, 7, 0, 1, 2 };
        System.out.println(solution.findMin(nums)); // 输出: 0
        System.out.println(solution.findMin2(nums)); // 输出: 0
    }
}
