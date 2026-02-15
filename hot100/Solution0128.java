package hot100;

// 给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

// 请你设计并实现时间复杂度为 O(n) 的算法解决此问题。

import java.util.*;

public class Solution0128 {
    public int longestConsecutive(int[] nums) {
        int maxLen = 0;
        Set<Integer> set = new HashSet<>();
        for (int num : nums) {
            set.add(num);
        }

        for (int num : set) {
            if (!set.contains(num - 1)) {
                int currentNums = num;
                int currentLen = 1;
                while(set.contains(currentNums + 1)){
                    currentLen++;
                    currentNums++;
                }
                maxLen = Math.max(maxLen, currentLen);
            }
        }
        return maxLen;
    }

    public static void main(String[] args) {
        Solution0128 solution0128 = new Solution0128();
        int[] nums = {100, 4, 200, 1, 3, 2};
        System.out.println(solution0128.longestConsecutive(nums));
    }
}
