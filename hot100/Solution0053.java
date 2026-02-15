package hot100;

public class Solution0053 {
    public int maxSubArray(int[] nums) {
        int currentSum = nums[0];
        int maxSum = nums[0];
        for (int i = 1; i < nums.length; i++) {
            currentSum = Math.max(currentSum + nums[i], nums[i]);
            maxSum = Math.max(maxSum, currentSum);
        }
        return maxSum;
    }

    public int maxSubArray2(int[] nums) {
        return maxSubArray2Helper(nums, 0, nums.length - 1);
    }

    private int maxSubArray2Helper(int[] nums, int left, int right) {
        if (left == right) {
            return nums[left];
        }
        int mid = left + (right - left) / 2;
        int leftMax = maxSubArray2Helper(nums, left, mid);
        int rightMax = maxSubArray2Helper(nums, mid + 1, right);

        int tempSum = 0;
        int leftCrossMax = Integer.MIN_VALUE;
        int rightCrossMax = Integer.MIN_VALUE;

        for (int i = mid; i >= left; i--) {
            tempSum += nums[i];
            leftCrossMax = Math.max(leftCrossMax, tempSum);
        }
        tempSum = 0;
        for (int i = mid + 1; i <= right; i++) {
            tempSum += nums[i];
            rightCrossMax = Math.max(rightCrossMax, tempSum);
        }
        return Math.max(Math.max(leftMax, rightMax), leftCrossMax + rightCrossMax);
    }

    private record Status(int interval_sum, int left_sum, int right_sum, int segement_sum) {
    }

    public int maxSubArray3(int[] nums) {
        return maxSubArray3Helper(nums, 0, nums.length - 1).segement_sum;
    }

    private Status maxSubArray3Helper(int[] nums, int left, int right) {
        if (left == right) {
            return new Status(nums[left], nums[left], nums[left], nums[left]);
        }

        int mid = left + (right - left) / 2;
        Status leftStatus = maxSubArray3Helper(nums, left, mid);
        Status rightStatus = maxSubArray3Helper(nums, mid + 1, right);

        return new Status(
                leftStatus.interval_sum + rightStatus.interval_sum,
                Math.max(leftStatus.left_sum, leftStatus.interval_sum + rightStatus.left_sum),
                Math.max(rightStatus.right_sum, rightStatus.interval_sum + leftStatus.right_sum),
                Math.max(Math.max(leftStatus.segement_sum, rightStatus.segement_sum),
                        leftStatus.right_sum + rightStatus.left_sum));
    }

    public static void main(String[] args) {
        int[] nums = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
        System.out.println(new Solution0053().maxSubArray(nums));
        System.out.println(new Solution0053().maxSubArray2(nums));
        System.out.println(new Solution0053().maxSubArray3(nums));
    }
}
