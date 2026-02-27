package anew;

// 给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

// 子数组是数组中的一个连续部分。

public class Solution0053 {
    public int maxSubArray(int[] nums) {
        int maxSum = Integer.MIN_VALUE;
        int sum = 0;
        for (int i = 0; i < nums.length; i++) {
            sum = Math.max(sum + nums[i], nums[i]);
            maxSum = Math.max(maxSum, sum);
        }
        return maxSum;
    }

    public int maxSubArray2(int[] nums) {
        return maxSubArrayHelper(nums, 0, nums.length - 1);
    }

    private int maxSubArrayHelper(int[] nums, int left, int right) {
        if (left == right) {
            return nums[left];
        }
        int mid = left + (right - left) / 2;
        int leftSubArrayMax = maxSubArrayHelper(nums, left, mid);
        int rightSubArrayMax = maxSubArrayHelper(nums, mid + 1, right);

        int leftCrossMax = Integer.MIN_VALUE;
        int tempSum = 0;
        for (int i = mid; i >= left; i--) {
            tempSum += nums[i];
            leftCrossMax = Math.max(leftCrossMax, tempSum);
        }
        int rightCrossMax = Integer.MIN_VALUE;
        tempSum = 0;
        for (int i = mid + 1; i <= right; i++) {
            tempSum += nums[i];
            rightCrossMax = Math.max(rightCrossMax, tempSum);
        }
        return Math.max(Math.max(leftSubArrayMax, rightSubArrayMax), leftCrossMax + rightCrossMax);
    }

    private record Status(int interval, int segement, int left, int right) {
    }

    public int maxSubArray3(int[] nums) {
        return maxSubArrayHelper3(nums, 0, nums.length - 1).segement;
    }

    private Status maxSubArrayHelper3(int[] nums, int left, int right) {
        if (left == right) {
            return new Status(nums[left], nums[left], nums[left], nums[left]);
        }

        int mid = left + (right - left) / 2;
        Status leftStatus = maxSubArrayHelper3(nums, left, mid);
        Status rightStatus = maxSubArrayHelper3(nums, mid + 1, right);

        return new Status(
                leftStatus.interval + rightStatus.interval,
                Math.max(Math.max(leftStatus.segement, rightStatus.segement),
                        leftStatus.right + rightStatus.left),
                Math.max(leftStatus.interval + rightStatus.left, leftStatus.left),
                Math.max(rightStatus.interval + leftStatus.right, rightStatus.right));
    }

    public static void main(String[] args) {
        int[] nums = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
        System.out.println(new Solution0053().maxSubArray(nums));
        System.out.println(new Solution0053().maxSubArray2(nums));
        System.out.println(new Solution0053().maxSubArray3(nums));
    }
}
