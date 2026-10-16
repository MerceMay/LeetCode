import java.util.*;

//给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
//
//算法的时间复杂度应该为 O(log (m+n)) 。

public class Solution0004 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line1 = sc.nextLine();
        String line2 = sc.nextLine();
        int[] nums1 = Arrays.stream(line1.substring(1, line1.length() - 1).split(","))
                .mapToInt(Integer::parseInt)
                .toArray();
        int[] nums2 = Arrays.stream(line2.substring(1, line2.length() - 1).split(","))
                .mapToInt(Integer::parseInt)
                .toArray();
        System.out.println(findMedianSortedArrays(nums1, nums2));
        System.out.println(findMedianSortedArrays2(nums1, nums2));
    }

    public static double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int len1 = nums1.length, len2 = nums2.length;
        if (len1 > len2) {
            return findMedianSortedArrays(nums2, nums1);
        }
        int median1 = 0, median2 = 0;
        int left = 0, right = len1; // 切的位置
        while (left <= right) {
            int mid1 = left + ((right - left) >> 1);
            int mid2 = (len1 + len2) / 2 - mid1; // 注意，左半边只有(len1 + len2) / 2，也就是奇数5个，左边只有3个，这关乎最后return的，如果是(len1 + len2 + 1) / 2，return应该返回median1
            int leftMax1 = mid1 == 0 ? Integer.MIN_VALUE : nums1[mid1 - 1];
            int rightMin1 = mid1 == len1 ? Integer.MAX_VALUE : nums1[mid1];
            int leftMax2 = mid2 == 0 ? Integer.MIN_VALUE : nums2[mid2 - 1];
            int rightMin2 = mid2 == len2 ? Integer.MAX_VALUE : nums2[mid2];

            if (leftMax1 <= rightMin2) {
                median1 = Math.max(leftMax1, leftMax2);
                median2 = Math.min(rightMin1, rightMin2);
                left = mid1 + 1;
            } else {
                right = mid1 - 1;
            }
        }
        return (len1 + len2) % 2 == 0 ? (median1 + median2) / 2.0 : median2;
    }

    public static double findMedianSortedArrays2(int[] nums1, int[] nums2) {
        int len1 = nums1.length, len2 = nums2.length;
        int totalLen = len1 + len2;
        if (totalLen % 2 == 1) {
            int midIndex = totalLen / 2;
            return getKth(nums1, nums2, midIndex + 1);
        } else {
            int midIndex1 = totalLen / 2 - 1, midIndex2 = totalLen / 2;
            return (getKth(nums1, nums2, midIndex1 + 1) + getKth(nums1, nums2, midIndex2 + 1)) / 2.0;
        }
    }

    private static double getKth(int[] nums1, int[] nums2, int k) {
        int len1 = nums1.length, len2 = nums2.length;
        int index1 = 0, index2 = 0;
        int kth = 0;
        while (true) {
            if (index1 == len1) {
                return nums2[index2 + k - 1];
            }
            if (index2 == len2) {
                return nums1[index1 + k - 1];
            }
            if (k == 1) {
                return Math.min(nums1[index1], nums2[index2]);
            }

            int half = k / 2;
            int newIndex1 = Math.min(index1 + half, len1) - 1;
            int newIndex2 = Math.min(index2 + half, len2) - 1;
            int pivot1 = nums1[newIndex1], pivot2 = nums2[newIndex2];
            if (pivot1 <= pivot2) {
                k -= (newIndex1 - index1 + 1);
                index1 = newIndex1 + 1;
            } else {
                k -= (newIndex2 - index2 + 1);
                index2 = newIndex2 + 1;
            }
        }
    }
}
