package anew;

// 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。

// 算法的时间复杂度应该为 O(log (m+n)) 。

public class Solution0004 {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int m = nums1.length;
        int n = nums2.length;
        if (m > n) {
            findMedianSortedArrays(nums2, nums1);
        }
        int left = 0, right = m;
        int leftMax = 0, rightMin = 0;
        while (left <= right) {
            int cut1 = left + (right - left) / 2;
            int cut2 = (m + n + 1) / 2 - cut1;

            int leftMax1 = cut1 == 0 ? Integer.MIN_VALUE : nums1[cut1 - 1];
            int rightMin1 = cut1 == m ? Integer.MAX_VALUE : nums1[cut1];
            int leftMax2 = cut2 == 0 ? Integer.MIN_VALUE : nums2[cut2 - 1];
            int rightMin2 = cut2 == n ? Integer.MAX_VALUE : nums2[cut2];

            if (leftMax1 < rightMin2) {
                leftMax = Math.max(leftMax1, leftMax2);
                rightMin = Math.min(rightMin1, rightMin2);
                left = cut1 + 1;
            } else {
                right = cut1 - 1;
            }
        }
        return (m + n) % 2 == 0 ? (leftMax + rightMin) / 2.0 : leftMax;
    }

    public double findMedianSortedArrays2(int[] nums1, int[] nums2) {
        int totalLength = nums1.length + nums2.length;
        if (totalLength % 2 == 1) {
            return findKth(nums1, nums2, totalLength / 2 + 1);
        } else {
            return (findKth(nums1, nums2, totalLength / 2) + findKth(nums1, nums2, totalLength / 2 + 1)) / 2.0;
        }
    }

    private double findKth(int[] nums1, int[] nums2, int k) {
        int index1 = 0;
        int index2 = 0;
        while (true) {
            if (index1 == nums1.length) {
                return nums2[index2 + k - 1];
            }
            if (index2 == nums2.length) {
                return nums1[index1 + k - 1];
            }
            if (k == 1) {
                return Math.min(nums1[index1], nums2[index2]);
            }
            int half = k / 2;
            int newIndex1 = Math.min(index1 + half, nums1.length) - 1;
            int newIndex2 = Math.min(index2 + half, nums2.length) - 1;
            if (nums1[newIndex1] <= nums2[index2]) {
                k -= newIndex1 - index1 + 1;
                index1 = newIndex1 + 1;
            } else {
                k -= newIndex2 - index1 + 1;
                index2 = newIndex2 + 1;
            }
        }
    }

    public static void main(String[] args) {
        Solution0004 solution = new Solution0004();
        int[] nums1 = { 1, 3 };
        int[] nums2 = { 2 };
        System.out.println(solution.findMedianSortedArrays(nums1, nums2)); // 输出: 2.0
        System.out.println(solution.findMedianSortedArrays2(nums1, nums2)); // 输出: 2.0
    }
}
