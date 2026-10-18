import java.util.*;

//给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
//
//算法的时间复杂度应该为 O(log (m+n)) 。

public class Solution0004 {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int n1 = nums1.length, n2 = nums2.length;
        if (n1 > n2) {
            return findMedianSortedArrays(nums2, nums1);
        }
        int median1 = 0, median2 = 0;
        int left = 0, right = n1;
        while (left <= right) {
            int mid1 = left + (right - left) / 2;
            int mid2 = (n1 + n2) / 2 - mid1;
            int leftMax1 = mid1 == 0 ? Integer.MIN_VALUE : nums1[mid1 - 1];
            int rightMin1 = mid1 == n1 ? Integer.MAX_VALUE : nums1[mid1];
            int leftMax2 = mid2 == 0 ? Integer.MIN_VALUE : nums2[mid2 - 1];
            int rightMin2 = mid2 == n2 ? Integer.MAX_VALUE : nums2[mid2];
            if (leftMax1 <= rightMin2) {
                median1 = Math.max(leftMax1, leftMax2);
                median2 = Math.min(rightMin1, rightMin2);
                left = mid1 + 1;
            } else {
                right = mid1 - 1;
            }
        }
        return (n1 + n2) % 2 == 0 ? ((double) median1 + median2) / 2 : median2;
    }
}
