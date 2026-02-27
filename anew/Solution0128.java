package anew;

import java.util.Set;
import java.util.HashSet;

// 给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

// 请你设计并实现时间复杂度为 O(n) 的算法解决此问题。

public class Solution0128 {
    public int longestConsecutive(int[] nums) {
        Set<Integer> set = new HashSet<>();
        for (int num : nums) {
            set.add(num);
        }

        int maxLen = 0;
        for (int num : set) {
            if (!set.contains(num - 1)) {
                int currNum = num;
                int currLen = 1;
                while (set.contains(currNum + 1)) {
                    currNum++;
                    currLen++;
                }
                maxLen = Math.max(maxLen, currLen);
            }
        }
        return maxLen;
    }
}
