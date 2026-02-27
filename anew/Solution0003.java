package anew;

import java.util.Set;
import java.util.HashSet;

// 给定一个字符串 s，请你找出其中不含有重复字符的 最长 子串 的长度。

public class Solution0003 {
    public int lengthOfLongestSubstring(String s) {
        Set<Character> set = new HashSet<>();
        int maxLen = 0;
        int left = 0;
        for (int right = 0; right < s.length(); right++) {
            while (set.contains(s.charAt(right))) {
                set.remove(s.charAt(right));
                left++;
            }
            set.add(s.charAt(right));
            maxLen = Math.max(maxLen, right - left + 1);
        }
        return maxLen;
    }

    public int lengthOfLongestSubstring2(String s) {
        int[] lastAppear = new int[128];
        int maxLen = 0;
        int left = 0;
        for (int right = 0; right < s.length(); right++) {
            left = Math.max(left, lastAppear[s.charAt(right)]);
            maxLen = Math.max(maxLen, right - left + 1);
            lastAppear[s.charAt(right)] = right + 1;
        }
        return maxLen;
    }

    public static void main(String[] args) {
        Solution0003 solution0003 = new Solution0003();
        System.out.println(solution0003.lengthOfLongestSubstring("abcabcbb"));
        System.out.println(solution0003.lengthOfLongestSubstring2("abcabcbb"));
    }
}
