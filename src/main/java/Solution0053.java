import java.util.*;


//给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
//
//子数组是数组中的一个连续部分。

public class Solution0053 {
    public int maxSubArray(int[] nums) {
        int max = nums[0], preSum = 0;
        for (int num : nums) {
            preSum = Math.max(preSum + num, num);
            max = Math.max(max, preSum);
        }
        return max;
    }

    public static class Status {
        public int lSum;
        public int rSum;
        public int iSum;
        public int aSum;

        public Status(int l, int r, int i, int a) {
            lSum = l;
            rSum = r;
            iSum = i;
            aSum = a;
        }

    }

    public int maxSubArray2(int[] nums) {
        return getStatus(nums, 0, nums.length - 1).iSum;
    }

    private Status getStatus(int[] nums, int left, int right) {
        if (left == right) {
            return new Status(nums[left], nums[right], nums[left], nums[right]);
        }
        int mid = left + (right - left) / 2;
        Status ls = getStatus(nums, left, mid);
        Status rs = getStatus(nums, mid + 1, right);
        return combine(ls, rs);
    }

    private Status combine(Status ls, Status rs) {
        return new Status(
                Math.max(ls.lSum, ls.aSum + rs.lSum),
                Math.max(rs.rSum, rs.aSum + ls.rSum),
                Math.max(Math.max(ls.iSum, rs.iSum), ls.rSum + rs.lSum),
                ls.aSum + rs.aSum
        );
    }
}
